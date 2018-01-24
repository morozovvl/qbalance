var currentDate = documents.getValue("ДАТА").toLocaleDateString();
var soldTotal = 0;


function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var begQuan = 0;
  var income = 0;
  var outcome = 0;
  var sold = 0;
  var soldSum = 0;
  var id = reportContext.getValue("таблица.ТОВАР__КОД", strNum);
  var command = "SELECT * FROM sp_calctovaroborot(" + id + ", '" + currentDate.toString() + "') ORDER BY ДАТА;";
  var query = db.execQuery(command);
  if (query.first())
  {
    begQuan = query.record().value("ДБКОЛ");
    while (query.next())
    {
      income = income + query.record().value("ДБКОЛ");
      outcome = outcome + query.record().value("КРКОЛ");
    }
   }
  reportContext.setValue("таблица.НАЧОСТАТОК", begQuan, strNum);
  reportContext.setValue("таблица.КОНОСТАТОК", begQuan + income - outcome, strNum);
  income = income - reportContext.getValue("таблица.P1__КОЛ", strNum);
  reportContext.setValue("таблица.ПРИХОД", income, strNum);
  reportContext.setValue("таблица.РАСХОД", outcome, strNum);
  if (outcome > 0 && outcome >= begQuan)
  {
    if (outcome - begQuan <= reportContext.getValue("таблица.P1__КОЛ", strNum))
      sold = outcome - begQuan;
    else
      sold = reportContext.getValue("таблица.P1__КОЛ", strNum);
  }
  soldSum = sold * reportContext.getValue("таблица.P1__ЦЕНА", strNum);
  soldTotal = soldTotal + soldSum;
  reportContext.setValue("таблица.ПРОДАНО", sold, strNum);
  reportContext.setValue("таблица.ПРОДАНОСУММА", soldSum , strNum);
  reportContext.setValue("документ.ПРОДАНОВСЕГО", soldTotal);
  reportContext.setValue("документ.ПРОЦЕНТОВПРОДАНО", Math.round(soldTotal * 100) / reportContext.getValue("документ.СУММА"));
}


reportContext.appendSortOrder("таблица.ТОВАР__ИМЯ");
reportContext.sortTable();
