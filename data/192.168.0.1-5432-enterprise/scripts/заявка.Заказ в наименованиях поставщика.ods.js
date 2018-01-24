var firmDict = getDictionary("фирмы");
var searchExpression = table.getSearchExpression("фирмы");
firmDict.queryName(searchExpression);
if (firmDict.getRowCount() == 1)
{
  var firmId = firmDict.getId();
  if (firmId > 0)
  {
    var itog = 0;
    reportContext.setValue("поставщик", firmDict.getName());
    for (var i = 1; i <= reportContext.getRowCount(); i++)
    {
      var price = 0;
      var priceId = reportContext.getValue("таблица.КОДВПРАЙСЕ", i);
      if (priceId.length > 0)
	price = db.getValue("SELECT МИНЦЕНА FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND КОДВПРАЙСЕ = '" + priceId + "';");
      else
      {
	var priceName = reportContext.getValue("таблица.ИМЯВПРАЙСЕ", i);
	priceName = priceName.replace("'", "''");
	price = db.getValue("SELECT МИНЦЕНА FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND ИМЯ = '" + priceName + "';");
      }
      var sum = reportContext.getValue("таблица.КОЛ_ОБРАБОТАННОЕ", i) * price;
      reportContext.setValue("таблица.ЦЕНА_ОБРАБОТАННАЯ", price, i);
      reportContext.setValue("таблица.СУММА", sum, i);
      itog = itog + sum;
    }
    reportContext.setValue("ИТОГО", itog);
  }
}


reportContext.appendSortOrder("таблица.ИМЯВПРАЙСЕ");
reportContext.sortTable();
