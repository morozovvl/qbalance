function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var quan;
  var price;
  var sum;
  
  quan = reportContext.getValue("таблица.КОНКОЛ", strNum);
  price = reportContext.getValue("таблица.ТОВАР__ЦЕНА", strNum);
  sum = quan * price;
  reportContext.setValue("таблица.ТОВАР__СУММА", sum, strNum);
}
