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
var agentDict;

var url;
var id;
var priceId = 0;
var priceName;
var price;
var priceInPrice;
var newPosition = false;
var nomId;
var nomPrice = 0;
var automatedInput = false;
var zakazDocs = [];
var headerPrinted = false;


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
	  prepareSMS(zakazDocs[i]);
       }
       zakazDocs = [];
     }
    }
}


function EventBeforeAddString()
{
	var result = false;
	newPosition = false;
	priceId = 0;
	priceName = "";
	nomId = 0;
	priceDict.setMustShow(false);
	priceDict.exec();
	if (priceDict.isFormSelected() && priceDict.getRowCount() > 0)
	{
	  priceId = priceDict.getId();
	  priceName = priceDict.getName();
	  WriteTovar(0, 0);
	}
	else
	{
		nomDict.exec();
		if (nomDict.isFormSelected())
		{
		    nomId = nomDict.getId();
		    document.prepareValue("КОД_ТОВАР", nomId);
		    nomDict.setMustShow(false);
		    result = true;
		}
	}
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


function prepReports(quan, price)
{
  if (agentName.length == 0)
	agentName = agentDict.getName();
    
  if (app.printArrayCount("заголовок") == 0)
  {
  	app.printToArray("заголовок", "");
  	app.printToArray("заголовок", "Приход товара от <" + agentName + "> по накладной № " + document.getNumber() + " от " + document.getDate());
  	app.printToArray("заголовок", "------------------------------------------");
	headerPrinted = false;
  }

  if (priceDict.getId() != priceId)
    priceDict.setId(priceId);
  
  if (nomDict.getId() != nomId)
    nomDict.setId(nomId);
  
  var nomName = nomDict.getName();
  
  var priceInPrice = priceDict.getValue("МИНЦЕНА");
  price = price * priceDict.getValue("КОЛ_ТОВАР") / priceDict.getValue("КОЛ_ПРАЙС");

  if (priceInPrice != price)
  {
    var proc = Math.round(1000 *  (priceInPrice - price) / price) / 10;
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
      if ((ost + quan) > zap)
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
  if (!headerPrinted)
  {
    if (app.printArrayCount("запас") > 0 ||
        app.printArrayCount("запас1") > 0 ||
        app.printArrayCount("запас2") > 0 ||
        app.printArrayCount("ценыповысились") > 0 ||
        app.printArrayCount("ценыпонизились") > 0 ||
        app.printArrayCount("новыепозиции") > 0 ||
        app.printArrayCount("нетзаказа") > 0 ||
        app.printArrayCount("закрытыезаказы") > 0)
    {
      app.printArray("заголовок");
      headerPrinted = true;
    }
  }
  app.printArray("запас");
  app.printArray(" ");
  app.printArray("запас1");
  app.printArray(" ");
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
		
		evaluateScript(dir + "/readDocNumber.js");	// Запустим локальный скрипт, который вытащит из файла номер и дату документа

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
					tovarId = tovarId.replace(/^[0]+/g,"");	// удалим первые 0
					tovarId = tovarId.replace(/\s+/g, "");	// удалим пробелы
					tovarName = tovarName.replace("'", "''");
					
					if (tovarId > 0)
					  priceDict.query("прайс.КОД_ФИРМЫ = " + firmId + " AND прайс.КОДВПРАЙСЕ = '" + tovarId + "'");
					else
					  priceDict.query("прайс.КОД_ФИРМЫ = " + firmId + " AND прайс.ИМЯ = '" + tovarName + "'");
					// Если такой позиции нет в прайсе, то добавим её
					if (priceDict.rowCount() == 0)
  					{
						priceDict.setId(db.getValue("INSERT INTO прайс (КОДВПРАЙСЕ, ИМЯ, ШИФР_ПО_КАТАЛОГУ, ЕДИЗМ, МИНЦЕНА, КОД_ФИРМЫ, ДАТА, НАЛИЧИЕ) VALUES ('" + tovarId + "','" + tovarName + "','" + tovarArticul + "','" + tovarUnit + "'," + tovarPrice + "," + firmId + ", current_date, '+') RETURNING КОД;"));
					}
					priceId = priceDict.getId();
					priceName = priceDict.getName();
					var result = WriteTovar(tovarQuan, tovarPrice);
					if (result.length > 0)
					  app.print(tovarId + " " + tovarName + ": " + result);
					else
					{
					  WriteZakaz(tovarName, tovarQuan);
					  prepReports(tovarQuan, tovarPrice);
					}
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
/*  
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
		WriteTovar(firmId, tovarId, tovarName, tovarArticul, tovarProizv, tovarUnit, tovarQuan, tovarPrice, tovarSum, docDate);
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
*/    
}


function WriteTovar(quan, price)
// Запишем позицию в документ, предварительно выяснив соответствие в таблице прайсов
{
  var result = "";
  newPosition = false;

  if (priceDict.getId() != priceId)
    priceDict.setId(priceId);
  
  if (priceDict.rowCount() == 1 || !automatedInput)
  {
    var priceArticul = priceDict.getValue("ШИФР_ПО_КАТАЛОГУ") + " " + priceDict.getValue("АРТИКУЛ");
    var priceProizv = priceDict.getValue("ПРОИЗВОДИТЕЛЬ");
    nomId = priceDict.getValue("КОД_ТОВАР");	// Посмотрим, какой нашей позиции соответствует это название в прайсе
    firmId = priceDict.getValue("КОД_ФИРМЫ");
    priceInPrice = priceDict.getValue("МИНЦЕНА") * priceDict.getValue("КОЛ_ПРАЙС") / priceDict.getValue("КОЛ_ТОВАР");
    quan = quan * priceDict.getValue("КОЛ_ТОВАР") / priceDict.getValue("КОЛ_ПРАЙС");
    price = price * priceDict.getValue("КОЛ_ПРАЙС") / priceDict.getValue("КОЛ_ТОВАР");
    if (price == 0 && priceInPrice != 0)
      price = priceInPrice;
    if (nomId == 0)			// Если мы не знаем, какой нашей позиции соотстветствует это наименование
    {					// тогда спросим это у пользователя
      var formTitle = nomDict.getFormTitle();
      nomDict.setFormTitle("Укажите позицию аналогичную: " + priceName + " (" + priceArticul + ") " + priceProizv);		// Установим в заголовке окна подсказку для пользователя
      nomDict.getForm().setParameter("товар", priceName);
      nomDict.exec();
      nomDict.setFormTitle(formTitle);					// Вернем прежнее название окна
      if (nomDict.isFormSelected())	// если пользователь нажал кнопку Ok
      {
	nomId = nomDict.getId();
	db.exec("UPDATE прайс SET КОД_ТОВАР = " + nomId + " WHERE КОД = " + priceId + ";");
	newPosition = true;
      }
    }
    else
      nomDict.setId(nomId);

    if (nomId != 0)
    {
      // Запишем кол-во, цену, сумму в проводку
      document.prepareValue("P1__КОЛ", quan);
      document.prepareValue("P1__ЦЕНА", price);
      document.prepareValue("P1__СУММА", quan * price);
      document.prepareValue("КОД_ПРАЙС", priceId);
      document.prepareValue("КОД_ТОВАР", nomId);
      document.prepareValue("ЦЕНА_В_ПРАЙСЕ", priceInPrice);
      // Сохраним проводку на сервере
      var row = document.appendDocString();
    
      // скопируем фотографию
      var toFileName = nomDict.getPhotoPath() + "/" + nomId + ".jpg";
      priceDict.getPhotoFile(toFileName);
    }
  }
  else if (priceDict.rowCount() > 1)
  {
    result = "В прайсе найдено больше одной позиции с таким кодом или наименованием";
  }
  else
  {
    result = "В прайсе не найдено позиций с таким кодом или наименованием";
  }
  return result;
}


function WriteZakaz(name, quan)
{
  var zakazRec = db.getRecord("SELECT * FROM vw_заказы WHERE КОД_ПРАЙС = " + priceId, 0);
  if (!zakazRec.isEmpty())
  {
    var docId = zakazRec.value("ДОККОД");
    var strNum = zakazRec.value("СТР");
    var docZakazId = zakazRec.value("КОДДОКЗАКАЗ");
    var strZakazId = zakazRec.value("СТРДОКЗАКАЗ");
    var zakazId = zakazRec.value("КОДЗАКАЗ");
    if (docZakazId > 0)
    {
      var command = "UPDATE набор402 SET КОД_ДОКУМЕНТЫ3 = " + docZakazId + " WHERE КОД = " + document.getValue("P1__ДБКОД");
      print(command);
      db.exec(command);
      command = "UPDATE атрибуты3 SET ВЫПОЛНЕН = TRUE, ОТМЕНЕН = FALSE WHERE ДОККОД = " + docZakazId + " AND СТР = " + strZakazId;
      db.exec(command);
      // Посчитаем не выполненные заказы
      var notProcessed = db.getValue("SELECT COUNT(*) FROM атрибуты3 WHERE ДОККОД = " + docZakazId + " AND NOT (ВЫПОЛНЕН OR ОТМЕНЕН);");
      if (notProcessed == 0)
      {
	command = "UPDATE докатрибуты3 SET ВЫПОЛНЕН = TRUE WHERE КОД = " + docZakazId;
	db.exec(command);
      }
    }
    var command = "UPDATE атрибуты129 SET ВЫПОЛНЕН = TRUE WHERE ДОККОД = " + docId + " AND СТР = " + strNum;
    db.exec(command);
    
    if (zakazId > 0)
    {
      zakazRec = db.getRecord("SELECT КОЛ, ПОСТОЯННО FROM заявка WHERE КОД = " + zakazId, 0);
      if (!zakazRec.isEmpty())
      {
	var constantly = zakazRec.value("ПОСТОЯННО");
	var zakQuan = zakazRec.value("КОЛ");
	if (constantly)
	  db.exec("UPDATE товар SET ЗАПАС=" + quan + " WHERE КОД=" + nomId);
	if (zakQuan > quan)
	  db.exec("UPDATE заявка SET КОЛ = " + (zakQuan - quan) + " WHERE КОД = " + zakazId);
	else
	db.exec("DELETE FROM заявка WHERE КОД = " + zakazId + ";");
      }
    }
    
    if (zakazDocs.indexOf(docId) < 0)
	zakazDocs.push(docId);
  }
  else
    app.printToArray("нетзаказа", "Не найден заказ для позиции: <" + name + "> в количестве " + quan);     
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

	if (getCurrentFieldName() == "P1__СУММА" && кол != 0) 
	{
		цена = сумма / кол;
	}
	else 
	{
		сумма = кол * цена;
	}
	setValue("P1__КОЛ", кол);
	setValue("P1__ЦЕНА", цена);
	setValue("P1__СУММА", сумма);
	if (getCurrentFieldName() == "P1__КОЛ" && !automatedInput)
	{
	  priceId = getValue("КОД_ПРАЙС");
	  WriteZakaz(getValue("ТОВАР__ИМЯ"), getValue("P1__КОЛ"));
	  nomId = getValue("ТОВАР__КОД");
	  prepReports(getValue("P1__КОЛ"), getValue("P1__ЦЕНА"));
	}
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


function prepareSMS(docId)
{
	var command = "SELECT КОДДОКЗАКАЗ, SUM(CASE WHEN ВЫПОЛНЕН THEN 1 ELSE 0 END) AS ВЫПОЛНЕНО FROM атрибуты129 WHERE ДОККОД = " + docId + " AND КОДДОКЗАКАЗ > 0 GROUP BY КОДДОКЗАКАЗ;";
	var zakQuery = db.execQuery(command);
	if (zakQuery.first())
	{
		var totPos = 0;
		var zakPos = 0;
		var oldZakDocId = 0;
		do
		{
			var zakRec = zakQuery.record();
			var zakDocId = zakRec.value("КОДДОКЗАКАЗ");
			if (zakDocId != oldZakDocId)
			{
			  if (totPos > 0)
			  {
			    sendSMS(oldZakDocId, zakPos, totPos);
			    zakPos = 0;
			    totPos = 0;
			  }
			  oldZakDocId = zakDocId;
			}
			if (zakRec.value("ВЫПОЛНЕНО"))
			  zakPos = zakPos + 1;
			totPos = totPos + 1;
		} while (zakQuery.next());
		if (totPos > 0)
		  sendSMS(oldZakDocId, zakPos, totPos);
	}
}


function sendSMS(zakDocId, zakPos, totPos)
{
  var message = "";
  var command = "SELECT ТЕЛЕФОН FROM люди WHERE КОД = (SELECT ДБКОД FROM проводки WHERE ДОККОД = " + zakDocId + " AND ОПЕР = 3 AND НОМЕРОПЕР =  1 LIMIT 1);";
  var phone = db.getValue(command);
  if (zakPos > 0)
  {
    if (zakPos < totPos)
      message = "По вашему заказу ожидается поступление " + zakPos + " поз. из " + totPos + ".";
    else
      message = "Ожидается поступление вашего заказа.";
  }
  else
    message = "К сожалению, товар из вашего заказа у поставщика отсутствует."
  app.print("СМС на телефон " + phone + ": " + message);
  app.sendSMS(phone, message);
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
		if (docs.isFormSelected() && !docs.getValue("ЗАКРЫТ"))
		{
			var doc = docs.getDocument(docs.getId());
			doc.query();
			firmId = doc.getDictionary("фирмы").getId();
			var tovarDict = getDictionary("товар");
			var orgDict = getDictionary("организации");
			var progress = ProgressDialog("Заполнение на основании заказа. Ожидайте...");
			progress.show();
			progress.setMaximum(doc.getRowCount());
			for (var rowCount = 0; rowCount < doc.getRowCount(); rowCount++)
			{
				doc.setCurrentRow(rowCount);
				progress.setValue(rowCount);
				priceId = doc.getValue("ПРАЙС__КОД");
				priceName = doc.getValue("ПРАЙС__ИМЯ");
				var quan = doc.getValue("P1__КОЛ");
				var result = WriteTovar(quan, doc.getValue("P1__ЦЕНА"));
				if (result.length > 0)
				  app.print(doc.getValue("ПРАЙС__ИМЯВПРАЙСЕ") + " " + priceName + ": " + result);
				else
				{
				  WriteZakaz(priceName, quan);
				  prepReports(quan, doc.getValue("P1__ЦЕНА"));
				}
				app.showMessageOnStatusBar("Загружено " + Math.round(rowCount * 100 / doc.getRowCount())+ "%");	
			}
			progress.hide();
		}
	}
}



