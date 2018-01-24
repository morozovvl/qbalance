var drvFR = 0;
var smenaForm = app.createForm("смена");
var string = "";
var skidka = "";
var firstCheck = 0;
var lastCheck = 0;
var sum = "";
var checkOpen = false;
var prodCheck = false;
var prod_sum = 0;
var vozvr_sum = 0;


if (app.drvFRisValid() && smenaForm != null)			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    // Создадим временную таблицу на сервере со списком чеков
    if (db.isTableExists("tmp_checks"))
      db.exec("DROP TABLE tmp_checks;");
    db.exec("CREATE TEMP TABLE tmp_checks (НОМЕРЧЕКА INTEGER, СУММА NUMERIC(10, 2));");
  
    smenaForm.findChild("lineEditSmena").setText(drvFR.getProperty("SessionNumber") + 1)
    smenaForm.exec()
    if (smenaForm.isFormSelected())
    {
      drvFR.setProperty("SessionNumber", smenaForm.findChild("lineEditSmena").text);
      string = "";
      sum = "";
      prod_sum = 0;
      vozvr_sum = 0;
      var result = drvFR.GetEKLZJournal();
      while (result == 0)
      {
	var str = drvFR.getProperty("EKLZData");
	if (str.substr(0, 7) == "ПРОДАЖА")
	{
	  app.print(string);
	  string = "";
	}
	if (str.substr(0, 7) == "ВОЗВ.ПР")
	{
	  app.print(string);
	  string = "";
	}
	if (str.substr(0, 10) == "ЗАКР.СМЕНЫ")
	{
	  app.print(string);
	  string = "";
	}
	processStr(str);
	result = drvFR.GetEKLZData();
      }
      app.print(string);
      str = "";
    }
    drvFR.DisConnect();
    // 
    app.print("Всего продаж на сумму: " + prod_sum);
    app.print("Всего возвратов на сумму: " + vozvr_sum);
    // Найдем чеки, в которых не сходится сумма
    command = "SELECT d.*, t.СУММА AS СУММА_ЧЕКА \
		  FROM tmp_checks t \
		  INNER JOIN \
		  (SELECT d.ДАТАВРЕМЯ, d.НОМЕР, d.СУММА, c.НОМЕРЧЕКА \
		   FROM документы d \
		    INNER JOIN (SELECT КОД, НОМЕРЧЕКА \
				FROM докатрибуты1 \
				WHERE НОМЕРЧЕКА >= " + firstCheck + " AND НОМЕРЧЕКА <= " + lastCheck + ") c ON d.КОД = c.КОД \
		  ) d ON t.НОМЕРЧЕКА = d.НОМЕРЧЕКА \
		  WHERE t.СУММА <> d.СУММА";
    var notEquelChecksQuery = db.execQuery(command);
    if (notEquelChecksQuery.first())
    {
      app.print();
      app.print("Чеки, в которых не сходится сумма:");
      while (notEquelChecksQuery.isValid())
      {
	var checksRecord = notEquelChecksQuery.record();
	app.print("Дата, время:" + new QDateTime(checksRecord.value("ДАТАВРЕМЯ")).toString("dd.MM.yyyy hh:mm:ss") + ", Номер документа: " + checksRecord.value("НОМЕР").toString() + ", Сумма: " + checksRecord.value("СУММА") + ", Номер чека: " + checksRecord.value("НОМЕРЧЕКА").toString().trim() + ", Сумма в чеке: " + checksRecord.value("СУММА_ЧЕКА").toString().trim());
	notEquelChecksQuery.next();
      }
    }

    // Найдем не отбитые чеки
    command = "SELECT d.ДАТАВРЕМЯ, d.НОМЕР, d.СУММА \
	     FROM документы d \
	     WHERE d.КОД NOT IN (SELECT КОД \
				FROM докатрибуты1 \
				WHERE НОМЕРЧЕКА >= " + firstCheck + " AND НОМЕРЧЕКА <= " + lastCheck + ") AND \
		   d.КОД >= (SELECT КОД \
				FROM докатрибуты1 \
				WHERE НОМЕРЧЕКА = " + firstCheck + ") AND \
		   d.КОД <= (SELECT КОД \
				FROM докатрибуты1 \
				WHERE НОМЕРЧЕКА = " + lastCheck + ") AND \
		   d.ОПЕР = 1 AND d.СУММА > 0;"
    var absentChecksQuery = db.execQuery(command);
    if (absentChecksQuery.first())
    {
      app.print();
      app.print("Не отбитые чеки:");
      while (absentChecksQuery.isValid())
      {
	var checksRecord = absentChecksQuery.record();
	app.print("Дата, время:" + new QDateTime(checksRecord.value("ДАТАВРЕМЯ")).toString("dd.MM.yyyy hh:mm:ss") + ", Номер документа: " + checksRecord.value("НОМЕР").toString() + ", Сумма: " + checksRecord.value("СУММА"));
	absentChecksQuery.next();
      }
    }
  }
}




function processStr(str)
{
  if (str.substr(0, 7) == "ПРОДАЖА")
  {
    str = str.replace("ПРОДАЖА", "");
    if (str.indexOf("/") > 0)
    {
      str = str.replace(/\//g, ".");
      string += "Продажа;" + str.trim() + ";";
      checkOpen = true;
      prodCheck = true;
    }
  }
  else if (str.substr(0, 8) == "ВОЗВ.ПР.")
  {
    str = str.replace("ВОЗВ.ПР.", "");
    if (str.indexOf("/") > 0)
    {
      str = str.replace(/\//g, ".");
      string += "Возврат;" + str.trim() + ";";
      checkOpen = true;
      prodCheck = false;
    }
  }
  else if (str.substr(6, 10) == "ОПЕРАТОР30" && checkOpen)
  {
    str = str.replace("ОПЕРАТОР30", "");
    string += str.trim() + ";";
  }
  else if (str.substr(0, 4) == "ИТОГ" && checkOpen)
  {
    str = str.replace("ИТОГ", "");
    str = str.replace("*", "");
    sum = str;

    if (prodCheck)
      prod_sum += parseFloat(str);
    else
      vozvr_sum += parseFloat(str);

    str = str.replace(".", ",");
    if (skidka == "")
      string += ";";
    skidka = "";
    string += str.trim() + ";";
  }
  else if (str.substr(0, 4) == "СКИД" && checkOpen)
  {
    str = str.replace("СКИД", "");
    str = str.replace("*", "");
    str = str.replace(".", ",");
    string += str.trim() + ";";
    skidka = str;
  }
  else if (str.indexOf("#") > 0 && checkOpen)
  {
    str = str.substr(0, str.indexOf("#"));
    str = str.replace(/^0+/, "");
    str = str.trim();
    string += str;
    if (firstCheck == 0)
      firstCheck = str;
    lastCheck = str;
    // Запомним номер чека и сумму
    db.exec("INSERT INTO tmp_checks (НОМЕРЧЕКА, СУММА) VALUES (" + str + ", " + sum + ");");
    checkOpen = false;
  }
}
