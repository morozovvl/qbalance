var fileName;
var templateFileName;
var agentName = "";
var firmId = 0;
var dir;
var agentDict;

var rowId;
var tovarId  = "";
var tovarName = "";
var tovarArticulOEM = "";
var tovarArticul = "";
var tovarUnit = "";
var tovarQuan = 0;
var tovarPrice = 0;
var tovarPrice1 = 0;
var tovarSum = 0;
var tovarUpack = 1;	// По умолчанию в упаковке 1 единица товара
var tovarNalich = "-";	// По умолчанию товара нет в наличии
var tovarProizv = "";
var tovarCountry = "";
var tovarPictureUrl = "";
var tovarDescription = "";

var colId;
var colName;
var colName1;
var colArticulOEM;
var colArticul;
var colUnit;
var colPrice;
var colPrice1;
var colUpack;
var colNalich;
var colProizv;
var colCountry;
var colPictureUrl;
var colDescription;
var sheetName = "";
var templateFound = false;
var ods;
var currentRow = 0;
var filterOk = true;
var procent = 0;
var row = 0;
var counter = 0;
var nalichCounter = 0;
var oldNalichCounter = 0;

scriptResult = false;				// По умолчанию будем считать, что скрипт не загружен

if (app.getScript().length > 0)			// Если в параметрах приложения задано выполнение этого скрипта
{
  fileName = app.getScriptParameter();	        // То имя файла с документами возьмем тоже из параметров
  if (fileName.length == 0)
    app.showMessageOnStatusBar("Файл с прайсом не указан.\n");		  
  templateFileName = app.getScriptParameter(1);	        // То имя файла с документами возьмем тоже из параметров
  if (templateFileName.length == 0)
    templateFileName = "шаблон.ods";
}
else if (form != 0)
  fileName = QFileDialog.getOpenFileName(form, "Откройте прайс", QDir.currentPath(), "Документ OpenOffice (*.ods);;Все файлы (*.*)");

if (fileName != "")
{    
  var file = new QFileInfo(fileName);
  var fileInfo = new QFileInfo(fileName);
  dir = fileInfo.absolutePath();
  if (file.suffix() == "ods")
  {
    ReadAgent();
    OdsFile(fileName);
//    if (!scriptResult)
//      app.sendSMS(app.getConst("ТелефонДляСлужебныхСМС"), "Прайс " + agentName + " " + fileInfo.fileName() + " не загружен.");
  }
}


function OdsFile(fileName)
{ // Функция читает файлы ods OpenOffice
	odsTemp = new OOXMLEngine();
	odsTemp.setShowError(false);			// Не показывать сообщение об ошибке загрузки шаблона

	// Откроем шаблон в этом же каталоге и прочитаем координаты начала данных	
	if (odsTemp.open(dir + "/" + templateFileName, true))
	{
	  rowId = odsTemp.row(odsTemp.getCellWithAnnotation("НАИМЕНОВАНИЕ"));
	  if (rowId >= 0)
	  {
		colId = odsTemp.column(odsTemp.getCellWithAnnotation("КОД"));
		colName = odsTemp.column(odsTemp.getCellWithAnnotation("НАИМЕНОВАНИЕ"));
		colName1 = odsTemp.column(odsTemp.getCellWithAnnotation("НАИМЕНОВАНИЕ1"));
		colArticulOEM = odsTemp.column(odsTemp.getCellWithAnnotation("АРТИКУЛОЕМ"));
		colArticul = odsTemp.column(odsTemp.getCellWithAnnotation("АРТИКУЛ"));
		colUnit = odsTemp.column(odsTemp.getCellWithAnnotation("ЕДИЗМ"));
		colPrice = odsTemp.column(odsTemp.getCellWithAnnotation("ЦЕНА"));
		colPrice1 = odsTemp.column(odsTemp.getCellWithAnnotation("ЦЕНА1"));
		colUpack = odsTemp.column(odsTemp.getCellWithAnnotation("УПАКОВКА"));
		colNalich = odsTemp.column(odsTemp.getCellWithAnnotation("НАЛИЧИЕ"));
		colProizv = odsTemp.column(odsTemp.getCellWithAnnotation("ПРОИЗВОДИТЕЛЬ"));
		colCountry = odsTemp.column(odsTemp.getCellWithAnnotation("СТРАНА"));
		colPictureUrl = odsTemp.column(odsTemp.getCellWithAnnotation("PHOTO_URL"));
		colDescription = odsTemp.column(odsTemp.getCellWithAnnotation("ОПИСАНИЕ"));
	  }
	  odsTemp.close();
	}
	else
	{
		evaluateScript(dir + "/шаблон.js");
	}
	if (firmId != 0)
	{
		ods = new OOXMLEngine();
		if (ods.open(fileName, sheetName, true))
		{
		  app.showMessageOnStatusBar("Открываем файл " + fileName + "\n");		  
		  var rowCount = 0;

		  // Начнем разбирать документ
		  var row = rowId;
		  var rowCount = ods.rowCount();
		  db.exec("DELETE FROM last_price;");
		  exitKeyPressed = false;
		
		  while (row <= ods.rowCount() && !exitKeyPressed)
		  {
			  tovarId  = "";
			  tovarName = "";
			  tovarArticulOEM = "";
			  tovarArticul = "";
			  tovarUnit = "";
			  tovarQuan = 0;
			  tovarPrice = 0;
			  tovarPrice1 = 0;
			  tovarSum = 0;
			  tovarUpack = 1;	// По умолчанию в упаковке 1 единица товара
			  tovarNalich = "-";	// По умолчанию товара нет в наличии
			  tovarProizv = "";
			  tovarCountry = "";
			  tovarPictureUrl = "";
			  tovarDescription = "";
			  if (colId >= 0)
			  {
				  tovarId = FindFieldData(row, colId, "КОД", false);
				  tovarId = tovarId.replace(/^0+/, "");
			  }
			  if (colName >= 0)
			  {
				  tovarName = FindFieldData(row, colName, "НАИМЕНОВАНИЕ", true);
				  if (colName1 >= 0)
				  {
				    tovarName = tovarName + " " + FindFieldData(row, colName1, "НАИМЕНОВАНИЕ1", true);
				  }
				  
//				  tovarName = tovarName.replace(/(\h.+)/g, "");
				  tovarName = tovarName.replace(/'/g, "''").substring(0, 100);
				  if (firmId == 420)
				  {	// Специальная обработка прайса "ТИС-Восток" от ихней хуйни в наименованиях
				    tovarName = tovarName.replace(/\xA0/g, String.fromCharCode(32));
				    tovarName = tovarName.replace(/[А-Яа-я]a/g, replaceLatA);
				    tovarName = tovarName.replace(/a[А-Яа-я]/g, replaceLatA);
				  }
			  }
			  if (colArticulOEM >= 0)
			  {
				  tovarArticulOEM = FindFieldData(row, colArticulOEM, "АРТИКУЛОЕМ", false);
				  tovarArticulOEM = tovarArticulOEM.replace(/'/g, "''").substring(0, 50);
			  }
			  if (colArticul >= 0)
			  {
				  tovarArticul = FindFieldData(row, colArticul, "АРТИКУЛ", false);
				  tovarArticul = tovarArticul.replace(/'/g, "''").substring(0, 50);
			  }
			  if (colUnit >= 0)
			  {
				  tovarUnit = FindFieldData(row, colUnit, "ЕДИЗМ", false);
			  }
			  if (colUpack >= 0)
			  {
				  tovarUpack = FindFieldData(row, colUpack, "УПАКОВКА", false);
				  tovarUpack = tovarUpack.replace(/\s+/g, "").replace(",", ".");
				  if (tovarUpack === "")
					  tovarUpack = 1;
			  }
			  if (colNalich >= 0)
			  {
				  tovarNalich = FindFieldData(row, colNalich, "НАЛИЧИЕ", false);
				  tovarNalich = tovarNalich.substring(0, 1);
				  if (tovarNalich == "")
					  tovarNalich = "+";
				  else if (tovarNalich == "0")
					  tovarNalich = "-";
				  else if (tovarNalich == "1")
					  tovarNalich = "+";
				  else if (tovarNalich == "з")
					  tovarNalich = "-";
				  else if (tovarNalich == "н")
					  tovarNalich = "-";
				  else if (tovarNalich == "Нет на складе")
					  tovarNalich = "-";
				  else if (tovarNalich == "-")
					  tovarNalich = "-";
				  else
					  tovarNalich = "+";
			  }
			  else		// Если столбец с наличием не указан, то будем считать, что товар есть в наличии
					  tovarNalich = "+";
			  if (colProizv >= 0)
			  {
				  tovarProizv = FindFieldData(row, colProizv, "ПРОИЗВОДИТЕЛЬ", false);
				  tovarProizv = tovarProizv.replace(/'/g, "''").substring(0, 50);
			  }
			  if (colCountry >= 0)
			  {
				  tovarCountry = FindFieldData(row, colCountry, "СТРАНА", false);
				  tovarCountry = tovarCountry.replace(/'/g, "''").substring(0, 50);
				  if (tovarCountry.length > 0 && tovarProizv != tovarCountry)
					  tovarProizv = tovarProizv + ", " + tovarCountry;
			  }
			  if (colPrice >= 0)
			  {
				  tovarPrice = FindFieldData(row, colPrice, "ЦЕНА", true);
				  tovarPrice = tovarPrice.replace(/\s+/g, "").replace(",", ".");
				  tovarPrice = tovarPrice * (1 + procent / 100);
			  }
			  if (colPrice1 >= 0)
			  {
				  tovarPrice1 = FindFieldData(row, colPrice1, "ЦЕНА1", true);
				  tovarPrice1 = tovarPrice1.replace(/\s+/g, "").replace(",", ".");
				  tovarPrice1 = tovarPrice1 * (1 + procent / 100);
			  }
			
			  var res = parseFloat(tovarPrice);
			  if (isNaN(res))
			    tovarPrice = tovarPrice1;
				  if (colPictureUrl >= 0)
			  {
				  tovarPictureUrl = FindFieldData(row, colPictureUrl, "PHOTO_URL", false);
			  }
			  if (colDescription >= 0)
			  {
				  tovarDescription = FindFieldData(row, colPictureUrl, "ОПИСАНИЕ", false);
			  }
			  
			  // Пропустим запись через локальный фильтр прайса
			  filterOk = true;
			  currentRow = row;
			  evaluateScript(dir + "/filter.js");
			  if (filterOk && tovarName.match(/[А-Яа-я]+/) && tovarPrice > 0 && !exitKeyPressed)	// Если наименование не пустое и содержит буквы, а количество и сумма больше 0
			  {							// Значит нам попалась строка с описанием позиции товара
				  templateFound = true;
				  tovarId = tovarId.substring(0, 50);
				  tovarArticulOEM = tovarArticulOEM.substring(0, 50);
				  tovarProizv = tovarProizv.substring(0, 50);
				  tovarArticul = tovarArticul.substring(0, 50);
				  var command = "INSERT INTO last_price (ID_FIRM, ID, NAME, KATALOG, ARTICUL, UNIT, PRICE, UPAK, NALICH, PROIZV, PHOTO_URL, DESCRIPTION) values (" + firmId + ",'" + tovarId + "','" + tovarName + "','" + tovarArticulOEM + "','" + tovarArticul + "','" + tovarUnit + "'," + tovarPrice + "," + tovarUpack + ",'" + tovarNalich + "', '" + tovarProizv + "', '" + tovarPictureUrl + "', '" + tovarDescription + "');";
				  db.appendCommand(command);
//				  print(command);
//				  db.exec(command);
				  app.showMessageOnStatusBar("Загружено " + Math.round(row * 100 / rowCount) + "%");
				  counter++;
			  }
			
			  row++;
		  }
		  if (!exitKeyPressed)
		  {
		    if (counter > 0)
		    {
		      app.showMessageOnStatusBar("Сохраним прайс в базе данных...\n");
		      if (db.execCommands())
		      {
			oldNalichCounter = db.getValue("SELECT COUNT(*) FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND НАЛИЧИЕ = '+';");
			nalichCounter = db.getValue("SELECT sp_updateprice();");
			oldNalichCounter = nalichCounter - oldNalichCounter;
			app.debug(0, "Прайс " + agentName + " " + fileName + " загружен.");
		      }
		      app.showMessageOnStatusBar("");
		    
		      // Проанализируем прайс на предмет изменений
		      var historyQuery = db.execQuery("SELECT t.КОД, t.ИМЯ, s.СТАРОЕЗНАЧЕНИЕ, s.НОВОЕЗНАЧЕНИЕ, s.ДАТАВРЕМЯ \
							FROM (SELECT p.КОД_ТОВАР, i.СТАРОЕЗНАЧЕНИЕ, i.НОВОЕЗНАЧЕНИЕ, i.ДАТАВРЕМЯ \
							FROM история i \
							  INNER JOIN прайс p ON i.ТАБЛИЦА = 'прайс' AND i.КОДСТРОКИ = p.КОД AND p.КОД_ТОВАР > 0 AND p.КОД_ФИРМЫ = " + firmId + "\
						        WHERE i.ДАТАВРЕМЯ::date = current_date) s \
							  INNER JOIN товар t ON s.КОД_ТОВАР = t.КОД \
							ORDER BY ИМЯ, s.ДАТАВРЕМЯ ASC;");
		      if (historyQuery.first())
		      {
				  app.showMessageOnStatusBar("\n");
				  app.showMessageOnStatusBar("Произошли следующие изменения в соответствиях:\n");
				  var oldId = 0;
				  do
				  {
					  var historyRecord = historyQuery.record();
					  var oldValue = historyRecord.value("СТАРОЕЗНАЧЕНИЕ").trim();
					  var newValue = historyRecord.value("НОВОЕЗНАЧЕНИЕ").trim();
					  if (oldId != historyRecord.value("КОД"))
					  {
					    app.showMessageOnStatusBar("Для позиции: " + historyRecord.value("КОД") + " " + historyRecord.value("ИМЯ") + "\n");
					    oldId = historyRecord.value("КОД");
					  }
					  app.showMessageOnStatusBar("      Было: " + oldValue + "\n");
					  app.showMessageOnStatusBar("     Стало: " + newValue + "\n");
				  } while (historyQuery.next());     
				  app.showMessageOnStatusBar("\n");
		      }
		      
		      app.showMessageOnStatusBar("Всего " + db.getValue("SELECT COUNT(*) FROM last_price;") + " записей.\n");
		      var nalichStr = '';
		      if (oldNalichCounter > 0)
			nalichStr = " ( +" + oldNalichCounter + " )";
		      else if (oldNalichCounter < 0)
			nalichStr = " ( " + oldNalichCounter + " )";
		      else
			nalichStr = "";
		      app.showMessageOnStatusBar("Из них в наличии " + nalichCounter + " позиций" + nalichStr + ".\n");
		      
		      db.exec("DELETE FROM история WHERE ТАБЛИЦА = 'прайс' AND КОДСТРОКИ IN (SELECT КОД FROM прайс WHERE COALESCE(КОД_ТОВАР, 0) = 0 AND КОД_ФИРМЫ = " + firmId + ");");
		    }
		    else
		      app.showMessageOnStatusBar("Не обновлено ни одной позиции.\n");
		    scriptResult = true;
		  }
		  ods.close();
		}
		else
		{
		  app.showMessageOnStatusBar("Не удалось открыть файл " + fileName + "\n");
		}
	}
}


function replaceLatA(str, exp)
{
  return str.replace("a", "а");		// Заменим латинскую букву на аналогичную русскую (для ТИС-Восток)
}

function FindFieldData(row, column, name, exact)
{
  var result = ods.getCellText(row, column);
  if ((!result || result.length == 0) && exact && row == rowId)		// Данные для обязательного поля не найдены в строке первой позиции прайса
  {
    var errorString = "Прайс отличается от шаблона. Не найдено поле <" + name + "> в строке " + row + ". Продолжим работу.";
    if (form != 0)
      QMessageBox.warning(form, "Прайс", errorString);
    else
    {
      app.showMessageOnStatusBar(errorString + "\n");
      debug(errorString);
    }
    if (templateFound)
      exitKeyPressed = true;
  }
  return result;
}


function ReadAgent()
{
		evaluateScript(dir + "/readFirmId.js");
		agentDict = getDictionary("фирмы");	// Найдем такого контрагента в нашей БД
		if (agentName.length > 0)
		{
    			agentDict.query("фирмы.ИМЯ ILIKE '%" + agentName + "%'");
            		firmId = agentDict.getId(0);
		}
		if (firmId > 0)
		{
		  agentDict.setId(firmId);
		}
		if (firmId == 0)
		{
			var formTitle = agentDict.getFormTitle();	// Сохраним старый заголовок окна
			agentDict.setFormTitle("Поставщик не указан. Укажите, пожалуйста, поставщика");		// Установим в заголовке окна подсказку для пользователя
			agentDict.exec();
			agentDict.setFormTitle(formTitle);		// Вернем прежнее название окна
			if (agentDict.isFormSelected())		// если пользователь нажал кнопку Ok
				firmId = agentDict.getId();
		}	  
		if (firmId == 0)
		  app.showMessageOnStatusBar("Контрагент не указан.\n");		  
		else
		{
		  procent = agentDict.getValue("ПРОЦЕНТ", 0);	// Процент наценки на прайс, чтобы получить точную конечную цену
		}
}


function DelOldPrice()
{
  app.showMessageOnStatusBar("Удаление старых данных из прайса " + agentName + "...");
  var command = "DELETE FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND ДАТА < current_date - " + app.getConst("АктуальностьПрайсов") + ";";
  db.exec(command);
}
