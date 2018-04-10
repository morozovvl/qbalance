var процентскидки = 0;
var сумма = 0;	// сумма продажи без скидок
var скидка = 0;	// скидка
var menId = 0;
var menName = "";
var menPhone = "";
var cardId = 0;
var cardName = "";
var cardProc = 0;
var form;
var itogForm1;
var itogFormName = "itog";
var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldDocumentTovarId	= "ТОВАР__КОД"; 
var fieldSaldoTovarId	= db.getObjectName("набор1.КОД_ТОВАР"); 
var maxDiscount	= app.getConst("МаксимальнаяСкидка");
var tablePeople 	= db.getObjectName("люди");
var fieldPeopleId	= db.getObjectName("люди.КОД");
var fieldPeopleName 	= db.getObjectName("люди.ИМЯ");
var fieldPeoplePhone 	= db.getObjectName("люди.ТЕЛЕФОН");
var fieldPeopleDiscount 	= db.getObjectName("люди.СКИДКА");
var tableCards 	= db.getObjectName("карточки");
var fieldCardId 	= db.getObjectName("карточки.КОД");
var fieldCardProc 	= db.getObjectName("карточки.СКИДКА");
var fieldCardName 	= db.getObjectName("карточки.ИМЯ");
var fieldCardIdPeople 	= db.getObjectName("карточки.КОД_ЛЮДИ");
var tableGroup	= getDictionary("группы");

var lastMaxDocId = 0;
var drvFR = 0;
var needPrintCheck = false;
var nal = 0;
var checkType = 0;
var barCodeReaded = false;
var bankTerminalExit = false;



function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	// При изменении спинбоксов с процентом или суммой скидки запустим пересчет итогов
	form = table.getFormWidget();
	form.findChild("lineEditDiscount").returnPressed.connect(ChangeDiscount);
	if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
		drvFR = app.getDrvFR();
	itogForm = app.createForm(itogFormName);
	if (itogForm != null)
	{
		itogForm.findChild("lineEditCash").returnPressed.connect(ShowSdacha);
		itogForm.findChild("buttonOk").clicked.connect(setNeedPrintCheck);
	}
	else
		app.showError("Не найдена форма" + itogFormName);

	tableGroup.query();		// Загрузим полностью один раз справочник "группы"

	form.findChild("lineEditMenPhone").returnPressed.connect(SearchMen);
	form.findChild("lineEditMenName").returnPressed.connect(SearchMen);
	form.findChild("pushButtonMenSearch").clicked.connect(SearchMen);
	form.findChild("pushButtonAddMen").clicked.connect(AddMen);
	form.findChild("pushButtonClear").clicked.connect(ClearMen);
	form.findChild("buttonTerminal").clicked.connect(BankTerminal);

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField(fieldDocumentTovarId);
	document.setPhotoEnabled(true);


	// Установим фотографии для справочника остатков товара
	document.getSaldo("411").setPhotoIdField(fieldSaldoTovarId);
	document.getSaldo("411").setPhotoPath(tovarPhotoPath);
	document.getSaldo("411").setFilter("адрес.ИМЯ NOT ILIKE '%Брак%'");
//	document.getSaldo("411").setAutoSelect(true);
	
	table.setPhotoNameField("ТОВАР__ИМЯ");

	// Если это не системный администратор, то запретим удаление продаж
	if (!app.isSA())
		table.setDeleteable(false);

	documents.setOrderClause("ДАТАВРЕМЯ");
	lastMaxDocId = db.getValue("SELECT MAX(КОД) FROM документы WHERE (ОПЕР = 1 OR ОПЕР = 71) AND ДАТА < current_date;");
	
}


function ChangeDiscount()
{
	var maxDiscount = parseInt(app.getConst("МаксимальнаяСкидка"), 10);
	var newDiscount = parseInt(form.findChild("lineEditDiscount").text, 10);
	if (newDiscount > maxDiscount)
	{
		процентскидки = maxDiscount;
		QMessageBox.warning(form, "Внимание!", "Скидка слишком велика.");
	}
	else
	{
		процентскидки = newDiscount;
	}
	CalcDiscount();
	form.setFocus();
}



function CalcDiscount()
{
	var oldItog = сумма - скидка;

	сумма = Math.round(getSumValue("P1__СУММА") * 100) / 100;		// Просуммируем первую проводку в операции для всего документа
	
	var суммаДляСкидки = 0;
	for (var i = 0; i < document.getRowCount(); i++)
	{
		if (getValue("ТОВАР__СКИДКА", i))
			суммаДляСкидки = суммаДляСкидки + getValue("P1__СУММА", i);
	}
	
	скидка = Math.round(суммаДляСкидки *  процентскидки) / 100;
	
	// Выведем комментарий о скидке
	if (скидка != 0)
		documents.setValue("КОММЕНТАРИЙ", "Скидка " + скидка + " руб. (" + процентскидки + "%). Без скидки " + сумма + " руб.");
	else
	{
		var comment = documents.getValue("КОММЕНТАРИЙ").toString();
		if (comment.indexOf("Скидка") != -1)			// Если комментарий был про скидку
			documents.setValue("КОММЕНТАРИЙ", "");		// то очистим его
	}
	setValue("P3__СУММА",  скидка);		// Запишем значение скидки в БД в третьей (свободной) проводке
	documents.setValue("СКИДКА", процентскидки);
	documents.setValue("СУММА", сумма - скидка);
	ShowItog();
}




function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
  // Восстановим переменные из БД
	menName = "";
	menPhone = "";
	процентскидки = documents.getValue("СКИДКА");
	menId = documents.getValue("КОД_ЛЮДИ");
	if (menId > 0)
	{
		var command = "SELECT * FROM " + quotes(tablePeople) + " WHERE " + quotes("КОД") + " = " + menId + ";";
		var menQuery = db.execQuery(command);
		if (menQuery.first())
		{
			var menRecord = menQuery.record();
			menName = menRecord.value(fieldPeopleName).toString().trim();
			menPhone = menRecord.value(fieldPeoplePhone).toString().trim();
			if (menRecord.value(fieldPeopleDiscount) > 0)
				процентскидки = menRecord.value(fieldPeopleDiscount).toString();
		}
	}
	скидка = getValue("P3__СУММА");
	сумма = getSumValue("P1__СУММА");		// Просуммируем первую проводку в операции для всего документа
	ShowItog();

	cardId = documents.getValue("КОД_КАРТОЧКИ");
	FindCard(cardId);
	CalcTotalDiscount(cardId);

	// Если это не системный администратор, то запретим редактирование документа продажи не сегодняшней датой
	var currentDate = new Date();
	var checkPrinted = documents.getValue("ЧЕКОТБИТ");
	var terminalPrinted = documents.getValue("БЕЗНАЛИЧНЫЕ");
	if (!app.isSA() && ((documents.getValue("ДАТА").toLocaleDateString() != currentDate.toLocaleDateString()) || checkPrinted || terminalPrinted))
		document.setEnabled(false);
	else
		document.setEnabled(true);
	needPrintCheck = false;
	nal = 0;

	tableGroup.setMustShow(false);
}


function SearchMen()
{ 
	menId = 0;
	menName = "";
	процентскидки = 0;
	// Поиск человека в базе данных по телефону
	var phone = form.findChild("lineEditMenPhone").text.replace(/-/g, "");	// Получим номер телефона
	if (phone.length > 0)
	{
		var command = "SELECT * FROM " + quotes(tablePeople) + " WHERE trim(" + quotes(fieldPeoplePhone) + ") = '" + phone + "';";
		var menQuery = db.execQuery(command);
		if (menQuery.first())
		{
			var menRecord = menQuery.record();
			menId = menRecord.value(fieldPeopleId);
			menName = menRecord.value(fieldPeopleName).toString().trim();
			menPhone = menRecord.value(fieldPeoplePhone).toString().trim();
			if (menRecord.value(fieldPeopleDiscount) > 0)
				процентскидки = menRecord.value(fieldPeopleDiscount).toString();
		}
		else
		{
			menPhone = phone;
			var errorMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Человек с таким номером телефона не найден.");
			errorMsg.exec();
		}
	}
	// Поиск человека в базе данных по имени
	var name = form.findChild("lineEditMenName").text.trim()
	if (name.length > 0)
	{
		var command = "SELECT * FROM " + quotes(tablePeople) + " WHERE " + quotes(fieldPeopleName) + " ILIKE '%" + name + "%' LIMIT 1;";
		var menQuery = db.execQuery(command);
		if (menQuery.first())
		{
			var menRecord = menQuery.record();
			menId = menRecord.value(fieldPeopleId);
			menName = menRecord.value(fieldPeopleName).toString().trim();
			menPhone = menRecord.value(fieldPeoplePhone).toString().trim();
			if (menRecord.value(fieldPeopleDiscount) > 0)
				процентскидки = menRecord.value(fieldPeopleDiscount).toString();
		}
		else
		{
			menPhone = phone;
			var errorMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Человек с таким именем не найден.");
			errorMsg.exec();
		}
	}
	if (menId > 0)
	{
		documents.setValue("КОД_ЛЮДИ", menId);
		CalcDiscount();
		document.saveChanges();
		CalcTotalDiscount(cardId);
	}
	var cardName = form.findChild("lineEditCardName").text.trim();
	if (cardName.length > 0)
	{
		EventCardCodeReaded(cardName);
	}
}


function AddMen()
{ // Если человека с таким номером телефона нет, то он добавляется в базу данных. Если есть, то у него исправляется ФИО на случай, если оно написано с ошибкой
	var phone = form.findChild("lineEditMenPhone").text.replace(/-/g, "");	// Получим номер телефона
	var name = form.findChild("lineEditMenName").text.trim();
	if (name.length > 0)
	{
		if (menId == 0)
		{
			var command;
			if (phone.length > 0)
			  command = "SELECT * FROM " + quotes(tablePeople) + " WHERE trim(" + quotes(fieldPeoplePhone) + ") = '" + phone + "';";
			else
			  command = "SELECT * FROM " + quotes(tablePeople) + " WHERE " + quotes(fieldPeopleName) + " ILIKE '%" + name + "%' LIMIT 1;";
			  
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
			command = "UPDATE " + quotes(tablePeople) + " SET " + quotes(fieldPeopleName) + " = '" + name + "', " + quotes(fieldPeoplePhone) + " = '" + phone + "' WHERE " + quotes(fieldPeopleId) + " = " + menId + ";";
			db.exec(command); 
			command = "UPDATE " + quotes(tableCards) + " SET " + quotes(fieldCardIdPeople) + " = " + menId + " WHERE " + quotes(fieldCardId) + " = " + cardId + ";";
			db.exec(command); 
		}
		else
		{
			command = "INSERT INTO " + quotes(tablePeople) + " (" + quotes(fieldPeopleName) + "," + quotes(fieldPeoplePhone) + ") VALUES ('" + name + "', '" + phone + "');";
			db.exec(command); 
			SearchMen();
		}
	}
}


function ClearMen()
{
	menId = 0;
	menName = "";
	menPhone = "";
	процентскидки = 0;
	cardId = 0;
	cardName = "";
	documents.setValue("КОД_ЛЮДИ", menId);
	documents.setValue("КОД_КАРТОЧКИ", cardId);
	CalcDiscount();
	document.saveChanges();
	form.findChild("lineEditTotSum").setText(0);
}


function CalcTotalDiscount(cardId)
{
 var totSum = 0;
 if (cardId > 0)
	totSum = db.getValue("SELECT SUM(d.СУММА) AS СУММА FROM докатрибуты1 da INNER JOIN документы d ON da.КОД = d.КОД WHERE da.КОД_КАРТОЧКИ = " + cardId + " AND d.КОД != " + documents.getId() + ";") + documents.getValue("СУММА");
totSum = Math.round(totSum * 100) / 100;
 form.findChild("lineEditTotSum").setText(totSum);
 return totSum;
}


function ShowItog()
{
	form.vsegoNumeric.setValue(сумма);		
	form.lineEditDiscount.setText(процентскидки);
	form.skidkaNumeric.setValue(скидка);
	form.itogNumeric.setValue(сумма-скидка);
	form.findChild("lineEditMenName").setText(menName);
	form.findChild("lineEditMenPhone").setText(menPhone);
	form.findChild("lineEditCardName").setText(cardName);
}


function EventBeforeHideForm(form)
{
	if (itogForm != null && !bankTerminalExit && сумма > 0 && document.isEnabled() && document.isModified())
	{
		itogForm.findChild("lineEditItog").setValue(сумма-скидка);
		itogForm.findChild("lineEditCash").setValue("");
		itogForm.findChild("lineEditCash").selectAll();
		itogForm.findChild("lineEditSdacha").setValue(0);
		itogForm.exec();
		nal = parseFloat(itogForm.findChild("lineEditCash").text);
//		if (typeof app.capturePhoto == "function" && процентскидки > 0)		// Если существует функция записи фотографий и если была сделана скидка,
//			documents.setValue("ФОТОКЛИЕНТА", app.capturePhoto());		// то сделаем фотографию клиента
	}

	if (app.drvFRisValid())
	{
		var docLocked = db.getValue("SELECT COUNT(*) FROM блокдокументов WHERE КОД_ДОКУМЕНТЫ = " + documents.getId() + " AND \"PID\" != pg_backend_pid();");
		if (docLocked == 0)
		{
			// Отпечатаем чек, если это необходимо
			if (!needPrintCheck)
			{
				documents.updateCurrentRow();	// Обновим информацию о документ, вдруг чек отбит
				if (!documents.getValue("ЧЕКОТБИТ") && documents.getValue("СУММА") > 0)
				{
			    		var checkMessage = new QMessageBox(form, "Внимание!", "Чек для этой продажи не отбит. Отбить?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
		    			if (checkMessage.exec() == QMessageBox.Yes)
		      				needPrintCheck = true;
				}
			}
			if (needPrintCheck)
			{
				PrintCheck();
				needPrintCheck = false;
			}
		}
		else
		{
			if (needPrintCheck)
				QMessageBox.warning(form, "Внимание!", "Документ открыт другим пользователем. Нельзя отбить чек.");
		}
	}
	bankTerminalExit = false;
}


function ShowSdacha()
{
	if (itogForm != null)
	{
		var nal = itogForm.findChild("lineEditCash").text;
		itogForm.findChild("lineEditSdacha").setValue(nal-(сумма-скидка));	// Посчитаем сдачу
	}
}

      
function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
	var цена = getValue("ТОВАР__ЦЕНА");
	setValue("P1__ЦЕНА", цена);
}


function EventBeforeAddString()
{
	var result = true;
	var currentDate = new Date();
	var docDate = documents.getValue("ДАТА");
	if ((docDate.toLocaleDateString() != currentDate.toLocaleDateString()))
	{
		QMessageBox.warning(form, "Внимание!", "Дата документа устарела. Начните вводить продажу в новом документе.");
		result = false;
	}
	return result;
}


function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
	CalcDiscount();
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
	form.findChild("lineEditMenPhone").setEnabled(enabled);
	form.findChild("lineEditMenName").setEnabled(enabled);
	form.findChild("lineEditDiscount").setEnabled(enabled);
	form.findChild("pushButtonMenSearch").setEnabled(enabled);
	form.findChild("pushButtonAddMen").setEnabled(enabled);
	form.findChild("pushButtonClear").setEnabled(enabled);
}


function EventCalcTable()
{
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "P1__КОЛ" || barCodeReaded)		// Только при изменении количества 
	{
		EventAfterAddString();		// Обновим цену на всякий случай. Вдруг она изменилась с в промежуток времени между добавлением строки и проставлением количества
		if (getValue("P1__ЦЕНА") != 0)	// Если розничная цена указана
		{
			var кол = getOldValue("P1__КОЛ") + getValue("КР411__КОНКОЛ");			// Количество всего
			var сумма = getValue("P2__СУММА") - getValue("ДБ421__КОНСАЛЬДО");		// Сумма всего
			if (getValue("P1__КОЛ") > кол)
			{
				errorMessage = "Остаток меньше 0!";
			}
			// Посчитаем вторую проводку (по закупочной цене)
			var цена = 0;
			if (кол != 0)
				цена = сумма / кол;
			сумма =  getValue("P1__КОЛ") * цена;
			setValue("P2__СУММА", сумма);
			// Посчитаем первую проводку (по розничной цене)
			цена = getValue("P1__ЦЕНА");
			сумма = getValue("P1__КОЛ") * цена;
			setValue("P1__СУММА", сумма);
		}
		else
		{
			if (getValue("P1__КОЛ") != 0)
			{
				errorMessage = "Розничная цена позиции [" + getValue("ТОВАР__ИМЯ") + "] не определена!";
				scriptResult = false;
			}
		}
		CalcDiscount();
	}
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
	if (document.isEnabled())
	{
		barCodeReaded = true;
		var addStr = true;
		var saldo = document.getSaldo("411");
		var prepBarCode = barCode;
		prepBarCode = prepBarCode.replace(/^0+/,'').replace(/.$/,'');
		saldo.setQuan(true);
		if (prepBarCode.length > 5)
			saldo.query("товар.ШТРИХКОД = '" + barCode + "' AND сальдо.КОНКОЛ > 0", true);
		else
			saldo.query("товар.КОД = '" + prepBarCode + "' AND сальдо.КОНКОЛ > 0", true);
		saldo.setQuan(true);
	
		if (saldo.getRowCount() == 1)
		{
			saldo.lock(true);		// Если оказалась только одна позиция в остатках с таким штрих-кодом, то выберем ее
			saldo.getFormWidget().hide();
		}
		else
		{				// Иначе откроем окно с остатками и предложим пользователю уточнить позицию
			if (saldo.getRowCount() == 0)
			{
				app.showMessageOnStatusBar("В остатках не найдена позиция с таким штрих-кодом.");
				addStr = false;
			}
/*
			else
			{
				saldo.exec();
				if (!saldo.isFormSelected())
					addStr = false;	// Пользователь отказался от выбора позиции, добавлять строку не будем
				else
				{
					var tovarId = saldo.getValue("КОД_ТОВАР");
//		    		var barCodeMessage = new QMessageBox(form, "Внимание!", "Присвоить этот штрихкод выбранной позиции?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
//	    			if (barCodeMessage.exec() == QMessageBox.Yes)
					db.exec("UPDATE товар SET ШТРИХКОД = '" + barCode + "' WHERE КОД = " + tovarId);			
					saldo.lock(true);
				}
			}
*/
		}
		if (addStr)
		{
			var row = document.locateValue("P1__КРКОД", saldo.getId());
			if (row >= 0)	// Если такая позиция в документе уже есть
			{
				document.setCurrentRow(row);
				document.setValue("P1__КОЛ", document.getValue("P1__КОЛ") + 1);
				document.calculate();
			}
			else
			{			// Такой позиции в документе еще нет, добавим ее
				if (document.add())
				{
					document.setValue("P1__КОЛ", 1);
					document.calculate();
				}
			}
		}
		saldo.lock(false);			// Разблокируем справочник остатков, чтобы можно было в нем
	}
	barCodeReaded = false;
}


function EventCardCodeReaded(cardCode)
{ //Событие происходит после прочтения магнитной карты
	if ((!documents.getValue("ЧЕКОТБИТ") && document.isEnabled()) || app.isSA())	// Если чек еще не отбит
	{
		var command = "SELECT * FROM " + quotes(tableCards) + " WHERE trim(" + quotes(fieldCardName) + ") = '" + cardCode + "';";
		var cardQuery = db.execQuery(command);
		if (!cardQuery.first())
		{
			var command1 = "INSERT INTO " + quotes(tableCards) + " (ИМЯ) VALUES ('" + cardCode + "');";
			db.execQuery(command1);
			cardQuery = db.execQuery(command);
		}
		if (cardQuery.first())
		{
			var cardRecord = cardQuery.record();
			cardId = cardRecord.value(fieldCardId);
			cardName = cardRecord.value(fieldCardName);
			cardProc = cardRecord.value(fieldCardProc);
			form.findChild("lineEditCardName").setText(cardName);
			documents.setValue("КОД_КАРТОЧКИ", cardId);

			// Подсчитаем сумму продаж всего для этой карточки
//			var totSum = db.getValue("SELECT SUM(d.СУММА) AS СУММА FROM докатрибуты1 da INNER JOIN документы d ON da.КОД = d.КОД WHERE da.КОД_КАРТОЧКИ = " + cardId + " AND d.КОД != " + documents.getId() + ";") + documents.getValue("СУММА");
//			form.findChild("lineEditTotSum").setText(totSum);
			var totSum = CalcTotalDiscount(cardId);

			if (cardProc > 0)				// Если на карточке установлен какой-то конкретный процент скидки
				процентскидки = cardProc;		// то установим его
			else					// иначе
				процентскидки = 3;			// скидка будет по умолчанию

			// Посмотрим сумму продаж по таблице скидок
			var proc = db.getValue("SELECT ПРОЦЕНТ FROM скидки WHERE COALESCE(МИНСУММА, 0) <= " + totSum + " AND " + totSum + " < COALESCE(МАКССУММА, 0);");
			if (proc > процентскидки)
			{
				db.exec("UPDATE карточки SET СКИДКА = " + proc + " WHERE КОД = " + cardId + ";");
				QMessageBox.warning(form, "Внимание!", "Скидка изменена с " +  процентскидки + " на " + proc + "%.");
				процентскидки = proc;
			}

			CalcDiscount();
			document.saveChanges();
		}
	}	
}


function FindCard(cardId)
{
	cardName = "";
	if (cardId > 0)
	{
		var command = "SELECT * FROM " + quotes(tableCards) + " WHERE КОД = " + cardId + ";";
		var cardQuery = db.execQuery(command);
		if (cardQuery.first())
		{
			var cardRecord = cardQuery.record();
			cardName = cardRecord.value(fieldCardName);
			cardProc = cardRecord.value(fieldCardProc);
			if (cardProc > 0)				// Если на карточке установлен какой-то конкретный процент скидки
				процентскидки = cardProc;		// то установим его
			else					// иначе
				процентскидки = 3;			// скидка будет по умолчанию
		}	
	}
	form.findChild("lineEditCardName").setText(cardName);
}


function setNeedPrintCheck()
{
	needPrintCheck = true;		// Установить флаг, что нужно отпечатать чек
}


function PrintCheck()
{
	checkType = 1;
	document.setEnabled(false);
	document.setEnabled(!evaluateScript("printCheck.js"));
}


function BankTerminal()
{
	var сумма = Math.round(documents.getValue("СУММА") * 100);		// Применим округление, т.к. функция getValue может иногда возвращать значения типа 12.399999996 вместо 12.40 и я пока не могу ничего сделать
	if (!documents.getValue("ЧЕКОТБИТ") && сумма > 0)
	{
		document.setEnabled(false);
		if (!documents.getValue("БЕЗНАЛИЧНЫЕ"))
		{
			var terminal = app.getBankTerminal();
			if (app.bankTerminalIsValid())
			{
				if (terminal.process(1, сумма))
				{
					documents.setValue("БЕЗНАЛИЧНЫЕ", true);
					documents.setValue("НОМЕРКАРТЫ", terminal.getCardCode());
					documents.setValue("ДЕРЖКАРТЫ", terminal.getResultData("ИмяДержателяКарты"));
					document.saveChanges();
					needPrintCheck = true;
					bankTerminalExit = true;
					form.findChild("buttonOk").click();
				}
			}
		}
		else
			QMessageBox.warning(form, "Внимание!", "Платеж по этой продаже уже осуществлён.");
		if (!bankTerminalExit)
			document.setEnabled(true);
	}
}


function EventKeyPressed(key, modifiers)
{  // Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано
	if (key == Qt.Key_F8 && modifiers == 0)
	{
		form.findChild("buttonTerminal").click();
		return true;
	}
	return false;
}
