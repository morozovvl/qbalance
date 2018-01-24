scriptResult = false;
if (app.isSA())
{
  var calendar = new CalendarForm();
  var saldo = 0;
  calendar.exec();
  if (calendar.isFormSelected())
  {
    var command = "SELECT ДАТА, SUM(ДЕБЕТ) AS ДЕБЕТ, SUM(КРЕДИТ) AS КРЕДИТ FROM (SELECT *, CASE WHEN ОПЕРНОМЕР > 0 THEN 1 ELSE 0 END AS ОПЕР FROM sp_calcobjoborot('49', 0, '" + calendar.getBeginDate().toLocaleDateString() + "', '" + calendar.getEndDate().toLocaleDateString() + "')) s GROUP BY ДАТА, ОПЕР ORDER BY ДАТА, ОПЕР;";
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


