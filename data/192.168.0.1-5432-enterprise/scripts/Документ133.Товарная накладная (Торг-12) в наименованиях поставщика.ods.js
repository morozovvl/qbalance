var firmId = getDictionary("организации").getValue("КОД_ФИРМЫ");
if (firmId > 0)
{
  var itog = 0;
  for (var i = 1; i <= reportContext.getRowCount(); i++)
  {
    var docId = reportContext.getValue("таблица.ДОКУМЕНТЫ123__КОД", i);
    var command = "SELECT * FROM атрибуты123 WHERE ДОККОД = " + docId + " AND КОД_ТОВАР = " + reportContext.getValue("таблица.ТОВАР__КОД", i);
    var attrRec = db.getRecord(command, 0);
    var priceId = attrRec.value("КОД_ПРАЙС");
    var cost = reportContext.getValue("таблица.P2__ЦЕНА", i);
    if (priceId > 0)
    {
      var priceRec = db.getRecord("SELECT * FROM прайс WHERE КОД = " + priceId, 0);
      var idInPrice = priceRec.value("КОДВПРАЙСЕ");
      var nameInPrice = priceRec.value("ИМЯ");
      var unitInPrice = priceRec.value("ЕДИЗМ");
      var firmQuan = priceRec.value("КОЛ_ПРАЙС");
      var ourQuan = priceRec.value("КОЛ_ТОВАР");
      var priceCost = cost * ourQuan / firmQuan;
      var quan = reportContext.getValue("таблица.P1__КОЛ", i) * firmQuan / ourQuan;
      var sum = quan * priceCost;
      reportContext.setValue("таблица.КОД", idInPrice, i);
      reportContext.setValue("таблица.НАИМЕНОВАНИЕ", nameInPrice, i);
      reportContext.setValue("таблица.ЕДИЗМ", unitInPrice, i);
      reportContext.setValue("таблица.КОЛ", quan, i);
      reportContext.setValue("таблица.ЦЕНА", priceCost, i);
      reportContext.setValue("таблица.СУММА", sum, i);
      itog = itog + sum;
    }
  }
  reportContext.setValue("ИТОГО", itog);
}


reportContext.appendSortOrder("таблица.НАИМЕНОВАНИЕ");
reportContext.sortTable();
