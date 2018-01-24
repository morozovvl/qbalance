var diffTotal = 0;
  
function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var quan = reportContext.getValue("таблица.P1__КОЛ", strNum);
  var faktPrice = reportContext.getValue("таблица.P1__ЦЕНА", strNum);
  var zakazPrice = reportContext.getValue("таблица.ЦЕНА_В_ПРАЙСЕ", strNum);
  var diffPrice = faktPrice - zakazPrice;
  var diff = quan * diffPrice;
  var diffProc = (faktPrice - zakazPrice) * 100 / zakazPrice;
  diffTotal = diffTotal + diff;
  reportContext.setValue("таблица.РАЗНИЦАПРОЦЕНТ", diffProc, strNum);
  reportContext.setValue("таблица.РАЗНИЦАВЦЕНЕ", diffPrice, strNum);
  reportContext.setValue("таблица.РАЗНИЦАСУММА", diff, strNum);
  reportContext.setValue("ИТОГОРАЗНИЦА", diffTotal);
}
