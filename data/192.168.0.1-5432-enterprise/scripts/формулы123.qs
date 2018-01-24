var firmId = 0;
var docNumber = "";
var docDate = "";
var agentName = "";
var odsTemp;
var ods;
var rowId;

var exitKeyPressed;	// Флаг нажатия кнопки, прерывающей загрузку документа 

var colId;
var colName;
var colArticul;
var colUnit;
var colQuan;
var colPrice;
var colSum;
var colProizv;

var nomDict;
var nomForm;
var priceDict;
var setDict;
var agentDict;

var url;
var id;
var priceId = 0;
var nomPrice;
var newPosition = false;
var nomId = 0;
var nomName = "";
var nomQuan = 0;
var pricePrice = 0;
var automatedInput = false;
var zakazDocs = [];


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
	form.getButtonLoad().show();		// Включим кнопку "Загрузить документ" на форме
	table.setPhotoNameField("ТОВАР__ИМЯ");
	table.setPhotoIdField("ТОВАР__КОД");
	table.setPhotoEnabled(true);
	table.setPhotoPath(db.getDictionaryPhotoPath("товар"));

	priceDict = getDictionary("прайс");
	agentDict = getDictionary("организации");
	priceDict.setPhotoEnabled(true);
	
	// Заменим форму по умолчанию на новую форму
	nomDict = getDictionary("товар");
	nomDict.setForm("товар2");
	nomForm = nomDict.getFormWidget();
	nomForm.findChild("picturePrice").setVisible(false);
	nomForm.findChild("labelPrice").setVisible(false);
	setDict = getDictionary("набор402");
	getDictionary("документы3").setExact(false);
	form.addQueryMenuAction("__на_основании_заказа__", "Добавить поступление на основании заказа");
}


function EventBeforeShowForm()
{
	automatedInput = false;
	app.clearPrintArrays();
}


function EventBeforeHideForm()
{
    if (!automatedInput)
	printReports();	// Если накладная вводилась вручную, то покажем отчет при выходе
    if (zakazDocs.length > 0)
    {
      var exitMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Если не будет больше накладных от этого поставщика, то следует закрыть его заказ(ы). Закрыть?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
     if (exitMsg.exec() == QMessageBox.Yes)
     {
       for (var i = 0; i < zakazDocs.length; i++) 
       {
	  var number = db.getValue("SELECT НОМЕР FROM документы WHERE КОД = " + zakazDocs[i]);
	  db.exec("UPDATE докатрибуты129 SET ЗАКРЫТ = TRUE WHERE КОД = " + zakazDocs[i]);
	db.exec("UPDATE заявка SET КОД_ДОКУМЕНТЫ129 = 0 WHERE КОД_ДОКУМЕНТЫ129 = " + zakazDocs[i]);	
	  app.printToArray("закрытыезаказы", "Закрыт заказ № " + number);
	  sendSMS(zakazDocs[i]);
       }
       zakazDocs = [];
     }
    }
}


function EventBeforeAddString()
{
	automatedInput = false;
	var result = WriteTovar();
	return result;
}


function EventImport(form)
{ // Событие происходит при нажатии кнопки <Загрузить документ>
  if (getDictionary("организации").getId() > 0)
  {
    app.setDirName("GoodsIncomeDocDir");
    var fileName = app.getOpenFileName(form, "Откройте документ с приходом товара", "", "Документ OpenOffice(*.ods);; Документ CommerceML(*.xml)");
    if (fileName != "")
    {    
	automatedInput = true;
	var file = new QFileInfo(fileName);
	if (file.suffix() == "ods")
	{
		app.clearPrintArrays();
		document.saveChanges();
		OdsFile(fileName);
		printReports();
		ShowDebt();
	}
	if (file.suffix() == "xml")
	{
		XmlFile(fileName);
		ShowDebt();
	}
    }
  }
  else
    QMessageBox.warning(form, "Документ", "Сначала определите контрагента.");
}


function prepReports()
{
  if (agentName.length == 0)
	agentName = agentDict.getName();
    
  if (app.printArrayCount("заголовок") == 0)
  {
  	app.printToArray("заголовок", "");
  	app.printToArray("заголовок", "Приход товара от <" + agentName + "> по накладной № " + document.getNumber() + " от " + document.getDate());
  	app.printToArray("заголовок", "------------------------------------------");
  }
  var quanPrice = priceDict.getValue("КОЛ_ПРАЙС");
  var quanTovar = priceDict.getValue("КОЛ_ТОВАР");
  var quan = nomQuan * quanTovar / quanPrice;
  if (pricePrice != nomPrice)
  {
    var proc = Math.round(1000 *  (pricePrice - nomPrice) / nomPrice) / 10;
    if (isFinite(proc))
    {
      if (proc < 0)
	app.printToArray("ценыповысились", "Цена повысилась на " + (- proc) + "% --- " + nomName);
      if (proc > 0)
	app.printToArray("ценыпонизились", "Цена понизилась на " + proc + "% --- " + nomName);
    }
  }
// Проверим, не превышает ли остаток норму запаса, чтобы избежать накопления запасов
  var ostRec = db.execQuery("SELECT SUM(КОНКОЛ) FROM сальдо WHERE СЧЕТ = '411' AND КОД IN (SELECT КОД FROM набор1 WHERE КОД_ТОВАР = " + nomId + " AND КОД_АДРЕС NOT IN (SELECT КОД FROM адрес WHERE ИМЯ LIKE 'Брак'));");
  if (ostRec.first())
  {
    var ost = 0;
    var zap = 0;
    ost = parseInt(ostRec.record().value(0));
    zap = parseInt(nomDict.getValue("ЗАПАС"));
    if (zap > 0)
    {
      if (ost + parseInt(quan) > zap)
     {
	app.printToArray("запас", "Превышена норма запаса: <" + nomName + ">. Запас - " + zap + ", остаток - " + ost + ", поступило - " + quan);
      }
    }
    else
    {
      if (newPosition)
	app.printToArray("запас1", "Новая позиция: <" + nomName + ">. Поступило - " + quan);
      else
	app.printToArray("запас2", "НЕ ДОЛЖНА БЫЛА БЫТЬ ЗАКАЗАНА: <" + nomName + ">. Поступило - " + quan);
    }
  }
// Проверим, нет ли этой позиции в неразобранном товаре
  var ostRec = db.execQuery("SELECT SUM(КОНКОЛ) FROM сальдо WHERE СЧЕТ = '402' AND КОД IN (SELECT КОД FROM набор402 WHERE КОД_ТОВАР = " + nomId + " AND КОД_ДОКУМЕНТЫ123 <> " + documents.getId() + ");");
  if (ostRec.first())
  {
    var ost = 0;
    ost = parseInt(ostRec.record().value(0));
    if (ost > 0)
    {
      app.printToArray("запас3", "В неразобранном товаре уже имеется позиция: <" + nomName + "> в количестве " + ost + ". ВОЗМОЖНА ОШИБКА В ТАБЛИЦЕ СООТВЕТСТВИЙ!");
    }
  }
}


function printReports()
{
  app.printArray("заголовок");
  app.printArray("запас");
  app.printArray(" ");
  app.printArray("запас1");
  app.printArray(" ");
//  app.printArray("запас2");
//  app.printArray(" ");
  app.printArray("запас3");
  app.printArray(" ");
  app.printArray("ценыповысились");
  app.printArray(" ");
  app.printArray("ценыпонизились");
  app.printArray(" ");
  app.printArray("новыепозиции");
  app.printArray(" ");
  app.printArray("нетзаказа");
  app.printArray(" ");
  app.printArray("закрытыезаказы");
  app.printArray(" ");
}


function OdsFile(fileName)
{ // Функция читает файлы ods OpenOffice
	var fileInfo = new QFileInfo(fileName);
	var dir = fileInfo.absolutePath();
	odsTemp = new OOXMLEngine();
	ods = new OOXMLEngine();

	// Откроем шаблон в этом же каталоге и прочитаем координаты начала данных	
	odsTemp.open(dir + "/шаблон.ods", true);
	rowId = odsTemp.row(odsTemp.getCellWithAnnotation("НАИМЕНОВАНИЕ"));
	if (rowId >= 0)
	{
		ods.open(fileName);
		
//		agentName = odsTemp.getCellText(odsTemp.getCellWithAnnotation("КОНТРАГЕНТ"));	// Возьмем имя контрагента из шаблона

		docNumber = ods.getCellText(odsTemp.getCellWithAnnotation("НОМЕР"));
		docDate = ods.getCellText(odsTemp.getCellWithAnnotation("ДАТА"));
		colId = odsTemp.column(odsTemp.getCellWithAnnotation("КОД"));
		colName = odsTemp.column(odsTemp.getCellWithAnnotation("НАИМЕНОВАНИЕ"));
		colArticul = odsTemp.column(odsTemp.getCellWithAnnotation("АРТИКУЛ"));
		colProizv = odsTemp.column(odsTemp.getCellWithAnnotation("ПРОИЗВОДИТЕЛЬ"));
		colUnit = odsTemp.column(odsTemp.getCellWithAnnotation("ЕДИЗМ"));
		colQuan = odsTemp.column(odsTemp.getCellWithAnnotation("КОЛ"));
		colPrice = odsTemp.column(odsTemp.getCellWithAnnotation("ЦЕНА"));
		colSum = odsTemp.column(odsTemp.getCellWithAnnotation("СУММА"));

		var agentId = 0;
//		var agentDict = getDictionary("организации");	// Найдем такого контрагента в нашей БД
		
		evaluateScript(dir + "/readDocNumber.js");	// Запустим локальный скрипт, который вытащит из файла номер и дату документа

//		if (agentName.length > 0)
//            			agentDict.query("организации.ИМЯ ILIKE '%" + agentName + "%'");
         		agentId = agentDict.getId();
		if (agentId != 0)		// Если такого контрагента не существует в справочнике
		{
			agentName = agentDict.getName();

			if (docNumber.length > 0)
				document.setNumber(docNumber);
			if (docDate.length > 0)
	            			document.setDate(docDate);

			agentDict.setId(agentId);
            			document.showParameterText("организации");
	    		EventParametersChanged();
			var firmDict = getDictionary("фирмы");
			firmId = agentDict.getValue("КОД_ФИРМЫ");
			if (firmId == 0)
			{
				var formTitle = firmDict.getFormTitle();	// Сохраним старый заголовок окна
				firmDict.setFormTitle("Поставщик не указан. Укажите, пожалуйста, поставщика");		// Установим в заголовке окна подсказку для пользователя
    				firmDict.exec();
    				firmDict.setFormTitle(formTitle);		// Вернем прежнее название окна
			}
			else
			{
				firmDict.setId(firmId);
    				firmDict.exec();
			}
			if (firmDict.isFormSelected())		// если пользователь нажал кнопку Ok
    			{
				firmId = firmDict.getId();
				db.exec("UPDATE организации SET КОД_ФИРМЫ = " + firmId + " WHERE КОД = " + agentId + ";");
			}
			var rowCount = 0;

			// Посчитаем, сколько всего будет записей в документе
			var row = rowId;
			while (!ods.getCell(row, colName).isNull())
			{
				rowCount++;
				row++;
			}

			// Начнем разбирать документ
			row = rowId;
			var i = 1; 
			exitKeyPressed = false;
			while (!ods.getCell(row, colName).isNull() && !exitKeyPressed)
			{
				var tovarId  = "";
				var tovarName = "";
				var tovarArticul = "";
				var tovarProizv = "";
				var tovarUnit = "";
				var tovarQuan = 0;
				var tovarPrice = 0;
				var tovarSum = 0;
				if (colId >= 0)
				{
					tovarId = findFieldData(row, colId, "КОД", false);
//					tovarId = ods.getCellText(row, colId);
				}
				if (colName >= 0)
				{
					tovarName = findFieldData(row, colName, "НАИМЕНОВАНИЕ", false);
//					tovarName = tovarName.replace("'", "\'");
//					tovarName = tovarName.replace("\\", "\\\\");
				}
				if (colArticul >= 0)
				{
					tovarArticul = findFieldData(row, colArticul, "АРТИКУЛ", false);
				}
				if (colProizv >= 0)
				{
					tovarProizv = findFieldData(row, colProizv, "ПРОИЗВОДИТЕЛЬ", false);
				}
				if (colUnit >= 0)
				{
					tovarUnit = findFieldData(row, colUnit, "ЕДИЗМ", false);
				}
				if (colQuan >= 0)
				{
					tovarQuan = parseInt(findFieldData(row, colQuan, "КОЛ", false));
				}
				if (colPrice >= 0 && tovarQuan > 0)
				{
					tovarPrice = findFieldData(row, colPrice, "ЦЕНА", false);
				}
				if (colSum >= 0 && tovarQuan > 0)
				{
					tovarSum = findFieldData(row, colSum, "СУММА", false);
				}
				if (tovarName.match(/[А-Яа-я]+/) && tovarQuan > 0 && tovarSum > 0 && !exitKeyPressed)	// Если наименование не пустое и содержит буквы, а количество и сумма больше 0
				{	
					// Значит нам попалась строка с описанием позиции товара
					tovarPrice = tovarSum / tovarQuan;
					nomPrice = tovarPrice;
					nomQuan = tovarQuan;
					WriteTovar(tovarId, tovarName, tovarArticul, tovarProizv, tovarUnit, tovarQuan, tovarSum, docDate);
                                 				app.showMessageOnStatusBar("Загружено " + Math.round(i * 100 / rowCount)+ "%");	
				}
				i++;
				row++;
			}
		        	document.query(); 	// Обновим документ
             			document.calcItog();	// Подсчитаем ито по документу
		        document.saveChanges();
		        if (row == rowId)
  		        	app.showMessageOnStatusBar("Не загружено ни одной позиции. Вероятно документ пустой.");		
		        else
			{
				if (!exitKeyPressed)
  		             			app.showMessageOnStatusBar("Документ загружен полностью.");		
			}
		}
		else
            			QMessageBox.warning(form, "Документ", "Не определен контрагент.");

		ods.close();
	}
	odsTemp.close();
}


function findFieldData(row, column, name, exact)
{
	var result = ods.getCellText(row, column);
	if ((!result || result.length == 0) && exact && row == rowId)		// Данные для обязательного поля не найдены в строке первой позиции прайса
	{
            		QMessageBox.warning(form, "Документ", "Документ отличается от шаблона. Не найдено поле <" + name + ">.");
		exitKeyPressed = true;
	}
	return result;
}


function XmlFile(fileName)
{  // Функция производит чтение и разбор файлов CommerceML
    var file = new QFile(fileName);
    if (file.open(QIODevice.OpenMode(QIODevice.ReadOnly, QIODevice.Text))) 
    {
      var doc = new QDomDocument();
      if (doc.setContent(file))
      {
        if (doc.elementsByTagName("ХозОперация").at(0).toElement().text() == "Отпуск товара")	// Если это документ на отгрузку товара
        {
          docNumber = doc.elementsByTagName("Номер").at(0).toElement().text();
          docDate = doc.elementsByTagName("Дата").at(0).toElement().text();
          var agentName = "";
          var agentFullName = "";
          var agentAddress = "";
          var agentINN = "";
          // Найдем в документе реквизиты контрагента-продавца
          var agents = doc.elementsByTagName("Контрагент");
          for (var i = 0; i < agents.count(); i++)
          {
            if (agents.at(i).firstChildElement("Роль").text() == "Продавец")
            {
              agentName = agents.at(i).firstChildElement("Наименование").text();
              agentFullName = agents.at(i).firstChildElement("ОфициальноеНаименование").text();
              agentAddress = agents.at(i).namedItem("ЮридическийАдрес").namedItem("Представление").toElement().text();
	      agentINN = agents.at(i).firstChildElement("ИНН").text();
              break;
            }
          }		
          if (agentName != "")	// Если указан контрагент-продавец
          {
            if (agentFullName == "")
              agentFullName = agentName;
            document.setNumber(docNumber);
            document.setDate(docDate, Qt.ISODate);
            var agentDict = getDictionary("организации");	// Найдем такого контрагента в нашей БД
            agentDict.query("организации.ИНН LIKE '" + agentINN + "%'");
            var agentId = agentDict.getId(0);
            if (agentId != 0)		// Если такого контрагента не существует в справочнике
            {
	      // Сделаем наименование контрагента-продавца видимым на форме документа
	      agentDict.setId(agentId);
	      document.showParameterText("организации");
	      EventParametersChanged();
	      var firmDict = getDictionary("фирмы");
	      firmId = agentDict.getValue("КОД_ФИРМЫ");	// Получим код фирмы отгрузки контрагента
	      if (firmId == 0)
	      {
		var formTitle = firmDict.getFormTitle();	// Сохраним старый заголовок окна
		firmDict.setFormTitle("Поставщик не указан. Укажите, пожалуйста, поставщика");		// Установим в заголовке окна подсказку для пользователя
    		firmDict.exec();
    		firmDict.setFormTitle(formTitle);		// Вернем прежнее название окна
	      }
	      else
	     {
		firmDict.setId(firmId);
    		firmDict.exec();
	      }
	      if (firmDict.isFormSelected())		// если пользователь нажал кнопку Ok
    	     {
	       firmId = firmDict.getId();
	       db.exec("UPDATE организации SET КОД_ФИРМЫ = " + firmId + " WHERE КОД = " + agentId + ";");
	      }
	      // Переберем все позиции в накладной
	      var tovar = doc.elementsByTagName("Товар");
	      exitKeyPressed = false;	// Пока что не была нажата кнопка прерывания процесса загрузки
	      // Т.к. далее идет циклическая обработка строк, заготовим некоторые команды для сервера, чтобы их обработка происходила на сервере быстрее
	      var row = 0;
	      for (var i = 0; i < tovar.count() && !exitKeyPressed; i++)
	      {
		var tovarId = tovar.at(i).firstChildElement("Ид").text();
		var tovarName = tovar.at(i).firstChildElement("Наименование").text();
		var tovarArticul = tovar.at(i).firstChildElement("Артикул").text();
		var tovarUnit = tovar.at(i).firstChildElement("Единица").text();
		var tovarQuan = tovar.at(i).firstChildElement("Количество").text();
		var tovarPrice = tovar.at(i).firstChildElement("ЦенаЗаЕдиницу").text();
		var tovarSum = tovar.at(i).firstChildElement("Сумма").text();
		var tovarProizv = "";
		WriteTovar(tovarId, tovarName, tovarArticul, tovarProizv, tovarUnit, tovarQuan, tovarPrice, tovarSum, docDate);
		app.showMessageOnStatusBar("Загружено " + Math.round(i * 100 / tovar.count())+ "%");
		row++;
	      }
	      document.query(); 	// Обновим документ
              	      document.calcItog();	// Подсчитаем ито по документу
	      document.saveChanges();
	      if (row == 0)
		app.showMessageOnStatusBar("Не загружено ни одной позиции. Вероятно документ пустой.");		
	      else
	      {
		if (!exitKeyPressed)
		  app.showMessageOnStatusBar("Документ загружен полностью.");		
	      }
	    }
	    else
	      QMessageBox.warning(form, "Документ CommerceML", "Не найден контрагент c ИНН ", agentINN);
          }
          else
            QMessageBox.warning(form, "Документ CommerceML", "Не найден контрагент - продавец");
        }
        else
          QMessageBox.warning(form, "Документ CommerceML", "Это не документ на отгрузку товара");
      }
      else
        QMessageBox.warning(form, "Документ CommerceML", "Не удалось разобрать документ");
      file.close();
    }
    else
      QMessageBox.warning(form, "Документ CommerceML", "Не могу открыть файл " + fileName + ":\n" + file.errorString());
}


function WriteTovar(id, name, articul, proizv, unit, quan, sum, date)
// Запишем позицию в документ, предварительно выяснив соответствие в таблице прайсов
{
  var result = true;
  var addNewPosition = false;
  nomQuan = quan;
  pricePrice = nomPrice;
  rowPrice = nomPrice;
  nomPrice = 0;
  nomId = 0;
  if (date == '')
  	date = (new Date).toISOString().substr(0,10);

  if (automatedInput)	// Если указан поставщик, значит товар приходуется автоматически
  {
    var priceRec;
    id = id.replace(/^[0]+/g,"");	// удалим первые 0
    id = id.replace(/\s+/g, "");	// удалим пробелы
    name = name.replace("'", "''");
    
    var command = "SELECT * FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND ";
    if (id.length > 0)
      command = command + "КОДВПРАЙСЕ = '" + id + "';";
    else
      command = command + "ИМЯ = '" + name + "';";

    priceRec = db.execQuery(command);

    if (priceRec.first())
    {
      nomId = priceRec.record().value("КОД_ТОВАР");	// Посмотрим, какой нашей позиции соответствует это название в прайсе
      priceId = priceRec.record().value("КОД");
      name = priceRec.record().value("ИМЯ");
      name = name.replace("'", "''");    
      articul = priceRec.record().value("АРТИКУЛ");
      proizv = priceRec.record().value("ПРОИЗВОДИТЕЛЬ");
      var quan_price = priceRec.record().value("КОЛ_ПРАЙС");
      var quan_tovar = priceRec.record().value("КОЛ_ТОВАР");
      pricePrice = priceRec.record().value("МИНЦЕНА");
      if (pricePrice != rowPrice)
      {
	if (priceId > 0)
	  db.exec("UPDATE прайс SET МИНЦЕНА = " + rowPrice + " WHERE КОД = " + priceId + ";");
       }
      pricePrice = pricePrice * quan_price / quan_tovar;
      if (quan_price > 0)
      {
	quan = quan * quan_tovar / quan_price;
	if (quan > 0)
	  nomPrice = sum / quan;
      }
    }
    else
      addNewPosition = true;
  }
  else
  {
    nomDict.setMustShow(false);
    priceDict.setMustShow(false);
    priceDict.exec();
    if (priceDict.isFormSelected())
    {
      if (priceDict.getRowCount() > 0)
      {
	nomId = priceDict.getValue("КОД_ТОВАР");	// Посмотрим, какой нашей позиции соответствует это название в прайсе
	priceId = priceDict.getValue("КОД");
	name = priceDict.getValue("ИМЯ");
	name = name.replace("'", "''");    
	articul = priceDict.getValue("АРТИКУЛ");
	proizv = priceDict.getValue("ПРОИЗВОДИТЕЛЬ");
	var quan_price = priceDict.getValue("КОЛ_ПРАЙС");
	var quan_tovar = priceDict.getValue("КОЛ_ТОВАР");
	pricePrice = priceDict.getValue("МИНЦЕНА") * quan_price / quan_tovar;
	nomPrice = pricePrice;
      }
      else
	addNewPosition = true;
    }
  }
  if (nomId > 0)
    nomDict.setId(nomId);
  else  
  {
    var formTitle = nomDict.getFormTitle();
    if (name != undefined)
    {
      nomDict.setFormTitle("Укажите позицию аналогичную: " + name + " (" + articul + ") " + proizv);		// Установим в заголовке окна подсказку для пользователя
      nomDict.getForm().setParameter("товар", name);
    }
    nomDict.exec();
    if (name != undefined)
      nomDict.setFormTitle(formTitle);					// Вернем прежнее название окна
    if (nomDict.isFormSelected())	// если пользователь нажал кнопку Ok
    {
      nomId = nomDict.getId();
      if (addNewPosition)
      {
	db.exec("INSERT INTO прайс (КОДВПРАЙСЕ, ИМЯ, ШИФР_ПО_КАТАЛОГУ, ЕДИЗМ, МИНЦЕНА, КОД_ФИРМЫ, КОД_ТОВАР, ДАТА, НАЛИЧИЕ) VALUES ('" + id + "','" + name + "','" + articul + "','" + unit + "'," + rowPrice + "," + firmId + "," + nomId + ",'" + date + "', '+');");
	app.printToArray("новыепозиции", "Позиция <" + name + "> в прайсе не найдена. Была создана вновь.");
      }
      else
      {
	if (priceId > 0)
	  db.exec("UPDATE прайс SET КОД_ТОВАР = " + nomId + " WHERE КОД = " + priceId + ";");
      }
    }
    else
    {
/*	
	var exitMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Документ полностью не загружен. Прервать загрузку?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
	if (exitMsg.exec() == QMessageBox.Yes)
	  exitKeyPressed = true;
*/	
      result = false;
    }
  }

  document.prepareValue("P1__ЦЕНА", nomPrice);
  document.prepareValue("КОД_ТОВАР", nomId);
  if (priceId > 0)
  {
    document.prepareValue("ЦЕНА_В_ПРАЙСЕ", pricePrice);
    document.prepareValue("КОД_ПРАЙС", priceId);
  }
  if (automatedInput)
  {
    // Запишем кол-во, цену, сумму в проводку
    document.prepareValue("P1__КОЛ", quan);
    document.prepareValue("P1__СУММА", sum);
    nomDict.setId(nomId);
    // Сохраним проводку на сервере
    var row = document.appendDocString();
    if (priceId > 0)
    {
	// скопируем фотографию
	var toFileName = nomDict.getPhotoPath() + "/" + nomId + ".jpg";
	priceDict.getPhotoFile(toFileName);
    }
    // Запишем в заказы те позиции, которые пришли
    nomName = getValue("ТОВАР__ИМЯ");
    nomQuan = quan;
    WriteZakaz();
  }
  return result;
}


function WriteZakaz()
{
  var zakazRec;
  zakazRec = db.execQuery("SELECT КОДВПРАЙСЕ, КОЛ, ПОСТОЯННО FROM заявка WHERE КОД_ПРАЙС = " + priceId + ";");
	
  if (zakazRec.first())
  {
    var constantly = zakazRec.record().value("ПОСТОЯННО");
    var zakQuan = zakazRec.record().value("КОЛ");
    if (constantly)
      db.exec("UPDATE товар SET ЗАПАС=" + zakQuan + " WHERE КОД=" + nomId + ";");
    if (zakQuan > nomQuan)
      db.exec("UPDATE заявка SET КОЛ = " + (zakQuan - nomQuan) + " WHERE КОД_ПРАЙС = " + priceId + ";");
    else
      db.exec("DELETE FROM заявка WHERE КОД_ПРАЙС = " + priceId + ";");
  }	
  
  zakazRec = db.execQuery("SELECT * FROM vw_заказы WHERE КОД_ПРАЙС = " + priceId);
  if (zakazRec.first())
  {
    var docId = zakazRec.record().value("ДОККОД");
    var strNum = zakazRec.record().value("СТР");
    var docZakazId = zakazRec.record().value("КОДДОКЗАКАЗ");
    var strZakazId = zakazRec.record().value("СТРДОКЗАКАЗ");
    if (docZakazId > 0)
    {
      db.exec("UPDATE атрибуты3 SET ВЫПОЛНЕН = TRUE, ОТМЕНЕН = FALSE WHERE ДОККОД = " + docZakazId + " AND СТР = " + strZakazId);
      db.exec("UPDATE атрибуты3 SET ОТМЕНЕН = TRUE WHERE ДОККОД = " + docZakazId + " AND КОД_ФИРМЫ = " + firmId + " AND ВЫПОЛНЕН = FALSE");
      // Посчитаем не выполненные заказы
/*      
      var notProcessed = db.getValue("SELECT COUNT(*) FROM атрибуты3 WHERE ДОККОД = " + docZakazId + " AND NOT (ВЫПОЛНЕН OR ОТМЕНЕН);");
      if (notProcessed == 0)
      {
	db.exec("UPDATE докатрибуты3 SET ВЫПОЛНЕН = TRUE WHERE КОД = " + docZakazId);
      }
*/      
    }
    db.exec("UPDATE атрибуты129 SET ВЫПОЛНЕН = TRUE WHERE ДОККОД = " + docId + " AND СТР = " + strNum);
    if (zakazDocs.indexOf(docId) < 0)
	zakazDocs.push(docId);
  }
  else
    app.printToArray("нетзаказа", "Не найден заказ для позиции: <" + nomName + "> в количестве " + nomQuan);     
  prepReports();
}


function EventParametersChanged()
{
// Запишем наименование фирмы-поставщика в комментарии к документу
	agentName = agentDict.getName();
	documents.setValue("Комментарий", agentName);
	documents.setValue("КОД_ОРГАНИЗАЦИИ", getDictionary("организации").getId());
	ShowDebt();
}


function EventCalcTable()
{
	кол = getValue("P1__КОЛ");
	цена = getValue("P1__ЦЕНА");
	сумма = getValue("P1__СУММА");

	if (кол != 0 && !automatedInput)
	{
	  if (getCurrentFieldName() == "P1__СУММА") 
	    цена = сумма / кол;
	  else 
	    сумма = кол * цена;

	  nomPrice = цена;
	  nomQuan = кол;
	  pricePrice = getValue("ЦЕНА_В_ПРАЙСЕ");
	  nomName = getValue("ТОВАР__ИМЯ");
	  
	  WriteZakaz();
	}

	setValue("P1__КОЛ", кол);
	setValue("P1__ЦЕНА", цена);
	setValue("P1__СУММА", сумма);
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
	var tovar = document.getDictionary("товар");
	tovar.query("ШТРИХКОД = '" + barCode + "'");
	if (tovar.getRowCount() == 1)
	{
		var mustShow = tovar.isMustShow();
		tovar.setMustShow(false);
		document.add();
		tovar.setMustShow(mustShow);
	}
	else
		document.add();
}


function EventPreparePrintValues()
{ // Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа
   // Здесь Вы можете вставить свой код
  var процент = 0;
  var сумма_зак = 0;
  var итого_зак = 0;
  var сумма_реал = 0;
  var итого_реал = 0;
  var разница = 0;
  var итого_разница = 0;
  for (var i = 1; i <= table.getRowCount(); i++)
  {
     сумма_зак = getValue("P1__СУММА", i - 1);
     сумма_реал = getValue("P1__КОЛ", i - 1) * getValue("ТОВАР__ЦЕНА", i - 1);
     разница = сумма_реал - сумма_зак;
     процент = 100 * (getValue("ТОВАР__ЦЕНА", i - 1) - getValue("P1__ЦЕНА", i - 1)) / getValue("P1__ЦЕНА", i - 1);
     table.appendPrintValue("таблица" + i + ".ТОВАР__СУММА", сумма_реал);
     table.appendPrintValue("таблица" + i + ".ТОВАР__ПРОЦЕНТ", процент);
     table.appendPrintValue("таблица" + i + ".ТОВАР__РАЗНИЦА", разница);
     итого_зак = итого_зак + сумма_зак;
     итого_реал = итого_реал + сумма_реал;
     итого_разница = итого_разница + разница;
  }
  table.appendPrintValue("ИТОГО_ЗАКУП", итого_зак);
  table.appendPrintValue("ИТОГО_РЕАЛИЗАЦИЯ", итого_реал);
  table.appendPrintValue("ИТОГО_РАЗНИЦА", итого_разница);
  table.appendPrintValue("ИТОГО_РАЗНИЦА_ПРОЦЕНТ", 100 * итого_разница / итого_зак);
}


function sendSMS(docId)
{
  var command = "SELECT КОДДОКЗАКАЗ, SUM(CASE WHEN ВЫПОЛНЕН THEN 1 ELSE 0 END) AS ВЫПОЛНЕНО FROM атрибуты129 WHERE ДОККОД = " + docId + " AND КОДДОКЗАКАЗ > 0 GROUP BY КОДДОКЗАКАЗ;";
  var zakQuery = db.execQuery(command);
  if (zakQuery.first())
  {
	do
	{
		var zakRec = zakQuery.record();
		var message = "";
		var zakDocId = zakRec.value("КОДДОКЗАКАЗ");
		var zakPos = zakRec.value("ВЫПОЛНЕНО");
		command = "SELECT ТЕЛЕФОН FROM люди WHERE КОД = (SELECT ДБКОД FROM проводки WHERE ДОККОД = " + zakDocId + " AND ОПЕР = 3 AND НОМЕРОПЕР =  1 LIMIT 1);";
		var phone = db.getValue(command);
		if (zakPos > 0)
			message = "По вашему заказу ожидается поступление позиций: " + zakPos + ".";
		else
			message = "К сожалению, ваш заказ не будет выполнен."
		app.print("СМС на телефон " + phone + ": " + message);
//		app.sendSMS(phone, message);
	} while (zakQuery.next());

  }
}


function ShowDebt()
{
	var debtSum = 0;
	var contrAgentId =  getDictionary("организации").getId();
	if (contrAgentId > 0)
	{
		debtSum = db.getValue("SELECT COALESCE(КОНСАЛЬДО, 0) FROM сальдо WHERE СЧЕТ = '60' AND КОД = " + contrAgentId);
		if (typeof debtSum == 'undefined')
			debtSum = 0;
		debtSum = -debtSum;
	}
	table.getFormWidget().findChild("myNumericEditDebt").setText(debtSum);
}


function EventAfterShowForm()
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
	ShowDebt();
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
	if (id == "__на_основании_заказа__")
	{
		var docs = app.getDocuments(129);
		docs.exec();
		if (docs.isFormSelected())
		{
			var doc = docs.getDocument();
//			var docs3 = app.getDocuments(3);
			doc.query();
//			print(doc.getRowCount());
//			var firmDict = doc.getDictionary("фирмы");
			firmId = doc.getDictionary("фирмы").getId();
/*
			if (firmId == 0)
			{
				var formTitle = firmDict.getFormTitle();	// Сохраним старый заголовок окна
				firmDict.setFormTitle("Поставщик не указан. Укажите, пожалуйста, поставщика");		// Установим в заголовке окна подсказку для пользователя
    				firmDict.exec();
    				firmDict.setFormTitle(formTitle);		// Вернем прежнее название окна
			}
			else
			{
				firmDict.setId(firmId);
    				firmDict.exec();
			}
*/
			var tovarDict = getDictionary("товар");
			var priceDict = getDictionary("прайс");
			var setDict = getDictionary("набор402");
			var orgDict = getDictionary("организации");
			var progress = ProgressDialog("Заполнение на основании заказа. Ожидайте...");
			progress.show();
			progress.setMaximum(doc.getRowCount());
			for (var rowCount = 0; rowCount < doc.getRowCount(); rowCount++)
			{
				doc.setCurrentRow(rowCount);
				progress.setValue(rowCount);
				
				if (!doc.getValue("ВЫПОЛНЕН"))
				{
					var tovarId = doc.getValue("ПРАЙС__КОДВПРАЙСЕ");
					var tovarName = doc.getValue("ПРАЙС__ИМЯ");
					var tovarArticul = doc.getValue("ПРАЙС__ШИФР_ПО_КАТАЛОГУ");
					var tovarProizv = doc.getValue("ПРАЙС__ПРОИЗВОДИТЕЛЬ");
					var tovarUnit = doc.getValue("ПРАЙС__ЕДИЗМ");
					var tovarQuan = doc.getValue("P1__КОЛ");
					var tovarPrice = doc.getValue("P1__ЦЕНА");
					var tovarSum = doc.getValue("P1__СУММА");
					WriteTovar(firmId, tovarId, tovarName, tovarArticul, tovarProizv, tovarUnit, tovarQuan, tovarPrice, tovarSum, docDate);
				}
				app.showMessageOnStatusBar("Загружено " + Math.round(rowCount * 100 / doc.getRowCount())+ "%");	
			}
			progress.hide();
		}
	}
}



