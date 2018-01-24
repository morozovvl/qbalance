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


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
	form.getButtonLoad().show();		// Включим кнопку "Загрузить документ" на форме
	table.setPhotoNameField("ТОВАР__ИМЯ");
	table.setPhotoIdField("ТОВАР__КОД");
	table.setPhotoEnabled(true);
	table.setPhotoPath(db.getDictionaryPhotoPath("товар"));

	priceDict = getDictionary("прайс");
	
	// Заменим форму по умолчанию на новую форму
	nomDict = getDictionary("товар");
	nomDict.setForm("товар2");
	nomForm = nomDict.getFormWidget();
	nomForm.findChild("picturePrice").setVisible(false);
	nomForm.findChild("labelPrice").setVisible(false);	
}


function EventImport(form)
{ // Событие происходит при нажатии кнопки <Загрузить документ>
  if (getDictionary("организации").getId() > 0)
  {
    var fileName = QFileDialog.getOpenFileName(form, "Откройте документ с приходом товара", QDir.currentPath(), "Документ OpenOffice(*.ods);; Документ CommerceML(*.xml)");
    if (fileName != "")
    {    
	document.saveChanges();
	var file = new QFileInfo(fileName);
	if (file.suffix() == "ods")
	{
		app.clearPrintArrays();
		OdsFile(fileName);
		app.print("Приход товара от <" + agentName + "> по накладной № " + document.getNumber() + " от " + document.getDate());
		app.print("------------------------------------------");
		app.print();
		app.printArray("запас");
		app.print();
		app.printArray("запас1");
		app.print();
		app.printArray("запас2");
		app.print();
		app.printArray("ценыповысились");
		app.print();
		app.printArray("ценыпонизились");
		app.print();
		return;
	}
	if (file.suffix() == "xml")
	{
		XmlFile(fileName);
		return;
	}
    }
  }
  else
    QMessageBox.warning(form, "Документ", "Сначала определите контрагента.");
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
		var agentDict = getDictionary("организации");	// Найдем такого контрагента в нашей БД
		
		evaluateScript(dir + "/readDocNumber.js");	// Запустим локальный скрипт, который вытащит из файла номер и дату документа

		if (agentName.length > 0)
            			agentDict.query("организации.ИМЯ ILIKE '%" + agentName + "%'");
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
			var firmId = agentDict.getValue("КОД_ФИРМЫ");
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
//					tovarName = ods.getCellText(row, colName);
				}
				if (colArticul >= 0)
				{
					tovarArticul = findFieldData(row, colArticul, "АРТИКУЛ", false);
//					tovarArticul = ods.getCellText(row, colArticul);
				}
				if (colProizv >= 0)
				{
					tovarProizv = findFieldData(row, colProizv, "ПРОИЗВОДИТЕЛЬ", false);
//					tovarProizv = ods.getCellText(row, colProizv);
				}
				if (colUnit >= 0)
				{
					tovarUnit = findFieldData(row, colUnit, "ЕДИЗМ", false);
//					tovarUnit = ods.getCellText(row, colUnit);
				}
				if (colQuan >= 0)
				{
					tovarQuan = findFieldData(row, colQuan, "КОЛ", true);
//					tovarQuan = parseFloat(ods.getCellText(row, colQuan).replace(",", "."));
				}
				if (colPrice >= 0 && tovarQuan > 0)
				{
					tovarPrice = findFieldData(row, colPrice, "ЦЕНА", false);
//					tovarPrice = parseFloat(ods.getCellText(row, colPrice).replace(/\s+/g, "").replace(",", "."));
				}
				if (colSum >= 0 && tovarQuan > 0)
				{
					tovarSum = findFieldData(row, colSum, "СУММА", true);
//					tovarSum = parseFloat(ods.getCellText(row, colSum).replace(/\s+/g, "").replace(",", "."));
				}
//				print(tovarName, tovarQuan, tovarSum, tovarName.match(/[А-Яа-я]+/));
				if (tovarName.match(/[А-Яа-я]+/) && tovarQuan > 0 && tovarSum > 0 && !exitKeyPressed)	// Если наименование не пустое и содержит буквы, а количество и сумма больше 0
				{					// Значит нам попалась строка с описанием позиции товара
					tovarPrice = tovarSum / tovarQuan;
					WriteTovar(firmId, tovarId, tovarName, tovarArticul, tovarProizv, tovarUnit, tovarQuan, tovarPrice, tovarSum, docDate);
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
	      var firmId = agentDict.getValue("КОД_ФИРМЫ");	// Получим код фирмы отгрузки контрагента
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
}


function WriteTovar(firmId, id, name, articul, proizv, unit, quan, price, sum, date)
// Запишем позицию в документ, предварительно выяснив соответствие в таблице прайсов
{
  var newPosition = false;
  var nomId = 0;
  var priceId = 0;
  id = id.replace(/^[0]+/g,"");	// удалим первые 0
  id = id.replace(/\s+/g, "");	// удалим пробелы
  name = name.replace("'", "\'");
  if (date == '')
  	date = (new Date).toISOString().substr(0,10);

  // Поищем в прайсе поставщика запись о позиции, которая поступила
  var priceRec;
  var command;
  if (id.length > 0)
  	command = "SELECT * FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';";
  else
  	command = "SELECT * FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND (strpos(ИМЯ, '" + name + "') > 0 OR strpos('" + name + "', ИМЯ) > 0)" + ";";
  priceRec = db.execQuery(command);
  if (priceRec.size() != 0)		// Если в прайсе есть записи о такой позиции
  {
    if (priceRec.first())
       {					
          nomId = priceRec.record().value("КОД_ТОВАР");	// Посмотрим, какой нашей позиции соответствует это название в прайсе
          priceId = priceRec.record().value("КОД");
          name = priceRec.record().value("ИМЯ");
          articul = priceRec.record().value("АРТИКУЛ");
          proizv = priceRec.record().value("ПРОИЗВОДИТЕЛЬ");
          var quan_price = priceRec.record().value("КОЛ_ПРАЙС");
          var quan_tovar = priceRec.record().value("КОЛ_ТОВАР");
          if (quan_price > 0)
         {
     	quan = quan * quan_tovar / quan_price;
	if (quan > 0)
	      price = sum / quan;
          }
       }
  }
  else
  	app.print("Позиция <" + name + "> в прайсе не найдена. Будет создана вновь.");
  if (nomId == 0)			// Если мы не знаем, какой нашей позиции соотстветствует это наименование
  {					// тогда спросим это у пользователя
     if (priceId > 0)
     {
     	priceDict.setId(priceId);
	nomForm.findChild("picturePrice").setVisible(true);
	nomForm.findChild("labelPrice").setVisible(true);	
	nomForm.findChild("picturePrice").show(priceDict.getPhotoFile());
	nomForm.findChild("picturePrice").setPhotoWindowTitle(name);
     }
     else
     {
	nomForm.findChild("picturePrice").setVisible(true);
	nomForm.findChild("labelPrice").setVisible(true);	
     }
    var formTitle = nomDict.getFormTitle();
    nomDict.setFormTitle("Укажите позицию аналогичную: " + name + " (" + articul + ") " + proizv);		// Установим в заголовке окна подсказку для пользователя
    nomDict.getForm().setParameter("товар", name);
    nomDict.exec();
    nomDict.setFormTitle(formTitle);					// Вернем прежнее название окна
    if (nomDict.isFormSelected())	// если пользователь нажал кнопку Ok
    {
      newPosition = true;
      nomId = nomDict.getId();
/*
      if (nomDict.getValue("ЦЕНА") == 0)	// если цена позиции нулевая, позиция новая
      {
           var newPrice = 0;
          newPrice = db.getValue("SELECT sp_calcnewprice(" + nomDict.getValue("КОД_ГРУППЫ") + ", " + price + ");");
           nomDict.setValue("ЦЕНА", newPrice);	// то вычислим и поставим новую цену
       }
*/
      if (priceRec.size() == 0)		// Если в прайсе раньше такой позиции не было
      {
	  db.exec("INSERT INTO прайс (КОДВПРАЙСЕ, ИМЯ, ШИФР_ПО_КАТАЛОГУ, ЕДИЗМ, МИНЦЕНА, КОД_ФИРМЫ, КОД_ТОВАР, ДАТА) VALUES ('" + id + "','" + name + "','" + articul + "','" + unit + "'," + price + "," + firmId + "," + nomId + ",'" + date + "');");
	  if (id.length > 0)
	      priceRec = db.execQuery("SELECT * FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';");
	  else
	      priceRec = db.execQuery("SELECT * FROM прайс WHERE КОД_ФИРМЫ = " + firmId + " AND trim(ИМЯ) = '" + name + "';");
      }
      else
      {
	if (nomId > 0)
	{
		if (id.length > 0)
			db.exec("UPDATE прайс SET КОД_ТОВАР = " + nomId + ",ИМЯ = '" + name + "'::varchar(100), ШИФР_ПО_КАТАЛОГУ = '" + articul + "', ЕДИЗМ = '" + unit + "',МИНЦЕНА = " + price + " WHERE КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';");
		else
			db.exec("UPDATE прайс SET КОД_ТОВАР = " + nomId + ",ИМЯ = '" + name + "'::varchar(100), ШИФР_ПО_КАТАЛОГУ = '" + articul + "', ЕДИЗМ = '" + unit + "',МИНЦЕНА = " + price + " WHERE КОД_ФИРМЫ = " + firmId + " AND trim(ИМЯ) = '" + name + "';");
      	}
      }
      if (priceRec.size() != 0)		// Если в прайсе есть записи о такой позиции
      {
	if (priceRec.first())
             priceId = priceRec.record().value("КОД");
      }

    }
    else
    {
     var exitMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Документ полностью не загружен. Прервать загрузку?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
     if (exitMsg.exec() == QMessageBox.Yes)
 	exitKeyPressed = true;
    }
  }
  else
    nomDict.setId(nomId);
  var zakRec = db.execQuery("SELECT КОДВПРАЙСЕ, КОЛ, ПОСТОЯННО FROM заявка WHERE МОДИФИЦИРОВАНО = true AND КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';");
  if (zakRec.first())
  {
     var constantly = zakRec.record().value("ПОСТОЯННО");
     var zakQuan = zakRec.record().value("КОЛ");
     if (constantly)
        db.exec("UPDATE товар SET ЗАПАС=" + quan + " WHERE КОД=" + nomId + ";");
     if (zakQuan > quan)
    {
        db.exec("UPDATE заявка SET КОЛ = " + (zakQuan - quan) + " WHERE МОДИФИЦИРОВАНО = true AND КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';");
    }
     else
    {
       db.exec("DELETE FROM заявка WHERE МОДИФИЦИРОВАНО = true AND КОД_ФИРМЫ = " + firmId + " AND trim(КОДВПРАЙСЕ) = '" + id + "';");
    }
  }	
  if (nomId != 0)
  {
// Проверим, не превышает ли остаток норму запаса, чтобы избежать накопления запасов
    var ostRec = db.execQuery("SELECT SUM(КОНКОЛ) FROM сальдо WHERE СЧЕТ = '411' AND КОД IN (SELECT КОД FROM набор1 WHERE КОД_ТОВАР = " + nomId + " AND КОД_АДРЕС NOT IN (SELECT КОД FROM адрес WHERE ИМЯ LIKE 'Брак'));");
    if (ostRec.first())
    {
      var ost = ostRec.record().value(0);
      var zap = nomDict.getValue("ЗАПАС");
      if (zap > 0)
      {
      	if (ost + quan > zap)
	        app.printToArray("запас", "Превышена норма запаса: " + nomDict.getName() + ". Запас - " + zap + ", остаток - " + ost + ", поступило - " + quan);
       }
       else
       {
	if (newPosition)
	        app.printToArray("запас1", "Новая позиция: " + nomDict.getName() + ". Поступило - " + quan);
                    else
	        app.printToArray("запас2", "НЕ ДОЛЖНА БЫЛА БЫТЬ ЗАКАЗАНА: " + nomDict.getName() + ". Поступило - " + quan);
       }
    }

    // Запишем кол-во, цену, сумму в проводку
    document.prepareValue("P1__ДБКОД", nomId);
    document.prepareValue("P1__КОЛ", quan);
    document.prepareValue("P1__ЦЕНА", price);
    document.prepareValue("P1__СУММА", sum);
    document.prepareValue("КОД_ПРАЙС", priceId);
    // Сохраним проводку на сервере
    var row = document.appendDocString();
    if (priceId > 0)
    {
	// скопируем фотографию
	priceDict.setId(priceId);
	priceDict.getPhotoFile(getDictionary("товар").getPhotoPath() + "/" + nomId + ".jpg");
	
	var priceInPrice = priceDict.getValue("МИНЦЕНА");
	var quanPrice = priceDict.getValue("КОЛ_ПРАЙС");
	var quanTovar = priceDict.getValue("КОЛ_ТОВАР");
	if (priceInPrice != price)
	{
		var proc = Math.round(100 *  (priceInPrice - price) / price);
		if (proc < 0)
		{
			app.printToArray("ценыповысились", "стр." + row + ". " + nomDict.getName() + " --- цена повысилась на " + (- proc) + "%");
			print(nomDict.getName(), priceInPrice, quanPrice, quanTovar, price);
		}
		if (proc > 0)
			app.printToArray("ценыпонизились", "стр." + row + ". " + nomDict.getName() + " --- цена понизилась на " + proc + "%");
		priceDict.setValue("МИНЦЕНА", price);
		priceDict.setValue("ДАТА", documents.getValue("ДАТА"));
	}
    }
 }
}


function EventParametersChanged()
{
// Запишем наименование фирмы-поставщика в комментарии к документу
	documents.setValue("Комментарий", getDictionary("организации").getValue("имя"));
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


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
	getDictionary("прайс").setMustShow(false);
}


