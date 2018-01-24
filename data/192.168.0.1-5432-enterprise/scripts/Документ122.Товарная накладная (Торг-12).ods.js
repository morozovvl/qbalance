var firmId = reportContext.getValue("организации.ФИРМЫ__КОД");
if (firmId > 0)		// Если указана фирма-поставщик
{
  for (var i = 1; i <= getRowCount(); i++)
  {
    var strName = "таблица" + i;
    var tovarId = reportContext.getValue(strName + ".ТОВАР__КОД");
    var priceRec;
    priceRec = db.execQuery("SELECT КОДВПРАЙСЕ, ИМЯ FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND КОД_ТОВАР = " + tovarId + ";");
    if (priceRec.size() != 0)		// Если в прайсе есть записи о такой позиции
    {
      if (priceRec.first())
      {					
          var nomId = priceRec.record().value("КОДВПРАЙСЕ");	
	  var nomName = priceRec.record().value("ИМЯ");
	  reportContext.setValue(strName + ".КОДВПРАЙСЕ", nomId);
	  reportContext.setValue(strName + ".ИМЯВПРАЙСЕ", nomName);
      }
    }
  }
}
