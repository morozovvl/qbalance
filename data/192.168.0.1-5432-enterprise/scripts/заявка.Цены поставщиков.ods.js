var firmDict = getDictionary("фирмы");
var firmId = 0;
var firmName = "";
var minPrice = 0;
var nalich;


function procPrice(num)
{
  for (var i = 1; i <= reportContext.getRowCount(); i++)
  {
    var price = 0;
    var zak_quan = db.getValue("SELECT КОЛ FROM vw_заказы WHERE КОД_ПРАЙС = " + reportContext.getValue("таблица.КОД_ПРАЙС", i));
    if (zak_quan <= reportContext.getValue("таблица.КОЛ_ОБРАБОТАННОЕ", i))
    {
      reportContext.setValue("таблица.ЗАКАЗАНО", "да", i);
    }
    var id = reportContext.getValue("таблица.КОД_ТОВАР", i);
    if (id > 0)
    {
//      var command = "SELECT МИНЦЕНА, КОЛ_ПРАЙС, КОЛ_ТОВАР FROM vw_прайс3 WHERE КОД_ФИРМЫ = " + firmId + " AND КОД_ТОВАР = " + id + ";";
      var command = "SELECT МИНЦЕНА, КОЛ_ПРАЙС, КОЛ_ТОВАР, НАЛИЧИЕ FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND КОД_ТОВАР = " + id + ";";
      var priceQuery = db.execQuery(command);
      if (priceQuery.first())
      {
	minPrice = 0;
	nalich = "";
	do
	{
	  var priceRecord = priceQuery.record();
	  price = priceRecord.value("МИНЦЕНА");
	  nalich = priceRecord.value("НАЛИЧИЕ");
	  var priceQuan = priceRecord.value("КОЛ_ПРАЙС");
	  var nomQuan = priceRecord.value("КОЛ_ТОВАР");
	  if (nomQuan != 0)
	    price = price * priceQuan / nomQuan;
	  if (minPrice == 0 || minPrice > price)
	    minPrice = price;
	} while (priceQuery.next());
      }
    }
    if (nalich == "-")
      minPrice = -minPrice;
    reportContext.setValue("таблица.ПОСТАВЩИК" + num + "__ЦЕНА", minPrice, i);
    minPrice = 0;
    nalich = "";
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
setPrice(5, 427);	// Нормаль
setPrice(6, 410);	// Бином
setPrice(7, 440);	// НПН
setPrice(8, 426);	// Магистраль
setPrice(9, 435);	// Автодеталь43
setPrice(10, 411);	// Ресурс
setPrice(11, 439);	// Автоград


reportContext.appendSortOrder("таблица.ТОВАР__ИМЯ");
reportContext.sortTable();
