var saldo = 0;
scriptResult = false;

if (app.isSA())
{
  var calendar = new CalendarForm();
  calendar.exec();
  if (calendar.isFormSelected())
  {
    var command = "SELECT * FROM sp_calcobjoborot('512', 1, '" + calendar.getBeginDate().toLocaleDateString() + "', '" + calendar.getEndDate().toLocaleDateString() + "');";
    var query = db.execQuery(command);
    table.appendPrintValues("расчет", query);
    scriptResult = true;
  }
}


function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  saldo = saldo + reportContext.getValue("расчет.ДЕБЕТ", strNum) - reportContext.getValue("расчет.КРЕДИТ", strNum);
  reportContext.setValue("расчет.САЛЬДО", saldo, strNum);
}


