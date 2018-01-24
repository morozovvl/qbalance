var firmId = 436;
var paskerId = 117;
var priceDict = app.getDictionary("прайс");
var firmDict = app.getDictionary("фирмы");
var idList = {};
var procent = 0;

firmDict.setId(firmId);
procent = firmDict.getValue("ПРОЦЕНТ", 0);	// Процент наценки на прайс, чтобы получить точную конечную цену

priceDict.query("КОД_ФИРМЫ = " + firmId);
for (var i = 0; i < priceDict.rowCount(); i++)
{
  var id = priceDict.getValue("КОДВПРАЙСЕ", i);
  if (id > 0)
    idList[id] = 0;
}

db.exec("DELETE FROM last_price;");
var progress = ProgressDialog("Пересчет цен Бабицкого. Ожидайте...");
var progressCount = 0;
progress.show();
progress.setMaximum(priceDict.rowCount());
for(id in idList) 
{
  priceDict.query("КОД_ФИРМЫ = " + paskerId + " AND КОДВПРАЙСЕ = '" + id + "'");
  var paskerPrice = priceDict.getValue("МИНЦЕНА");
  paskerPrice = paskerPrice * (1 + procent / 100);
  var id_goods = priceDict.getValue("КОД_ТОВАР");
  var paskerName = priceDict.getValue("ИМЯ");
  var paskerUnit = priceDict.getValue("ЕДИЗМ");
  var paskerNalich = priceDict.getValue("НАЛИЧИЕ");
  var command = "INSERT INTO last_price (ID_FIRM, ID, NAME, UNIT, NALICH, PRICE, ID_GOODS) values (" + firmId + ",'" + id + "','" + paskerName + "','" + paskerUnit + "','" + paskerNalich + "'," + paskerPrice + "," + id_goods + ");";
//  print(command);
  db.appendCommand(command);
  progress.setValue(progressCount);
  progressCount++;
}
db.execCommands();
db.exec("SELECT sp_updateprice();");
progress.hide();

