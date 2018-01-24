var totOldSum = 0;
var totNewSum = 0;
var totDiff = 0;

for (var i = 1; i <= getRowCount(); i++)
{
  var strName = "таблица" + i;
  var oldSum = reportContext.getValue(strName + ".P1__СУММА");
  var newSum = reportContext.getValue(strName + ".P2__СУММА");
  var oldPrice = reportContext.getValue(strName + ".P1__ЦЕНА");
  var newPrice = reportContext.getValue(strName + ".P2__ЦЕНА");
  var difference = newPrice - oldPrice;
  reportContext.setValue(strName + ".РАЗНИЦА", difference);
  totOldSum = totOldSum + oldSum;
  totNewSum = totNewSum + newSum;
  totDiff = totDiff + difference;
}

reportContext.setValue("ИТОГОСТАРАЯСУММА", totOldSum);
reportContext.setValue("ИТОГОНОВАЯСУММА", totNewSum);
reportContext.setValue("ИТОГОРАЗНИЦА", totDiff);
reportContext.appendSortOrder("таблица.ТОВАР__ИМЯ");
reportContext.appendSortOrder("таблица.АДРЕС__ИМЯ");
reportContext.sortTable();
