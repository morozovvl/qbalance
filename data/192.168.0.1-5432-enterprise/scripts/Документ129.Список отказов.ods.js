function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var result = reportContext.getValue("таблица.ВЫПОЛНЕН", strNum);
  if (result)
    return false;
  return true;
}
