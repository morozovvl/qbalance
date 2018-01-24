var addrName = "";
var totSum = 0;

function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var quan;
  var price;
  var sum;
  
  quan = reportContext.getValue("таблица.КОНКОЛ", strNum);
  price = reportContext.getValue("таблица.ТОВАР__ЦЕНА", strNum);
  sum = quan * price;
  reportContext.setValue("таблица.ТОВАР__СУММА", sum, strNum);
  var addr = reportContext.getValue("таблица.АДРЕС__ИМЯ", strNum);
  if (addr != addrName)
    addrName = addr;
  else
    reportContext.setValue("таблица.АДРЕС__ИМЯ", "", strNum);
  totSum = totSum + sum;
}


function EventBeforeTotalPrint()
{
  reportContext.setValue("ИТОГО", totSum);
}


reportContext.clearSortOrder();
reportContext.appendSortOrder("таблица.АДРЕС__ИМЯ");
reportContext.appendSortOrder("таблица.ТОВАР__ИМЯ");
reportContext.sortTable();
