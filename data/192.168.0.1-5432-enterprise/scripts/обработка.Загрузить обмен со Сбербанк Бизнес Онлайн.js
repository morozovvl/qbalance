// Общие реквизиты документов
var docNumber;
var docDate;
var docSumma;
var docPoluch;
var docPoluchINN;
var docPlat;
var docPlatINN;
var docPoluchSchet;
var docPlatSchet;
var docNaznach;
var docType;
var accId;		// идентификатор банковского счета
var text;
var fileName;
var processed;
var dates = {};
var minDate;
var maxDate;

scriptResult = 1;

if (app.getScript().length > 0)			// Если в параметрах приложения задано выполнение этого скрипта
  fileName = app.getScriptParameter();	        // То имя файла с документами возьмем тоже из параметров
else
{
  app.setDirName("bankAccountAnalizeDir");
  fileName = app.getOpenFileName(app, "Откройте документ с банковским обменом", "", "Документ TXT (*.txt)");
}

if (fileName != "")
{    
  var file = new QFile(fileName);
  if (file.open(QIODevice.OpenMode(QIODevice.ReadOnly, QIODevice.Text))) 
  {
    text = new QTextStream(file);
    text.setCodec("Windows-1251");
    while (!text.atEnd()) 
    {
      var str = text.readLine();
      var section = "СекцияДокумент=";
      
      if (str.slice(0, section.length) == section)
      {
        clearVariables();
	docType = str.slice(section.length);
	if (!Platezhka(false))
	  break;
      }
    }
    
    RemoveOldDocs(4, minDate.toLocaleDateString(), maxDate.toLocaleDateString());
    RemoveOldDocs(12, minDate.toLocaleDateString(), maxDate.toLocaleDateString());
    RemoveOldDocs(55, minDate.toLocaleDateString(), maxDate.toLocaleDateString());
    RemoveOldDocs(128, minDate.toLocaleDateString(), maxDate.toLocaleDateString());
    
    text.seek(0);
    while (!text.atEnd()) 
    {
      var str = text.readLine();
      var section = "СекцияДокумент=";
      
      if (str.slice(0, section.length) == section)
      {
        clearVariables();
	docType = str.slice(section.length);
	if (!Platezhka(true))
	  break;
      }
    }
    file.close();
  }
  else
  {
    scriptResult = 2;	// Не удалось открыть файл
  }
}
else
  scriptResult = 0;


function toDate(dateStr) 
{
  var numbers = dateStr.match(/\d+/g); 
  return new Date(numbers[2], numbers[1] - 1, numbers[0]);
}


function clearVariables()
{
  docNumber = "";
  docDate = "";
  docSumma = "";
  docPoluch = "";
  docPoluchINN = "";
  docPlat = "";
  docPlatINN = "";
  docNaznach = "";
  docPoluchSchet = "";
  docPlatSchet = "";
}


function readHeader()
{
  var str = text.readLine();
  while (str != "КонецДокумента")
  {
    var section = "Номер=";
    if (str.slice(0, section.length) == section)
    {
      docNumber = str.slice(section.length);
      docNumber = docNumber.replace(/^0*/, '');		// Удалим лидирующие нули
    }
    else
    {
      section = "Дата=";
      if (str.slice(0, section.length) == section)
      {
	docDate = str.slice(section.length);
	var currentDate = toDate(docDate);
	if (minDate == undefined || minDate > currentDate)
	  minDate = currentDate;
	if (maxDate == undefined || maxDate < currentDate)
	  maxDate = currentDate;
      }
      else
      {
	section = "Сумма=";
	if (str.slice(0, section.length) == section)
	{
	  docSumma = str.slice(section.length);
	}
	else
	{
	  section = "Плательщик=";
	  if (str.slice(0, section.length) == section)
	  {
	    docPlat = str.slice(section.length);
	  }
	  else
	  {
	    section = "ПлательщикИНН=";
	    if (str.slice(0, section.length) == section)
	    {
	      docPlatINN = str.slice(section.length);
	    }
	    else
	    {
	      section = "Получатель=";
	      if (str.slice(0, section.length) == section)
	      {
		docPoluch = str.slice(section.length);
	      }
	      else
	      {
		section = "ПолучательИНН=";
		if (str.slice(0, section.length) == section)
		{
		  docPoluchINN = str.slice(section.length);
		}
		else
		{
		  section = "НазначениеПлатежа=";
		  if (str.slice(0, section.length) == section)
		  {
		    docNaznach = str.slice(section.length);
		    docNaznach = docNaznach.replace(/\'/g, "''");
		  }
		  else
		  {
		    section = "ПлательщикСчет=";
		    if (str.slice(0, section.length) == section)
		    {
		      docPlatSchet = str.slice(section.length);
		    }
		    else
		    {
		      section = "ПолучательСчет=";
		      if (str.slice(0, section.length) == section)
		      {
			docPoluchSchet = str.slice(section.length);
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    str = text.readLine();
  }
}


function Platezhka(makeDocs)
{
  var operNum;
  var orgName;		// наименование организации
  var inn = "";
  var acc = "";
  var success = true;
  processed = false;
  readHeader();
  if (makeDocs)
  {
    app.debug(1, "");
    app.debug(1, "Документ "  + docNumber + ". Начало обработки документа.");
	
  
    if (app.getConst("ИНН").toString().trim().replace(/"/g, '') == docPlatINN)	// Если мы являемся плательщиками
    {
      operNum = 4;
      WriteDoc(operNum, docPoluchINN, docPoluch, docPlatSchet);
    }
    else							// иначе - мы являемся получателями
    {
      if (docType == "-прочее")			// Если деньги нам платит Сбербарк, значит это выручка
      {
	operNum = 12;
	WriteDoc(operNum, 0, '', docPoluchSchet);
      }
      else
      {
	if (docNaznach.toUpperCase().indexOf('ДЕНЕЖНАЯ НАЛИЧНОСТЬ,ПОСТУПИВШАЯ ЧЕРЕЗ БАНКОМАТ') >= 0)
	{
	  operNum = 128;
	  WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);
	  operNum = 55;
	  WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);
	}
      
	else if (docNaznach.toUpperCase().indexOf('ПО ДОГОВОРУ ЭКВАЙРИНГА') >= 0)
	{
	  operNum = 128;
	  var commissionSubstr = 'комиссия: ';
	  var subStr = docNaznach.substr(docNaznach.indexOf(commissionSubstr));
	  subStr = subStr.replace(commissionSubstr, "");
	  var commission = parseFloat(subStr.substr(0, subStr.indexOf(";")));
	  commission = Math.round(commission * 100) / 100;
	  docSumma = parseFloat(docSumma) + commission;
	  docSumma = Math.round(docSumma * 100) / 100;
	  WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);

	  operNum = 55;
	  WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);
	
	  operNum = 4;
	  docSumma = commission;
	  if (docSumma > 0)
	    WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);
	}
	else
	{
	  operNum = 55;
	  WriteDoc(operNum, docPlatINN, docPlat, docPoluchSchet);
	}
      }
    }
    if (!processed)
      app.print("Не удалось обработать " + docType + " № " + docNumber + " от " + docDate + " на сумму " + docSumma);
    app.debug(1, "\\Документ "  + docNumber + ". Конец обработки документа.");  
  }
  return success;
}


function WriteDoc(operNum, inn, orgName, acc)
{
  var command;
  var rec;
  var orgId;		// идентификатор организации
  var success = true;
  
  if (operNum > 0)
  {
    if (inn != 0)
    {
      command = "SELECT КОД, ИМЯ FROM организации WHERE trim(ИНН) = '" + inn + "';";
      rec = db.execQuery(command);
      if (!rec.first())
      {
	var insertCommand = "INSERT INTO организации (ИМЯ, ИНН) VALUES ('" + orgName + "', '" + inn + "');";
	db.execQuery(insertCommand);
	rec = db.execQuery(command);
	if (!rec.first())
	{
	  app.print("Не удалось создать запись о контрагенте <" + orgName + "> с ИНН " + inn);
	  success = false;
	}
	else
	  app.print("Добавлена запись о контрагенте <" + orgName + "> с ИНН " + inn);
      }
      orgId = rec.record().value(0);
      orgName = rec.record().value(1).toString().trim();
    }

    if (success)
    {
      success = false;
      command = "SELECT КОД FROM банковские_счета WHERE trim(СЧЕТ) = '" + acc + "';";
      rec = db.execQuery(command);
      if (rec.first())
      {
	accId = rec.record().value(0);
	var documents = app.getDocuments(operNum);
	var document = documents.getDocument();
	
	if (orgId != 0)
	{
	  // Установим в справочнике организаций организацию, которая проходит в платежном поручении
	  var orgDict = document.getDictionary("организации");
	  orgDict.setId(orgId);
	}
	// Установим с справочнике счетов счет получателя
	var accDict = document.getDictionary("банковские_счета");
	accDict.setId(accId);
	
	if (documents.add())
	{
	  // Загрузим документ. При этом, в случае с платежкой, в нем автоматически добавится одна строка со ссылками на организацию-плательщик и счет получателя
	  document.loadDocument();
	  documents.setValue("ДАТА", docDate);
	  documents.setValue("НОМЕР", docNumber);
	  documents.setValue("КОММЕНТАРИЙ", orgName);
	  documents.setValue("ОПИСАНИЕ", docNaznach);
	  documents.setValue("СУММА", docSumma);
	  document.setValue("P1__СУММА", docSumma, 0);
	  document.saveChanges();
	  app.print("Добавлен документ " + docType + " от <" + orgName + "> № " + docNumber + " от " + docDate + " на сумму " + docSumma);
	  success = true;
	}
      }
      else
	app.print("Отсутствует счет с номером " + acc);
    }
    if (!success)
    {
      app.print("Не удалось добавить " + docType + " № " + docNumber + " от " + docDate);
    }
  }
  if (success)
    processed = true;
}


function RemoveOldDocs(oper, oldDate, newDate)
{
  var command = "SELECT КОД FROM документы WHERE ОПЕР = " + oper + " AND ДАТА >= '" + oldDate + "' AND ДАТА <= '" + newDate + "';";
  
  var rec = db.execQuery(command);
  if (rec.first())
  {
    while (rec.isValid())
    {
      var docId = rec.record().value("КОД");
      db.exec("SELECT sp_deletedoc(" + docId + ");");
      rec.next();
    }
  }
  
/*  
  else
  {
    var command = "SELECT КОД FROM документы WHERE ОПЕР = " + oper + " AND ДАТА = '" + date + "' AND trim(НОМЕР) = '" + number + "' AND СУММА = " + sum + ";";
    var rec = db.execQuery(command);
    if (rec.first())
    {
      result = true;
    }
  }
*/  
    
/*  
  var command = "SELECT КОД FROM документы WHERE ОПЕР = " + oper + " AND ДАТА = '" + date + "' AND trim(НОМЕР) = '" + number + "' AND СУММА = " + sum + ";";
  var rec = db.execQuery(command);
  if (rec.first())
  {
    processed = true;
    return true;
  }
  return false;
*/  
}  
      