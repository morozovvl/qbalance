var quan = 0;
for (var i = 1; i <= reportContext.getRowCount(); i++)
{
  quan = quan + reportContext.getValue("таблица.ДБКОЛ", i) - reportContext.getValue("таблица.КРКОЛ", i);
  reportContext.setValue("таблица.ОСТАТОК", quan, i);
}
