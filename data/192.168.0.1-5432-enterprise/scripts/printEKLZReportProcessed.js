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
var skid_sum = 0;
var oper = 0;
var lastMaxDocId = 0;

if (app.drvFRisValid() && smenaForm != null)			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    // Создадим временную таблицу на сервере со списком чеков
    if (!db.isTableExists("tmp_checks"))
    {
      db.exec("CREATE TABLE tmp_checks (ОПЕР INTEGER, НОМЕРЧЕКА INTEGER, СУММА NUMERIC(10, 2));");
      db.exec("GRANT ALL ON TABLE tmp_checks TO public;");
    }
    else
    {
      db.exec("DELETE FROM tmp_checks;");
    }
  
    smenaForm.findChild("lineEditSmena").setText(drvFR.getProperty("SessionNumber") + 1)
    smenaForm.exec()
    if (smenaForm.isFormSelected())
    {
      drvFR.setProperty("SessionNumber", parseInt(smenaForm.findChild("lineEditSmena").text));
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
    app.print("");
    app.print("По чекам:");
    app.print("Всего продаж на сумму: " + Math.round(prod_sum * 100) / 100);
    app.print("Всего возвратов на сумму: " + vozvr_sum);
    app.print("Итого: " + Math.round((prod_sum - vozvr_sum) * 100) / 100);
    
    command = "SELECT MIN(КОД) FROM документы WHERE ОПЕР = 1 AND ДАТА = (SELECT ДАТА FROM документы WHERE КОД = (SELECT MAX(КОД) FROM докатрибуты1 WHERE НОМЕРЧЕКА = " + firstCheck + "))";
    lastMaxDocId = db.getValue(command);

    var razn = 0;
    var razn1 = 0;
    // Найдем не отбитые чеки
    command = "SELECT d.ДАТАВРЕМЯ, d.НОМЕР, d.СУММА \
		FROM vw_документы d LEFT OUTER JOIN докатрибуты1 da ON d.КОД = da.КОД, \
		  (SELECT ДАТА FROM документы d INNER JOIN докатрибуты1 da ON d.КОД = da.КОД WHERE d.КОД >= " + lastMaxDocId + " AND НОМЕРЧЕКА = " + firstCheck + ") s \
		WHERE d.ДАТА = s.ДАТА AND \
		      d.ОПЕР = 1 AND \
		      d.СУММА > 0 AND \
		      da.НОМЕРЧЕКА IS NULL \
		ORDER BY НОМЕР";
    var wrongCheck = db.execQuery(command);
    if (wrongCheck.first())
    {
      app.print();
      app.print("Не отбитые чеки:");
      while (wrongCheck.isValid())
      {
	var checksRecord = wrongCheck.record();
	app.print("Дата, время:" + new QDateTime(checksRecord.value("ДАТАВРЕМЯ")).toString("dd.MM.yyyy hh:mm:ss") + ", Номер документа: " + checksRecord.value("НОМЕР").toString() + ", Сумма: " + checksRecord.value("СУММА"));
	razn += checksRecord.value("СУММА");
	razn1 += checksRecord.value("СУММА");
	wrongCheck.next();
      }
      app.print("Итого на сумму: " + razn1);
    }
    
    // Найдем чеки, в которых не сходится сумма
    razn1 = 0;
    command = "SELECT d.*, t.СУММА AS СУММА_ЧЕКА \
		FROM tmp_checks t \
		      INNER JOIN \
		    (SELECT d.ДАТАВРЕМЯ, d.НОМЕР, d.СУММА, c.НОМЕРЧЕКА \
		      FROM vw_документы d \
			INNER JOIN (SELECT КОД, НОМЕРЧЕКА \
				    FROM докатрибуты1 \
				    WHERE КОД >= " + lastMaxDocId + " AND НОМЕРЧЕКА >= " + firstCheck + " AND НОМЕРЧЕКА <= " + lastCheck + ") c ON d.КОД = c.КОД \
		    ) d ON t.НОМЕРЧЕКА = d.НОМЕРЧЕКА \
		WHERE t.СУММА <> d.СУММА \
		ORDER BY НОМЕР";
				
    wrongCheck = db.execQuery(command);
    if (wrongCheck.first())
    {
      app.print();
      app.print("Чеки, в которых не сходится сумма:");
      while (wrongCheck.isValid())
      {
	var checksRecord = wrongCheck.record();
	app.print("Дата, время:" + new QDateTime(checksRecord.value("ДАТАВРЕМЯ")).toString("dd.MM.yyyy hh:mm:ss") + ", Номер документа: " + checksRecord.value("НОМЕР").toString() + ", Сумма: " + checksRecord.value("СУММА") + ", Номер чека: " + checksRecord.value("НОМЕРЧЕКА").toString().trim() + ", Сумма в чеке: " + checksRecord.value("СУММА_ЧЕКА").toString().trim());
	razn += checksRecord.value("СУММА") - checksRecord.value("СУММА_ЧЕКА");
	razn1 += checksRecord.value("СУММА") - checksRecord.value("СУММА_ЧЕКА");
	wrongCheck.next();
      }
      app.print("Итого на сумму: " + razn1);
    }

    // Найдем лишние чеки
    razn1 = 0;
    command = "SELECT t.НОМЕРЧЕКА, t.СУММА AS СУММА_ЧЕКА \
		  FROM tmp_checks t \
		      LEFT OUTER JOIN \
		      (SELECT d.ДАТАВРЕМЯ, d.НОМЕР, d.СУММА, d.ОПЕР, c.НОМЕРЧЕКА \
			FROM vw_документы d \
			INNER JOIN (SELECT КОД, НОМЕРЧЕКА \
				    FROM докатрибуты1 \
				    WHERE КОД >= " + lastMaxDocId + " AND НОМЕРЧЕКА >= " + firstCheck + " AND НОМЕРЧЕКА <= " + lastCheck + ") c ON d.КОД = c.КОД \
		      ) d ON t.НОМЕРЧЕКА = d.НОМЕРЧЕКА AND t.ОПЕР = d.ОПЕР \
		  WHERE d.СУММА IS NULL AND \
			t.ОПЕР = 1 \
		ORDER BY НОМЕРЧЕКА";
				
    wrongCheck = db.execQuery(command);
    if (wrongCheck.first())
    {
      app.print();
      app.print("Излишне отбитые чеки:");
      while (wrongCheck.isValid())
      {
	var checksRecord = wrongCheck.record();
	app.print("Номер чека: " + checksRecord.value("НОМЕРЧЕКА").toString().trim() + ", Сумма в чеке: " + checksRecord.value("СУММА_ЧЕКА").toString().trim());
	razn -= checksRecord.value("СУММА_ЧЕКА");
	razn1 += checksRecord.value("СУММА_ЧЕКА");
	wrongCheck.next();
      }
      app.print("Итого на сумму: " + razn1);
    }
    if (razn != 0)
    {
      app.print();
      if (razn >= 0)
	app.print("Не пробито чеков: " + razn);
      else
    	app.print("Излишне пробито чеков: " + (-razn));
      
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
      oper = 1;
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
      oper = 71;
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
    
    if (str.trim().length)
      skid_sum += parseFloat(str);
    
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
    db.exec("INSERT INTO tmp_checks (ОПЕР, НОМЕРЧЕКА, СУММА) VALUES (" + oper + ", " + str + ", " + sum + ");");
    checkOpen = false;
  }
}
