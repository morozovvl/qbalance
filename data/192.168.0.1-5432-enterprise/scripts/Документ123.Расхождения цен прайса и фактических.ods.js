var diffTotal = 0;
var priceDict = getDictionary("прайс");
  
function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  priceDict.setId(reportContext.getValue("таблица.КОД_ПРАЙС", strNum));
  var quan = reportContext.getValue("таблица.P1__КОЛ", strNum) * priceDict.getValue("КОЛ_ПРАЙС") / priceDict.getValue("КОЛ_ТОВАР");
  reportContext.setValue("таблица.P1__КОЛ", quan, strNum);
  var faktPrice = reportContext.getValue("таблица.P1__ЦЕНА", strNum) * priceDict.getValue("КОЛ_ТОВАР") / priceDict.getValue("КОЛ_ПРАЙС");
  reportContext.setValue("таблица.P1__ЦЕНА", faktPrice, strNum);
  var zakazPrice = reportContext.getValue("таблица.ЦЕНА_В_ПРАЙСЕ", strNum) * priceDict.getValue("КОЛ_ТОВАР") / priceDict.getValue("КОЛ_ПРАЙС");
  reportContext.setValue("таблица.ЦЕНА_В_ПРАЙСЕ", zakazPrice, strNum);
  var diffPrice = faktPrice - zakazPrice;
  var diff = quan * diffPrice;
  var diffProc = (faktPrice - zakazPrice) * 100 / zakazPrice;
  diffTotal = diffTotal + diff;
  reportContext.setValue("таблица.РАЗНИЦАПРОЦЕНТ", diffProc, strNum);
  reportContext.setValue("таблица.РАЗНИЦАВЦЕНЕ", diffPrice, strNum);
  reportContext.setValue("таблица.РАЗНИЦАСУММА", diff, strNum);
  reportContext.setValue("ИТОГОРАЗНИЦА", diffTotal);
}
