var firmDict = getDictionary("фирмы");
var searchExpression = table.getSearchExpression("фирмы");
  firmDict.queryName(searchExpression);
  
if (firmDict.getRowCount() == 1)
{
  var firmId = firmDict.getId();
  if (firmId > 0)
  {
//    command = "SELECT '' AS ЗАКАЗ, t.КОД::text, z.КОДВПРАЙСЕ, z.НАЛИЧИЕ, t.ИМЯ, t.ЕДИЗМ, t.ЗАПАС, p.МИНЦЕНА * p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР AS ЦЕНА, CASE WHEN t.ЦЕНА > 0 THEN ((p.МИНЦЕНА * p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР - t.ЦЕНА)/t.ЦЕНА) * 100 ELSE 0 END AS РОСТЦЕНЫ, (z.КОЛ_ОБРАБОТАННОЕ - COALESCE(z1.КОЛ, 0)) * p.КОЛ_ТОВАР/p.КОЛ_ПРАЙС AS КОЛ, s.КОНКОЛ AS ОСТАТОК \
    command = "SELECT '' AS ЗАКАЗ, t.КОД::text, z.КОДВПРАЙСЕ, z.НАЛИЧИЕ, t.ИМЯ, t.ЕДИЗМ, t.АВТЗАПАС AS ЗАПАС, p.МИНЦЕНА * p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР AS ЦЕНА, CASE WHEN t.ЦЕНА > 0 THEN ((p.МИНЦЕНА * p.КОЛ_ПРАЙС/p.КОЛ_ТОВАР - t.ЦЕНА)/t.ЦЕНА) * 100 ELSE 0 END AS РОСТЦЕНЫ, (z.КОЛ_ОБРАБОТАННОЕ - COALESCE(z1.КОЛ, 0)) * p.КОЛ_ТОВАР/p.КОЛ_ПРАЙС AS КОЛ, s.КОНКОЛ AS ОСТАТОК \
		  FROM заявка z INNER JOIN товар t ON z.КОД_ТОВАР = t.КОД \
				  LEFT OUTER JOIN vw_прайс p ON p.КОД = z.КОД_ПРАЙС \
				  LEFT OUTER JOIN (SELECT КОД_ТОВАР, SUM(КОНКОЛ) AS КОНКОЛ \
						  FROM vw_saldo411 \
						  GROUP BY КОД_ТОВАР) s ON z.КОД_ТОВАР = s.КОД_ТОВАР \
				  LEFT OUTER JOIN vw_заказы z1 ON z.КОД_ПРАЙС = z1.КОД_ПРАЙС \
		  WHERE z.КОД_ФИРМЫ = " + firmId + " AND z.КОЛ_ОБРАБОТАННОЕ > COALESCE(z1.КОЛ, 0) \
		  UNION \
		  SELECT 'Заказ' AS ЗАКАЗ, '' AS КОД, z.КОДВПРАЙСЕ, z.НАЛИЧИЕ, ИМЯВПРАЙСЕ AS ИМЯ, ЕДИЗМВПРАЙСЕ AS ЕДИЗМ, 0 AS ЗАПАС, p.МИНЦЕНА AS ЦЕНА, 0 AS РОСТЦЕНЫ, (z.КОЛ - COALESCE(z1.КОЛ, 0)) AS КОЛ, 0 AS ОСТАТОК \
		  FROM заявка z \
				  INNER JOIN vw_прайс p ON p.КОД = z.КОД_ПРАЙС \
				  LEFT OUTER JOIN vw_заказы z1 ON z.КОД_ПРАЙС = z1.КОД_ПРАЙС \
		  WHERE z.КОД_ФИРМЫ = " + firmId + " AND z.КОД_ТОВАР IS NULL AND МОДИФИЦИРОВАНО AND (z.КОЛ - COALESCE(z1.КОЛ, 0)) > 0 \
		  UNION \
		  SELECT z.НОМЕР AS ЗАКАЗ, '' AS КОД, p.КОДВПРАЙСЕ, p.НАЛИЧИЕ, p.ИМЯ, ЕДИЗМ, 0 AS ЗАПАС, z.ЦЕНА AS ЦЕНА, 0 AS РОСТЦЕНЫ, z.КОЛ, 0 AS ОСТАТОК \
		  FROM прайс p \
		  INNER JOIN (SELECT p.КРКОД, p.КОЛ, p.ЦЕНА, d.НОМЕР \
			      FROM проводки p \
				  INNER JOIN (SELECT ДОККОД, СТР FROM атрибуты3 WHERE NOT ВЫПОЛНЕН AND NOT ОТМЕНЕН) s ON p.ДОККОД = s.ДОККОД AND p.СТР = s.СТР \
				  INNER JOIN (SELECT КОД FROM докатрибуты3 WHERE NOT ВЫПОЛНЕН AND NOT ОТМЕНЕН) s1 ON p.ДОККОД = s1.КОД \
				  INNER JOIN документы d ON p.ДОККОД = d.КОД \
		  WHERE p.НОМЕРОПЕР = 1) z ON p.КОД = z.КРКОД \
		  WHERE p.КОД_ФИРМЫ = " + firmId + " \
		  ORDER BY ЗАКАЗ, ИМЯ";
    var query = db.execQuery(command);
    table.appendPrintValues("заказ", query);
    table.appendPrintValue("поставщик", searchExpression); 
  }
}
else
{
  if (firmDict.getRowCount() > 1)
    app.showError("Найдено более одной фирмы с таким названием. Определите название точнее.");
  else
    app.showError("Не найдено ни одной фирмы с таким названием.");
}
