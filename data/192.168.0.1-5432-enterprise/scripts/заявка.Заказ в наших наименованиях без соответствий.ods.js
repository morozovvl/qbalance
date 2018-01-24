for (var i = 1; i <= getRowCount(); i++)
{
  var strName = "таблица" + i;
  var priceName = reportContext.getValue(strName + ".ИМЯВПРАЙСЕ");
  if (priceName.length > 0)
  {
    reportContext.removeValue(strName); // Удалить строку из таблицы
  }
}

reportContext.appendSortOrder("таблица.ГРУППЫ__ИМЯ");
reportContext.appendSortOrder("таблица.ТОВАР__ИМЯ");
reportContext.sortTable();
