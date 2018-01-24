var form;
var zakazForm;
var zakazFormName = "zakaz";
var name = "";
var unit = "";
var quan = 0;
var price = 0;
var menId = 0;		// Идентификатор заказчика
var menName = "";
var zakaz;

var firmId = 0;
var id;
var url = "";
var pinCode = "";
var pictureId = 0;

var tablePrice =	db.getObjectName("vw_прайс");
var tableTovar = 	db.getObjectName("товар");
var tablePeople = 	db.getObjectName("люди");
var tablePeople1 = 	db.getObjectName("vw_люди");
var tableZakaz = 	db.getObjectName("заявка");
var fieldId = 	db.getObjectName("vw_прайс.КОД");
var fieldName = 	db.getObjectName("vw_прайс.ИМЯ");
var fieldUnit = 	db.getObjectName("vw_прайс.ЕДИЗМ");
var fieldPrice = 	db.getObjectName("vw_прайс.МИНЦЕНА");
var fieldDictIdTovar = 	db.getObjectName("прайс.КОД_ТОВАР");
var fieldDictIdGroup = 	db.getObjectName("прайс.КОД_ГРУППЫ");
var fieldDictQuanPrice = 	db.getObjectName("прайс.КОЛ_ПРАЙС");
var fieldDictQuanTovar = 	db.getObjectName("прайс.КОЛ_ТОВАР");
var fieldDictQuan = 	db.getObjectName("прайс.КОЛ");
var fieldIdFirm = 	db.getObjectName("прайс.КОД_ФИРМЫ");
var fieldIdInPrice = 	db.getObjectName("прайс.КОДВПРАЙСЕ");
var fieldNameInPrice = 	db.getObjectName("прайс.ИМЯ");
var fieldUnitInPrice = 	db.getObjectName("прайс.ЕДИЗМ");
var fieldModified = 	db.getObjectName("прайс.МОДИФИЦИРОВАНО");
var fieldConst = 	db.getObjectName("прайс.ПОСТОЯННО");
var fieldPriceInPrice = 	db.getObjectName("прайс.МИНЦЕНА");
var fieldPriceInZakaz = 	db.getObjectName("заявка.ЦЕНА_ОБРАБОТАННАЯ");
var fieldIdMan = 		db.getObjectName("заявка.КОД_ЛЮДИ");
var fieldZakazIdTovar = 		db.getObjectName("заявка.КОД_ТОВАР");
var fieldZakazPriceId = 		db.getObjectName("заявка.КОДВПРАЙСЕ");
var fieldZakazPriceName = 	db.getObjectName("заявка.ИМЯВПРАЙСЕ");
var fieldZakazPriceUnit = 	db.getObjectName("заявка.ЕДИЗМВПРАЙСЕ");
var fieldZakazIdFirm = 		db.getObjectName("заявка.КОД_ФИРМЫ");
var fieldQuanModified = 	db.getObjectName("заявка.КОЛ_ОБРАБОТАННОЕ");
var fieldDateModified = 	db.getObjectName("заявка.ДАТАОБРАБОТКИ");
var fieldNalichie = 	db.getObjectName("прайс.НАЛИЧИЕ");
var fieldPeopleId = 	db.getObjectName("люди.КОД");
var fieldPeopleName = 	db.getObjectName("люди.ИМЯ");
var fieldPeopleNameCom = db.getObjectNameCom("люди.ИМЯ");
var fieldPeoplePhone = 	db.getObjectNameCom("люди.ТЕЛЕФОН");




function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	zakaz = app.getDictionaries().getDictionary(tableZakaz);
	zakazForm = app.createForm(zakazFormName);
	if (zakazForm != null)
	{
		var buttonBox = zakazForm.findChild("buttonBox");
		var pushButtonMenPhoneSearch = zakazForm.findChild("pushButtonMenSearch");
		var pushButtonAddMen = zakazForm.findChild("pushButtonAddMen");
		var pushButtonSendSMS = zakazForm.findChild("pushButtonSendSMS");
		form.buttonZakaz.clicked.connect(Zakaz);			// Соединим сигнал кнопки "Заказать" с обработчиком - слотом Zakaz
		form.buttonViewZakaz.clicked.connect(ViewZakaz);
		form.buttonCatalog.clicked.connect(ViewCatalog);
		pushButtonMenPhoneSearch.clicked.connect(SearchMenByPhone);
		pushButtonAddMen.clicked.connect(AddMen);
		pushButtonSendSMS.clicked.connect(sendSMS);
		buttonBox.button(QDialogButtonBox.Ok).clicked.connect(cmdOk);
		buttonBox.button(QDialogButtonBox.Cancel).clicked.connect(cmdCancel);
	}
	else
	{
		app.showError("Не найдена форма" + zakazFormName);
	}
	if (!table.isDefaultForm())
	{
		 table.getFormWidget().findChild("lineEditMinPrice").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditMaxPrice").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditArticul").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditProizv").returnPressed.connect(cmdRequery);
	}
}


function cmdRequery()
{
	table.getForm().cmdRequery()
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	var val = table.getForm().getSearchValue('vw_прайс').toString().trim();
	var priceId = parseInt(table.getForm().getSearchValue('vw_прайс'));
	if (!isNaN(priceId) && priceId.toString() == val)
	{
		filter = "vw_прайс.КОДВПРАЙСЕ = '" + priceId + "'";
		var firmName = table.getForm().getSearchValue('фирмы');
		if (firmName.length)
		{
			if (filter.length > 0)
				filter = filter + " AND ";
			filter = filter + "фирмы.ИМЯ ILIKE '%" + firmName + "%'";
		}
	}
	var minPrice = table.getFormWidget().findChild("lineEditMinPrice").text;
	if (minPrice.length > 0)
		minPrice = parseFloat(minPrice);
	var maxPrice = table.getFormWidget().findChild("lineEditMaxPrice").text;
	if (maxPrice.length > 0)
		maxPrice = parseFloat(maxPrice);
	var articul = table.getFormWidget().findChild("lineEditArticul").text.trim();
	var proizv = table.getFormWidget().findChild("lineEditProizv").text.trim();
	var priceDate = new Date();
	priceDate.setDate(priceDate.getDate() - app.getConst("АктуальностьПрайсов"));
	if (filter.length > 0)
		filter = filter + " AND ";
	filter = filter + "ДАТА >= '" + priceDate.toLocaleDateString() + "'";
	if (minPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "МИНЦЕНА >= " + minPrice;
	}
	if (maxPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "МИНЦЕНА <= " + maxPrice;
	}
	if (articul.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		articul = articul.replace(/\s+/g, "%");	// удалим пробелы
		filter = filter + "vw_прайс.ШИФР_ПО_КАТАЛОГУ LIKE '%" + articul + "%'";
	}
	if (proizv.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "vw_прайс.ПРОИЗВОДИТЕЛЬ LIKE '%" + proizv + "%'";
	}
	return filter;
}


function Zakaz()
{
	var lineEditName = zakazForm.findChild("lineEditName");		// Найдем виджет, в котором будем выводить имя позиции
	var lineEditUnit = zakazForm.findChild("lineEditUnit");		// Найдем виджет, в котором будем выводить единицу измерения
	var lineEditPrice = zakazForm.findChild("lineEditPrice");		// Найдем виджет, в котором будем выводить единицу измерения
	var spinBoxQuan = zakazForm.findChild("spinBox");
	var checkBoxConst = zakazForm.findChild("checkBox");
	name = getValue(fieldName);					// Получим имя позиции, которую нужно заказать
	if (name != undefined && name.length > 0)			// Если имя позиции определено и оно не пустая строка
	{
		lineEditName.setText(name);
		lineEditUnit.setText(getValue(fieldUnit));
		lineEditPrice.setText(getValue(fieldPrice));
		spinBoxQuan.setValue(1);			// Значение по умолчанию - заказываем 1 единицу товара
		checkBoxConst.setCheckState(0);		// Значение по умолчанию - не будем заказывать эту позицию постоянно
		zakazForm.exec();
	}
}


function ViewZakaz()
{
	var zakaz = app.getDictionaries().getDictionary(tableZakaz);
	zakaz.setDeleteable(true);
	zakaz.setOrderClause("ТОВАР__ИМЯ, ФИРМЫ__ИМЯ, ИМЯВПРАЙСЕ");
	zakaz.setFilter("МОДИФИЦИРОВАНО=true");
	zakaz.hideAllGridSections();
	zakaz.showGridSection("ТОВАР__ИМЯ");
	zakaz.showGridSection("ТОВАР__ЕДИЗМ");
	zakaz.showGridSection("ФИРМЫ__ИМЯ");
	zakaz.showGridSection("ИМЯВПРАЙСЕ");
	zakaz.showGridSection("ДАТАОБРАБОТКИ");
	zakaz.showGridSection("КОЛ");
	zakaz.exec();
	zakaz.showAllGridSections();
	zakaz.setFilter("");
}


function ViewCatalog()
{
	var nom_Articul = table.getValue("ШИФР_ПО_КАТАЛОГУ").trim();
	if (nom_Articul.length > 0)
	{
		var command = "firefox http://www.autoopt.ru/search/catalog/?q=" + nom_Articul + "&set_filter=y";
		app.print(command);
		app.runProcess(command, "Mozilla FireFox");
	}
}


function cmdOk()
{
	var appendEnabled = true;			// По умолчанию будет разрешено добавлять позицию в заказ
	var priceId = getValue(fieldId);
	var radioButtonToClient = zakazForm.findChild("radioButtonToClient");
	var radioButtonToShop = zakazForm.findChild("radioButtonToShop");
	var spinBoxQuan = zakazForm.findChild("spinBox");
	var checkBoxConst = zakazForm.findChild("checkBox");

	if (spinBoxQuan.value > 0)
	{
	  if (radioButtonToClient.checked)
	  {
	    var pin = zakazForm.findChild("lineEditPin").text.toString().trim();
	    if (pin.length > 0)
	    {
	      if (pin != pinCode)
	      {
		var errorMsg = new QMessageBox(QMessageBox.Critical, "Внимание!", "PIN код не верный. Заказ не принят.");
		errorMsg.exec();
		appendEnabled = false;
	      }
	    }
	    else
	    {
	      var errorMsg = new QMessageBox(QMessageBox.Critical, "Внимание!", "Не указан PIN код. Заказ не принят.");
	      errorMsg.exec();
	      appendEnabled = false;
	    }
	  }
	}
	if (appendEnabled)
	{
		var fieldsList = "";				// Здесь будем собирать список полей для команды INSERT
		var valuesList = "";				// Здесь будем собирать список значений для команды INSERT
		var priceDictionary = getDictionary(tablePrice);
		priceDictionary.setId(priceId);

		var quan = spinBoxQuan.value;
		var price = priceDictionary.getValue(fieldPrice);
		var tovarId = priceDictionary.getValue(fieldDictIdTovar);		// Получим из таблицы соответствий идентификатор позиции в нашей номенклатуре
		var firmId = priceDictionary.getValue(fieldIdFirm);

		if (tovarId > 0)					// Если в прайсе для данной позиции указана наша позиция, т.е. имеется соответствие,
		{					// тогда в заказ проставим код позиции из нашей номенклатуры, возможно для нашей позиции имеются соответствия у
							// других поставщиков и можно привезти эту позицию дешевле
			// Проверим, нет ли уже в заказе данной позиции
			var command = "SELECT * FROM " + tableZakaz + " WHERE " + fieldZakazIdTovar + " = " + tovarId + ";";
			var zakazQuery = db.execQuery(command);
			if (zakazQuery.first())
			  appendEnabled = false;	// Запретим добавление, т.к. такая позиция в заказе уже есть
			else
			{
			  var tovarDictionary = app.getDictionaries().getDictionary(tableTovar);
			  tovarDictionary.setId(tovarId);
			  var groupId = tovarDictionary.getValue(fieldDictIdGroup);
			  var quanPrice = priceDictionary.getValue(fieldDictQuanPrice);
			  var nomInPriceId = priceDictionary.getValue(fieldIdInPrice);
			  var nomInPriceName = priceDictionary.getValue(fieldNameInPrice);
			  var nomInPriceUnit = priceDictionary.getValue(fieldUnitInPrice);
			  if (quanPrice > 0)			// Для избежания деления на 0
			  {
				  quan = quan * priceDictionary.getValue(fieldDictQuanTovar) / quanPrice;	// Подсчитаем количество, которое заказать. Количество в позиции у нас и у поставщика
									  //  может быть разное. Например, у них считается комплектами, а у нас - поштучно
			  }
			  fieldsList = fieldDictIdTovar + "," + fieldDictIdGroup + "," + fieldZakazIdFirm + "," + fieldQuanModified + "," + fieldZakazPriceId + "," +  fieldZakazPriceName + "," + fieldZakazPriceUnit;
			  valuesList = tovarId + "," + groupId + "," + firmId + "," + quan + ",'" + nomInPriceId + "','" + nomInPriceName + "','" + nomInPriceUnit + "'";
			}
		}
		else
		{
			// Проверим, нет ли уже в заказе данной позиции
			var fldName = getValue(fieldName);
//			print(fldName);			
//			fldName = fldName.replace("'", "''");
//			print(fldName);
			var command = "SELECT * FROM " + tableZakaz + " WHERE " + fieldIdFirm + " = " + getValue(fieldIdFirm) + " AND " + fieldZakazPriceName + " = '" + fldName + "';";
			var zakazQuery = db.execQuery(command);
			if (zakazQuery.first())
			  appendEnabled = false;	// Запретим добавление, т.к. такая позиция в заказе уже есть
			else
			{
			  var nalichie =  priceDictionary.getValue(fieldNalichie);
			  fieldsList = fieldIdFirm + "," + fieldZakazPriceId + "," +  fieldZakazPriceName + "," + fieldZakazPriceUnit + "," + fieldQuanModified + "," + fieldPriceInZakaz + "," + fieldDateModified + "," + fieldNalichie;
			  valuesList = getValue(fieldIdFirm) + ",'" + getValue(fieldIdInPrice).replace(/^[0]+/g,"") + "','" + fldName + "','" + getValue(fieldUnit) + "'," + quan + "," + price + ",current_date, '" + nalichie + "'";
			}
		}
		if (appendEnabled)
		{
		  fieldsList += "," + fieldDictQuan + "," + fieldModified + ", КОД_ПРАЙС";
		  valuesList += "," + quan + ",true," + priceId;

		  var messageString = "Заказана позиция " + name + " в количестве " + quan + unit;
		
		  if (radioButtonToClient.checked)	// Если заказ поступил от физического лица
		  {

			  if (menId > 0)
			  {
			    var documents = app.getDocuments(3);
			    if (documents.add())
			    {
				var document = documents.getDocument();
				document.prepareValue("P1__ДБКОД", menId);
				document.prepareValue("P2__КРКОД", menId);
				document.prepareValue("P1__КРКОД", priceId);
				document.prepareValue("P1__КОЛ", quan);
				document.prepareValue("P1__ЦЕНА", price);
				document.prepareValue("P1__СУММА", quan * price);
				document.prepareValue("КОД_ФИРМЫ", firmId);
				document.appendDocString();
				document.calcItog();
			      	documents.getDocument().show();
			    }
			  }	
			  else
			  {
				  fieldsList = "";		// Обозначим, что заказ отменен
				  app.showError("Необходимо указать заказчика!");			
			  }
		  }
		  if (radioButtonToShop.checked)	// Если товар нужно привезти в магазин
		  {
			if (checkBoxConst.checked)		// Если указано, что товар нужно возить постоянно
			{
				fieldsList += "," + fieldConst;
				valuesList += ",true";
			}
			if (fieldsList.length > 0)
			{
			  var addMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Заказать позицию?");
			  addMsg.addButton(QMessageBox.Yes);
			  addMsg.addButton(QMessageBox.No);
			  addMsg.setDefaultButton(QMessageBox.No);
			  if (addMsg.exec() == QMessageBox.Yes)
			  {
			    var command = "INSERT INTO " + tableZakaz + " (" + fieldsList + ") VALUES (" + valuesList + ");";
			    db.exec(command);
/*
			    if (tovarId > 0)
			    {
			      command = "UPDATE " + tableTovar + " SET ЗАПАС = " + quan + ", АВТЗАПАС = " + quan + " WHERE КОД = " + tovarId;
			      db.exec(command);
			    }
*/
			    app.showMessageOnStatusBar(messageString);
			  }
			  else
			  {
			    cmdCancel();
			    return;
			  }
			}
		  }
		}
		else
		{
     			var exitMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Эта позиция уже заказана!", QMessageBox.StandardButtons(QMessageBox.Ok), form);
     			exitMsg.exec();
		}
	    }
	zakazForm.hide();
}


function cmdCancel()
{
	app.showMessageOnStatusBar("Заказ отменен.");
	zakazForm.hide();
}


function SearchMenByPhone()
{ // Поиск человека в базе данных по телефону
	var phone = zakazForm.findChild("lineEditMenPhone").text.replace(/-/g, "");	// Получим номер телефона
	if (phone.length > 0)
	{
		var lineEditMenName =  zakazForm.findChild("lineEditMenName");
		var command = "SELECT * FROM " + tablePeople + " WHERE trim(" + fieldPeoplePhone + ") = '" + phone + "';";
		var menQuery = db.execQuery(command);
		if (menQuery.first())
		{
			var menRecord = menQuery.record();
			menId = menRecord.value(fieldPeopleId);
			menName = menRecord.value(fieldPeopleName).toString();
			lineEditMenName.setText(menName.trim());
			var radioButtonToClient = zakazForm.findChild("radioButtonToClient");
			var spinBoxQuan = zakazForm.findChild("spinBox");
			var checkBoxConst = zakazForm.findChild("checkBox");
			radioButtonToClient.setChecked(true);
			spinBoxQuan.setValue(1);			// Значение по умолчанию - заказываем 1 единицу товара
			checkBoxConst.setCheckState(0);		// Значение по умолчанию - не будем заказывать эту позицию постоянно
		}
		else
		{
			menId = 0;
			menName = "";
			var errorMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Человек с таким номером телефона не найден.");
			errorMsg.exec();
		}
	}
}


function AddMen()
{ // Если человека с таким номером телефона нет, то он добавляется в базу данных. Если есть, то у него исправляется ФИО на случай, если оно написано с ошибкой
	var phone = zakazForm.findChild("lineEditMenPhone").text.replace(/-/g, "");	// Получим номер телефона
	var name = zakazForm.findChild("lineEditMenName").text.trim();
	if (phone.length > 0 && name.length > 0)
	{
		if (menId == 0)
		{
			var lineEditMenName =  zakazForm.findChild("lineEditMenName");
			var command = "SELECT * FROM " + tablePeople + " WHERE trim(" + fieldPeoplePhone + ") = '" + phone + "';";
			var menQuery = db.execQuery(command);
			if (menQuery.first())
			{
				var menRecord = menQuery.record();
				menId = menRecord.value(fieldPeopleId);
				menName = name;
			}
		}
		if (menId != 0)
		{
			command = "UPDATE " + tablePeople + " SET " + fieldPeopleNameCom + " = '" + name + "', " + fieldPeoplePhone + " = '" + phone + "' WHERE " + fieldPeopleId + " = " + menId + ";";
			db.exec(command); 
		}
		else
		{
			command = "INSERT INTO " + tablePeople + " (" + fieldPeopleNameCom + "," + fieldPeoplePhone + ") VALUES ('" + name + "', '" + phone + "');";
			db.exec(command); 
			SearchMenByPhone();
		}
	}
}


function sendSMS()
{
  var phone = zakazForm.findChild("lineEditMenPhone").text.replace(/-/g, "");	// Получим номер телефона
  var name = zakazForm.findChild("lineEditMenName").text.trim();
  if (phone.length > 0)
  {
    if (name.length > 0)
    {
      AddMen();
      pinCode = "0000" + Math.random() * 10000;
      pinCode = pinCode.slice(-4);
      pinCode = "4545";
      var message = "Пинкод для подтверждения заказа: " + pinCode;
//      app.sendSMS(phone, message);
    }
    else
    {
      var errorMsg = new QMessageBox(QMessageBox.Warning, "Внимание!", "Не указано Ф.И.О. клиента. Пожалуйста, укажите.");
      errorMsg.exec();
    }
  }
  else
  {
    var errorMsg = new QMessageBox(QMessageBox.Warning, "Внимание!", "Не указан номер телефона клиента.");
    errorMsg.exec();
  }
}


function PreparePictureUrl(object)
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
  // Функция должна вернуть url фотографии.
	firmId = object.getValue("КОД_ФИРМЫ");
	pictureId = object.getValue("КОДВПРАЙСЕ");
	table.setPhotoIdField("КОДВПРАЙСЕ");
	evaluateScript("getPictureUrl.js");	// Запустим локальный скрипт
	return url;
}




