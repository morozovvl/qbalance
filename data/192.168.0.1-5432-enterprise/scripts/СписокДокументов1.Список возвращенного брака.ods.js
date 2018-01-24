var docType = "";
var docDateTime = "";
var docNum = "";
var docSum = 0;
var docCheck = "";
var docDiscount = 0;
var docTotSum = 0;
var totSum = 0;
var totDiscount = 0;
var totDocSum = 0;
var totPeople = 0;
var totPeople1 = 0;
var totBay = 0;
var totRev = 0;
var totBeznal = 0;
var totBeznalQuan = 0;
var currentDate = getValue("ДАТАВРЕМЯ");
var repeatStr = false;
var minCheckNum = 100000000;
var maxCheckNum = 0;
var day = currentDate.getUTCDate();
var month = currentDate.getMonth() + 1;
var year = currentDate.getFullYear();
var command = "SELECT '2.Возвраты' AS ТИП, p.КОД, p.ДАТАВРЕМЯ, p.СТР, p.НОМЕР, FALSE AS БЕЗНАЛИЧНЫЕ, p.НОМЕРЧЕКА AS НОМЕРЧЕКА, s.АДРЕС, s.НАИМЕНОВАНИЕ, s.ЕДИЗМ, p.КОЛ, p.ЦЕНА, p.КОЛ * p.ЦЕНА AS СУММА, 0 AS СКИДКА, p.КОЛ * p.ЦЕНА AS ДОКСУММА \
			FROM (SELECT p.КОД, d.ДАТА AS ДАТАВРЕМЯ, d.НОМЕР, da.НОМЕРЧЕКА, d.СУММА, p.СТР, p.ДБКОД, p.КОЛ, p.ЦЕНА \
				FROM документы d INNER JOIN проводки p ON d.КОД = p.ДОККОД AND p.ОПЕР = 71 AND p.НОМЕРОПЕР = 1 \
				 LEFT OUTER JOIN докатрибуты71 da ON d.КОД = da.КОД \
     			WHERE p.КОЛ <> 0 AND d.ДАТА >= '" + app.getBeginDate().toLocaleDateString() + "' AND d.ДАТА <= '" + app.getEndDate().toLocaleDateString() + "' \
				) p \
					INNER JOIN (SELECT s.КОД, a.ИМЯ AS АДРЕС, t.ИМЯ AS НАИМЕНОВАНИЕ, t.ЕДИЗМ, t.ЦЕНА \
		    					FROM набор1 s INNER JOIN товар t ON s.КОД_ТОВАР = t.КОД \
								INNER JOIN адрес a ON s.КОД_АДРЕС = a.КОД \
		   						) s ON s.КОД = p.ДБКОД \
			ORDER BY ТИП, ДАТАВРЕМЯ, НОМЕР, СТР";
var query = db.execQuery(command);
reportContext.appendPrintValues("запрос", query);
reportContext.setTableName("запрос");		// Основная таблица будет называться "запрос"


function EventBeforeLinePrint(strNum)
{ //Вызывается перед печатью очередной строки в документе
  var value;
  var type;
  
  value = reportContext.getValue("запрос.ТИП", strNum);
  if (docType != value)	
    docType = value;
  else
    reportContext.setValue("запрос.ТИП", "", strNum);		// Тип документа повторяется, уберем повтор
  type = value;

  value = reportContext.getValue("запрос.ДАТАВРЕМЯ", strNum);
  if (docDateTime.toString() != value.toString())	
    docDateTime = value;
  else
    reportContext.setValue("запрос.ДАТАВРЕМЯ", "", strNum);	// Дата, время документа повторяется, уберем повтор
    
  repeatStr = false;
  value = reportContext.getValue("запрос.НОМЕР", strNum);
  if (docNum != value)	
    docNum = value;
  else
  {
    reportContext.setValue("запрос.НОМЕР", "", strNum);		// Номер документа повторяется, уберем повтор
    repeatStr = true;
  }
  docNum1 = value;
    
  value = 0;  
  value = reportContext.getValue("запрос.СУММА", strNum);
  if (value != undefined)
  {
    if (type.substr(0, 1) == "2")					// Если это Возврат
      value = -value;
    totSum = totSum + value;
  }
    
    
  value = reportContext.getValue("запрос.СКИДКА", strNum);
  if (!repeatStr)	
  {
    docDiscount = value;
    if (value > 0)
      totPeople1 = totPeople1 + 1;
  }
  else
  {
    reportContext.setValue("запрос.СКИДКА", "", strNum);	//  Скидка документа повторяется, уберем повтор
    value = 0;
  }
  
  if (value != undefined)
  {
    if (type.substr(0, 1) == "2")					// Если это Возврат
      value = -value;
    
    totDiscount = totDiscount + value;
  }
    
  value = reportContext.getValue("запрос.ДОКСУММА", strNum);
  if (docTotSum != value || !repeatStr || type.substr(0, 1) == "2")	
  {
    docTotSum = value;
  }
  else
  {
    reportContext.setValue("запрос.ДОКСУММА", "", strNum);	// Сумма документа повторяется, уберем повтор
    value = 0;
  }
  
  if (value != undefined)
  {
    if (type.substr(0, 1) == "2")					// Если это Возврат
    {
      totRev = totRev + value;
      value = -value;
    }
    else
    {
      totBay = totBay + value;
      if (value > 0)
	totPeople = totPeople + 1;
    }
    totDocSum = totDocSum + value;
  }

  if (reportContext.getValue("запрос.БЕЗНАЛИЧНЫЕ", strNum))
  {
    if (value > 0)
    {
      reportContext.setValue("запрос.БЕЗНАЛ", "*", strNum);
      totBeznalQuan = totBeznalQuan + 1;
    }
    totBeznal = totBeznal + value;
  }
}


function EventAfterLinePrint(strNum)
{ //Вызывается после печати очередной строки в документе
}
 
 
function EventBeforeTotalPrint()
{
  reportContext.setValue("СУММА", totBay + totDiscount);  
  reportContext.setValue("СКИДКА", Math.round(totDiscount * 100) / 100 + " (" + Math.round(totDiscount * 10000 / totBay) / 100 + "%)");  
  reportContext.setValue("ВОЗСУММА", totRev);  
  reportContext.setValue("ДОКСУММА", totDocSum);
  reportContext.setValue("ПОКУПАТЕЛЕЙ", totPeople);
  reportContext.setValue("БЕЗНАЛ", totBeznal);
  reportContext.setValue("НАЛИЧНЫЕ", totDocSum - totBeznal);
  if (totPeople > 0)
  {
    reportContext.setValue("ПОКУПАТЕЛЕЙ1", totPeople1 + " (" + Math.round(totPeople1 * 100 / totPeople) + "%)");
    reportContext.setValue("СРЕДНИЙЧЕК", totBay / totPeople);
    reportContext.setValue("БЕЗНАЛКОЛ", totBeznalQuan + " (" + Math.round(totBeznalQuan * 100 / totPeople) + "%)");
  }
}

