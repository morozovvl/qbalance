scriptResult = false;
if (app.isSA())
{
  var calendar = new CalendarForm();
  calendar.exec();
  if (calendar.isFormSelected())
  {
    var command = "SELECT CASE \
		    WHEN DOW = 0 THEN 'Воскресенье' \
		    WHEN DOW = 1 THEN 'Понедельник' \
		    WHEN DOW = 2 THEN 'Вторник' \
		    WHEN DOW = 3 THEN 'Среда' \
		    WHEN DOW = 4 THEN 'Четверг' \
		    WHEN DOW = 5 THEN 'Пятница' \
		    WHEN DOW = 6 THEN 'Суббота' \
		  END AS ДЕНЬНЕДЕЛИ, СУММА \
		  FROM (SELECT DOW, SUM(КРЕДИТ) AS СУММА \
			FROM (SELECT date_part('dow', ДАТА) AS DOW, КРЕДИТ \
			      FROM sp_calcaccoborot('411', '" + calendar.getBeginDate().toLocaleDateString() + "', '" + calendar.getEndDate().toLocaleDateString() + "') \
			      WHERE ОПЕРНОМЕР = 1) d \
			GROUP BY DOW) s \
		  ORDER BY СУММА DESC;";
    var query = db.execQuery(command);
    table.appendPrintValues("расчет", query);

    reportContext.setValue("ДАТАНАЧАЛО", calendar.getBeginDate().toLocaleDateString());
    reportContext.setValue("ДАТАКОНЕЦ", calendar.getEndDate().toLocaleDateString());
    scriptResult = true;
  }
}


