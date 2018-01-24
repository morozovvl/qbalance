var firmDict = getDictionary("фирмы");
var firmId = 0;
var firmName = "";


function procPrice(num)
{
  for (var i = 1; i <= reportContext.getRowCount(); i++)
  {
    var price = 0;
    var id = reportContext.getValue("таблица.ТОВАР__КОД", i);
    if (id > 0)
    {
      var command = "SELECT МИНЦЕНА, КОЛ_ПРАЙС, КОЛ_ТОВАР FROM vw_прайс3 WHERE КОД_ФИРМЫ = " + firmId + " AND КОД_ТОВАР = " + id + ";";
      var priceQuery = db.execQuery(command);
      if (priceQuery.first())
      {
	var priceRecord = priceQuery.record();
	price = priceRecord.value("МИНЦЕНА");
	var priceQuan = priceRecord.value("КОЛ_ПРАЙС");
	var nomQuan = priceRecord.value("КОЛ_ТОВАР");
	if (nomQuan != 0)
	  price = price * priceQuan / nomQuan;
      }
    }
    reportContext.setValue("таблица.ПОСТАВЩИК" + num + "__ЦЕНА", price, i);
  }
}


function setPrice(num, fId)
{
  firmId = fId;
  firmDict.setId(firmId);
  firmName = firmDict.getName();
  reportContext.setValue("поставщик" + num, firmName);
  procPrice(num);
}


setPrice(1, 117);	// Паскер
setPrice(2, 224);	// Заречный
setPrice(3, 419);	// КурсАвто
setPrice(4, 193);	// Юникс
setPrice(5, 424);	// Корсика
setPrice(6, 427);	// Нормаль
setPrice(7, 410);	// Бином
setPrice(8, 399);	// Движение
setPrice(9, 426);	// Магистраль


