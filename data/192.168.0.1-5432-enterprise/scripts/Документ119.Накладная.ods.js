for (var i = 1; i <= getRowCount(); i++)
{
  var strName = "таблица" + i;
  var tovarQuan = reportContext.getValue(strName + ".P1__КОЛ");
  if (tovarQuan == 0)			// Если количество равно 0
  {
    reportContext.removeValue(strName);	// Удалить строку из таблицы
  }
}
