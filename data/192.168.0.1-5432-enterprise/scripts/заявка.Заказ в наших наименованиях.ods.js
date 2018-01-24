var firmDict = getDictionary("фирмы");
var searchExpression = table.getSearchExpression("фирмы");
  firmDict.queryName(searchExpression);
if (firmDict.getRowCount() == 1)
{
  var firmId = firmDict.getId();
  if (firmId > 0)
  {
    var command = "SELECT '' AS ЗАКАЗ, t.КОД::text, t.ИМЯ, t.ЕДИЗМ, t.ЗАПАС, z.КОЛ_ОБРАБОТАННОЕ * p.КОЛ_ТОВАР/p.КОЛ_ПРАЙС AS КОЛ, s.КОНКОЛ AS ОСТАТОК \
		  FROM заявка z INNER JOIN товар t ON z.КОД_ТОВАР = t.КОД \
				  INNER JOIN прайс p ON p.КОД_ФИРМЫ = " + firmId + " AND z.КОД_ТОВАР = p.КОД_ТОВАР \
				  LEFT OUTER JOIN (SELECT КОД_ТОВАР, SUM(КОНКОЛ) AS КОНКОЛ \
						  FROM vw_saldo411 \
						  GROUP BY КОД_ТОВАР) s ON z.КОД_ТОВАР = s.КОД_ТОВАР \
		  WHERE z.КОД_ФИРМЫ = " + firmId + " \
		  UNION \
		  SELECT 'Заказ' AS ЗАКАЗ, КОДВПРАЙСЕ AS КОД, ИМЯВПРАЙСЕ AS ИМЯ, ЕДИЗМВПРАЙСЕ AS ЕДИЗМ, 0 AS ЗАПАС, КОЛ, 0 AS ОСТАТОК \
		  FROM заявка z \
		  WHERE КОД_ФИРМЫ = " + firmId + " AND МОДИФИЦИРОВАНО \
		  ORDER BY ЗАКАЗ, ИМЯ";
    var query = db.execQuery(command);
    table.appendPrintValues("заказ", query);
    table.appendPrintValue("поставщик", searchExpression); 
  }
}
/*
else
{
  if (firmDict.getRowCount() == 0)
    app.showError("Укажите поставщика.");
  else
    app.showError("Задайте поставщика поточнее.");
}
*/
