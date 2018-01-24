scriptResult = false;
if (app.isSA())
{
  var calendar = new CalendarForm();
  calendar.exec();
  if (calendar.isFormSelected())
  {
    var command = "SELECT g.ИМЯ, s.СУММА \
		    FROM группы g \
		      INNER JOIN \
			(SELECT t.КОД_ГРУППЫ, SUM(s.СУММА) AS СУММА \
			  FROM товар t \
			    INNER JOIN \
			      (SELECT * \
			      FROM набор1 s \
				  INNER JOIN (SELECT p.КРКОД AS КОД, p.СУММА \
						FROM проводки p INNER JOIN документы d ON p.ДОККОД = d.КОД \
						WHERE d.ДАТА >= '" + calendar.getBeginDate().toLocaleDateString() + "' AND d.ДАТА <= ' \
						" + calendar.getEndDate().toLocaleDateString() + "' AND (d.ОПЕР = 1 OR d.ОПЕР = 11) AND p.НОМЕРОПЕР = 1) p \
						ON s.КОД = p.КОД) s \
			      ON t.КОД = s.КОД_ТОВАР \
			  GROUP BY t.КОД_ГРУППЫ) s \
		      ON g.КОД = s.КОД_ГРУППЫ \
		      WHERE СУММА > 0 \
		    ORDER BY s.СУММА DESC;"
    var query = db.execQuery(command);
    table.appendPrintValues("расчет", query);

    // Подсчитаем итог
    var itog = 0;
    for (var i = 1; i <= reportContext.getRowCount("расчет"); i++)
    {
      itog = itog + reportContext.getValue("расчет.СУММА", i);
    }
    reportContext.setValue("ИТОГО", itog);
    
    // Подсчитаем процент
    for (var i = 1; i <= reportContext.getRowCount("расчет"); i++)
    {
      reportContext.setValue("расчет.ПРОЦЕНТ", reportContext.getValue("расчет.СУММА", i) * 100 / itog, i);
    }

    reportContext.setValue("ДАТАНАЧАЛО", calendar.getBeginDate().toLocaleDateString());
    reportContext.setValue("ДАТАКОНЕЦ", calendar.getEndDate().toLocaleDateString());
    scriptResult = true;
  }
}


