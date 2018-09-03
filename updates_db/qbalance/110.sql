-- Function: "sp_заказатьтовар"(integer)

-- DROP FUNCTION "sp_заказатьтовар"(integer);

CREATE OR REPLACE FUNCTION "sp_заказатьтовар"(nid integer)
  RETURNS void AS
$BODY$
DECLARE
	nOstQuan "сальдо"."КОНКОЛ"%TYPE;
	nZapasQuan "товар"."ЗАПАС"%TYPE;
	nKomplekt "товар"."КОМПЛЕКТ"%TYPE;
	nMinZapas "сальдо"."КОНКОЛ"%TYPE;
	nBrakQuan "сальдо"."КОНКОЛ"%TYPE;
	nZakaz 	"сальдо"."КОНКОЛ"%TYPE;
	nZakazMaded	"сальдо"."КОНКОЛ"%TYPE;
	nGroupId "товар"."КОД_ГРУППЫ"%TYPE;
BEGIN
	nOstQuan := (SELECT s1.QUAN + s2.QUAN
		     FROM (SELECT COALESCE(SUM("КОНКОЛ"), 0) AS QUAN
				FROM "сальдо" 
				WHERE "СЧЕТ" = '411' AND "КОД" IN (SELECT "КОД" 
						FROM "набор1" WHERE "КОД_ТОВАР" = nId
						    )) s1,
				(SELECT COALESCE(SUM("КОНКОЛ"), 0) AS QUAN
				FROM "сальдо" 
				WHERE "СЧЕТ" = '402' AND "КОД" IN (SELECT "КОД" 
			   			    FROM "набор402" WHERE "КОД_ТОВАР" = nId
						    )) s2					    
		     );
	nBrakQuan := (SELECT COALESCE(SUM("КОНКОЛ"), 0) 
		     FROM "сальдо" 
		     WHERE "СЧЕТ" = '411' AND "КОД" IN (SELECT "КОД" 
			   			    FROM "набор1" WHERE "КОД_ТОВАР" = nId AND "КОД_АДРЕС" = (SELECT "КОД" 
													FROM "адрес" 
													WHERE "ИМЯ" ILIKE '%Брак%')
						    )
		     );
	nOstQuan := nOstQuan - nBrakQuan;	     
	nZapasQuan := (SELECT COALESCE("ЗАПАС", 0) FROM "товар" WHERE "КОД" = nId LIMIT 1);
	nKomplekt := (SELECT COALESCE("КОМПЛЕКТ", 0) FROM "товар" WHERE "КОД" = nId LIMIT 1);
	nMinZapas := (SELECT to_number("ЗНАЧЕНИЕ", '999') FROM "константы" WHERE trim("ИМЯ") = 'УровеньЗаказа'); 
	IF nZapasQuan < 0 THEN
		nZapasQuan := 0;
	ELSE
		IF (SELECT COUNT(*) FROM "константы" WHERE "ИМЯ" = 'АвтоматическийЗаказ' AND "ЗНАЧЕНИЕ" = 'да') > 0 THEN
			nZapasQuan := (SELECT COALESCE("АВТЗАПАС", "ЗАПАС") FROM "товар" WHERE "КОД" = nId LIMIT 1);
		END IF;
	END IF;
	IF nKomplekt > nOstQuan THEN
		nMinZapas := nKomplekt - nOstQuan;
	ELSE
		nMinZapas := nZapasQuan * nMinZapas / 100;
	END IF;
--	RAISE NOTICE 'nZapazQuan=%, nOstQuan = %, nMinZapas = %', nZapasQuan, nOstQuan, nMinZapas;
	IF nZapasQuan >= 0 AND nMinZapas > 0 AND nOstQuan <= nMinZapas THEN
		nZakazMaded := 0;
		IF (SELECT COUNT(*) FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" > 0) > 0 THEN
			nZakazMaded := (SELECT SUM("КОЛ") FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" > 0);
		END IF;
--		RAISE NOTICE 'nZapazQuan=%, nOstQuan = %, nZakazMaded = %', nZapasQuan, nOstQuan, nZakazMaded;
		IF (nZapasQuan - nOstQuan - nZakazMaded) > 0 THEN
			IF (SELECT COUNT(*) FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" = 0) = 0 THEN
				nGroupId := (SELECT "КОД_ГРУППЫ" FROM "товар" WHERE "КОД" = nId);
				INSERT INTO "заявка" ("КОД_ТОВАР", "КОД_ГРУППЫ", "КОЛ", "ДАТАЗАЯВКИ") VALUES (nId, nGroupId, nZapasQuan - nOstQuan - nZakazMaded, current_date);
			END IF;
			IF (SELECT "МОДИФИЦИРОВАНО" FROM "заявка" WHERE "КОД_ТОВАР" = nId LIMIT 1) IS NOT TRUE THEN
				IF (nZapasQuan - nOstQuan - nZakazMaded) > 0 THEN
					UPDATE "заявка" SET "КОЛ" = nZapasQuan - nOstQuan - nZakazMaded, "ДАТАЗАЯВКИ" = current_date WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" = 0;
				ELSE
					DELETE FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" = 0 AND NOT "МОДИФИЦИРОВАНО";
				END IF;
			END IF;
		ELSE
			DELETE FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" = 0;			
		END IF;
	ELSE
		DELETE FROM "заявка" WHERE "КОД_ТОВАР" = nId AND "КОД_ДОКУМЕНТЫ129" = 0 AND NOT "МОДИФИЦИРОВАНО";
	END IF;
	RETURN;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION "sp_заказатьтовар"(integer)
  OWNER TO sa;
