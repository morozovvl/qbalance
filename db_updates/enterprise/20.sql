-- Function: "sp_распределитьзаказ"()

-- DROP FUNCTION "sp_распределитьзаказ"();

CREATE OR REPLACE FUNCTION "sp_распределитьзаказ"()
  RETURNS void AS
$BODY$
declare cCommand varchar(8000);
	curtemp 	refcursor;
	_id 		заявка.КОД%TYPE;
	_firm_id 	заявка.КОД_ФИРМЫ%TYPE;
	_id_price 	заявка.КОДВПРАЙСЕ%TYPE;
	_name_price	заявка.ИМЯВПРАЙСЕ%TYPE;

begin
	DELETE FROM заявка WHERE МОДИФИЦИРОВАНО = True AND ДАТАОБРАБОТКИ < current_date - 90;
	UPDATE заявка SET КОД_ФИРМЫ = NULL, ЦЕНА = 0, КОДВПРАЙСЕ = '', ИМЯВПРАЙСЕ = '', ЕДИЗМВПРАЙСЕ = '', ДАТАОБРАБОТКИ = NULL, КОЛ_ОБРАБОТАННОЕ = 0, НАЛИЧИЕ = ' ' WHERE МОДИФИЦИРОВАНО = false AND КОД_ДОКУМЕНТЫ129 = 0 AND ФИРМА_ПРИНУД = FALSE;	

-- 	Для позиций с принудительным кодом фирмы
	UPDATE заявка z SET КОД_ФИРМЫ = s.КОД_ФИРМЫ, КОДВПРАЙСЕ = s.КОДВПРАЙСЕ, ИМЯВПРАЙСЕ = s.ИМЯ, ЕДИЗМВПРАЙСЕ = s.ЕДИЗМ, ЦЕНА = s.ЦЕНА, ДАТАОБРАБОТКИ = current_date, КОЛ_ОБРАБОТАННОЕ = round(КОЛ*s.КОЛ_ПРАЙС/s.КОЛ_ТОВАР), ЦЕНА_ОБРАБОТАННАЯ=s.ЦЕНА_ОБРАБОТАННАЯ, НАЛИЧИЕ = s.НАЛИЧИЕ
		FROM (SELECT p.*, p.МИНЦЕНА AS ЦЕНА_ОБРАБОТАННАЯ
		      FROM (SELECT p.*, p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР::numeric(12, 2) AS ЦЕНА
					       FROM (SELECT p.*
						   FROM vw_прайс3 p INNER JOIN (SELECT КОД_ТОВАР, КОД_ФИРМЫ 
									FROM заявка 
									WHERE COALESCE(КОД_ФИРМЫ, 0) != 0 AND КОД_ДОКУМЕНТЫ129 = 0 AND КОД_ТОВАР != 0) s						   
						   ON p.КОД_ТОВАР = s.КОД_ТОВАР AND p.КОД_ФИРМЫ = s.КОД_ФИРМЫ
						   WHERE p.ПРИОРИТЕТ = 1 AND
							p.НАЛИЧИЕ = '+'
						  ) p
						) p
			WHERE (p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) = p.ЦЕНА
			) s WHERE z.КОД_ТОВАР = s.КОД_ТОВАР AND z.КОД_ДОКУМЕНТЫ129 = 0 AND z.ФИРМА_ПРИНУД = TRUE;	
			
-- 	Для всех остальных позиций			
	UPDATE заявка z SET КОД_ФИРМЫ = s.КОД_ФИРМЫ, КОДВПРАЙСЕ = s.КОДВПРАЙСЕ, ИМЯВПРАЙСЕ = s.ИМЯ, ЕДИЗМВПРАЙСЕ = s.ЕДИЗМ, ЦЕНА = s.ЦЕНА, ДАТАОБРАБОТКИ = current_date, КОЛ_ОБРАБОТАННОЕ = round(КОЛ*s.КОЛ_ПРАЙС/s.КОЛ_ТОВАР), ЦЕНА_ОБРАБОТАННАЯ=s.ЦЕНА_ОБРАБОТАННАЯ, НАЛИЧИЕ = s.НАЛИЧИЕ
		FROM (SELECT p.*, s.ЦЕНА, p.МИНЦЕНА AS ЦЕНА_ОБРАБОТАННАЯ
		      FROM vw_прайс3 p INNER JOIN (SELECT p.КОД_ТОВАР, MIN(p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) AS ЦЕНА
					       FROM (SELECT *
						   FROM vw_прайс3 p						   
						   WHERE p.КОД_ТОВАР IN (SELECT КОД_ТОВАР 
									FROM заявка 
									WHERE COALESCE(КОД_ФИРМЫ, 0) = 0 AND КОД_ДОКУМЕНТЫ129 = 0) AND
							p.КОД_ФИРМЫ IN (SELECT КОД FROM фирмы WHERE ПРАЙС_АКТУАЛЕН) AND
							p.ПРИОРИТЕТ = 1 AND
							p.НАЛИЧИЕ = '+'
						  ) p
						GROUP BY p.КОД_ТОВАР) s
			ON p.КОД_ТОВАР = s.КОД_ТОВАР AND (p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) = s.ЦЕНА AND p.КОД_ФИРМЫ IN (SELECT КОД FROM фирмы WHERE ПРАЙС_АКТУАЛЕН)
			) s WHERE COALESCE(z.КОД_ТОВАР, 0) > 0 AND z.КОД_ТОВАР = s.КОД_ТОВАР AND z.КОД_ДОКУМЕНТЫ129 = 0 AND ФИРМА_ПРИНУД = FALSE;	
			
	OPEN curtemp FOR SELECT КОД, КОД_ФИРМЫ, КОДВПРАЙСЕ, ИМЯВПРАЙСЕ FROM заявка WHERE КОД_ДОКУМЕНТЫ129 = 0;
	FETCH FIRST FROM curtemp INTO _id, _firm_id, _id_price, _name_price;
	WHILE found LOOP
		IF char_length(trim(_id_price)) > 0 THEN
			UPDATE заявка SET КОД_ПРАЙС = (SELECT КОД FROM прайс WHERE КОД_ФИРМЫ = _firm_id AND КОДВПРАЙСЕ = _id_price ORDER BY КОД ASC LIMIT 1) WHERE КОД = _id;
		ELSE
			UPDATE заявка SET КОД_ПРАЙС = (SELECT КОД FROM прайс WHERE КОД_ФИРМЫ = _firm_id AND ИМЯ = _name_price ORDER BY КОД ASC LIMIT 1) WHERE КОД = _id;
		END IF;
		FETCH NEXT FROM curtemp INTO _id, _firm_id, _id_price, _name_price;
	END LOOP;
	CLOSE curtemp;
	UPDATE заявка SET НАЛИЧИЕ = p.НАЛИЧИЕ FROM прайс p WHERE КОД_ПРАЙС = p.КОД;
end;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "sp_распределитьзаказ"()
  OWNER TO sa;
