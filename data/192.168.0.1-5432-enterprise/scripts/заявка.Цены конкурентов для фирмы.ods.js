var firmDict = getDictionary("фирмы");
firmDict.exec();
if (firmDict.isFormSelected())
{
  var firmId = firmDict.getId();
  reportContext.setValue("ПОСТАВЩИК", firmDict.getName());
  reportContext.setValue("ПОСТАВЩИК", firmDict.getName());
  var command = "SELECT DISTINCT p.КОДВПРАЙСЕ AS КОД, p.ИМЯ, p.ЕДИЗМ, p.КОЛ, p.ЦЕНА_ОБРАБОТАННАЯ AS ЦЕНА, (p.КОЛ * p.ЦЕНА_ОБРАБОТАННАЯ)::numeric(12, 2) AS СУММА, p.НАЛИЧИЕ, \
CASE WHEN p.ЦЕНА_КОНКУРЕНТА > 0 AND p.ЦЕНА_КОНКУРЕНТА < p.ЦЕНА_ОБРАБОТАННАЯ THEN f.ИМЯ ELSE NULL END AS КОНКУРЕНТ, \
CASE WHEN p.ЦЕНА_КОНКУРЕНТА > 0 AND p.ЦЕНА_КОНКУРЕНТА < p.ЦЕНА_ОБРАБОТАННАЯ THEN p.ЦЕНА_КОНКУРЕНТА ELSE NULL END AS ЦЕНА_КОНКУРЕНТА, \
CASE WHEN p.ЦЕНА_КОНКУРЕНТА > 0 AND p.ЦЕНА_КОНКУРЕНТА < p.ЦЕНА_ОБРАБОТАННАЯ THEN ((p.ЦЕНА_КОНКУРЕНТА - p.ЦЕНА_ОБРАБОТАННАЯ) * 100 / p.ЦЕНА_ОБРАБОТАННАЯ)::numeric(10, 1) ELSE NULL END AS ПРОЦЕНТ, \
CASE WHEN p.ЦЕНА_КОНКУРЕНТА > 0 AND p.ЦЕНА_КОНКУРЕНТА < p.ЦЕНА_ОБРАБОТАННАЯ THEN to_char(p.ДАТА_КОНКУРЕНТА, 'DD.MM.YY') ELSE NULL END AS ДАТА \
FROM (SELECT f.*, CASE WHEN f.КОД_ФИРМЫ != p.КОД_ФИРМЫ THEN p.КОД_ФИРМЫ ELSE NULL END AS КОД_КОНКУРЕНТА, CASE WHEN f.КОД_ФИРМЫ != p.КОД_ФИРМЫ THEN (p.ЦЕНА * f.КОЛ_ТОВАР / f.КОЛ_ПРАЙС)::numeric(12, 2) ELSE NULL END AS ЦЕНА_КОНКУРЕНТА, p.ДАТА AS ДАТА_КОНКУРЕНТА \
	FROM (SELECT p.*, (s.КОЛ*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(10, 3) AS КОЛ, s.ЦЕНА, p.МИНЦЕНА AS ЦЕНА_ОБРАБОТАННАЯ \
			FROM vw_прайс3 p INNER JOIN (SELECT p.КОД_ТОВАР, КОЛ, MIN(p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) AS ЦЕНА \
						FROM (SELECT p.*, z.КОЛ \
							FROM vw_прайс3 p INNER JOIN заявка z ON p.КОД_ТОВАР = z.КОД_ТОВАР AND \
								p.КОД_ФИРМЫ = " + firmId + " AND \
								p.ПРИОРИТЕТ = 1 AND z.КОД_ДОКУМЕНТЫ129 = 0 \
							) p \
							GROUP BY p.КОД_ТОВАР, КОЛ) s \
				ON p.КОД_ТОВАР = s.КОД_ТОВАР AND (p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) = s.ЦЕНА AND p.КОД_ФИРМЫ = " + firmId + ") f \
		LEFT OUTER JOIN \
		(SELECT p.КОД_ТОВАР, p.КОД_ФИРМЫ, s.ЦЕНА, p.ДАТА \
			FROM vw_прайс3 p INNER JOIN (SELECT p.КОД_ТОВАР, MIN(p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) AS ЦЕНА \
						FROM (SELECT * \
							FROM vw_прайс3 p \
							WHERE p.КОД_ТОВАР IN (SELECT КОД_ТОВАР FROM заявка) AND \
								p.КОД_ФИРМЫ IN (SELECT КОД FROM фирмы WHERE ПРАЙС_АКТУАЛЕН AND КОД != " + firmId + ") AND \
								p.ПРИОРИТЕТ = 1 AND \
								p.НАЛИЧИЕ = '+' \
							) p \
							GROUP BY p.КОД_ТОВАР) s \
				ON p.КОД_ТОВАР = s.КОД_ТОВАР AND (p.МИНЦЕНА*p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР)::numeric(12, 2) = s.ЦЕНА AND p.КОД_ФИРМЫ IN (SELECT КОД FROM фирмы WHERE ПРАЙС_АКТУАЛЕН AND КОД != " + firmId + ")) p \
		ON f.КОД_ТОВАР = p.КОД_ТОВАР \
) p LEFT OUTER JOIN фирмы f ON p.КОД_КОНКУРЕНТА = f.КОД \
ORDER BY p.ИМЯ";
    
  var priceQuery = db.execQuery(command);
  if (priceQuery.first())
  {
    var i = 1;
    var itog = 0;
    do
    {
      var priceRecord = priceQuery.record();
      reportContext.setValue("цены.КОД", priceRecord.value("КОД"), i);
      reportContext.setValue("цены.ИМЯ", priceRecord.value("ИМЯ"), i);
      reportContext.setValue("цены.ЕДИЗМ", priceRecord.value("ЕДИЗМ"), i);
      reportContext.setValue("цены.КОЛ", priceRecord.value("КОЛ"), i);
      reportContext.setValue("цены.ЦЕНА", priceRecord.value("ЦЕНА"), i);
      var sum = priceRecord.value("СУММА");
      reportContext.setValue("цены.СУММА", sum, i);
      reportContext.setValue("цены.НАЛИЧИЕ", priceRecord.value("НАЛИЧИЕ"), i);
      reportContext.setValue("цены.КОНКУРЕНТ", priceRecord.value("КОНКУРЕНТ"), i);
      reportContext.setValue("цены.ЦЕНА_КОНКУРЕНТА", priceRecord.value("ЦЕНА_КОНКУРЕНТА"), i);
      reportContext.setValue("цены.ПРОЦЕНТ", priceRecord.value("ПРОЦЕНТ"), i);
      reportContext.setValue("цены.ДАТА", priceRecord.value("ДАТА"), i);
      itog = itog + sum;
      i++;
    } while (priceQuery.next());
    reportContext.setValue("ИТОГО", itog);
  }
}
