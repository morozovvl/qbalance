var firmDict = getDictionary("фирмы");
var firmId = firmDict.getId();
if (firmId > 0)
{
  var itog = 0;
  reportContext.setValue("поставщик", firmDict.getName());
  for (var i = 1; i <= reportContext.getRowCount(); i++)
  {
    var price = 0;
    var priceId = reportContext.getValue("таблица.ПРАЙС__КОДВПРАЙСЕ", i);
    if (priceId.length > 0)
      price = db.getValue("SELECT МИНЦЕНА FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND КОДВПРАЙСЕ = '" + priceId + "';");
    else
    {
      var priceName = reportContext.getValue("таблица.ПРАЙС__ИМЯ", i);
      priceName = priceName.replace("'", "''");
      price = db.getValue("SELECT МИНЦЕНА FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND ИМЯ = '" + priceName + "';");
    }
    var sum = reportContext.getValue("таблица.P1__КОЛ", i) * price;
    reportContext.setValue("таблица.P1__ЦЕНА", price, i);
    reportContext.setValue("таблица.P1__СУММА", sum, i);
    itog = itog + sum;
  }
  reportContext.setValue("ИТОГО", itog);
}


reportContext.appendSortOrder("таблица.ПРАЙС__ИМЯ");
reportContext.sortTable();
