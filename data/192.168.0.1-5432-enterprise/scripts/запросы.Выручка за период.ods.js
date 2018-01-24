scriptResult = false;
if (app.isSA())
{
  var calendar = new CalendarForm();
  calendar.exec();
  if (calendar.isFormSelected())
  {
    var command = "SELECT s.ОПЕР, s.НОМЕРОПЕР, t.ИМЯ, SUM(s.ДЕБЕТ) AS ДЕБЕТ, SUM(s.КРЕДИТ) AS КРЕДИТ \
		  FROM sp_calcdocoborot('49', '" + calendar.getBeginDate().toLocaleDateString() + "', '" + calendar.getEndDate().toLocaleDateString() + "') s INNER JOIN топер t ON s.ОПЕР = t.ОПЕР AND s.НОМЕРОПЕР = t.НОМЕР \
		  GROUP BY s.ОПЕР, s.НОМЕРОПЕР, t.ИМЯ \
		  ORDER BY s.ОПЕР, s.НОМЕРОПЕР;";
    var query = db.execQuery(command);
    table.appendPrintValues("расчет", query);
    reportContext.setValue("ДАТАНАЧАЛО", calendar.getBeginDate().toLocaleDateString());
    reportContext.setValue("ДАТАКОНЕЦ", calendar.getEndDate().toLocaleDateString());
    scriptResult = true;
  }
}


