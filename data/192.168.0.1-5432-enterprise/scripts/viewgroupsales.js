var key = argument1;
if (key.length > 0)
{
  var date2 = new Date();
  var date1 = new Date();
  date1.setDate(date2.getDate() - app.getConst("ПросматриватьПродажиДней"));
  var command = "SELECT ДАТА, ОПЕРИМЯ, SUM(ДБКОЛ) AS ДБКОЛ, SUM(КРКОЛ) AS КРКОЛ FROM sp_calcgrouptovaroborot('" + key + "', '" + date1.toLocaleDateString() + "', '" + date2.toLocaleDateString() + "') GROUP BY ДАТА, ОПЕРИМЯ ORDER BY ДАТА"
  sales.setFormTitle("Продажи");
  sales.setSqlCommand(command);
  sales.setTagName("salesTableView");
  sales.query();
  sales.getGrdTable().appendColumnDefinition(1, "ДАТА", "Дата", true);
  sales.getGrdTable().appendColumnDefinition(2, "ОПЕРИМЯ", "Операция", true);
  sales.getGrdTable().appendColumnDefinition(4, "ДБКОЛ", "Поступления", true);
  sales.getGrdTable().appendColumnDefinition(5, "КРКОЛ", "Продажи", true);
  sales.exec();
}
