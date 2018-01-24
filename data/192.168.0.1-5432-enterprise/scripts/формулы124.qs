var lastAddr = getDictionary("посладрес");
var addr = getDictionary("адрес");
var tovarPhotoPath = db.getDictionaryPhotoPath("товар");
var barCodeReaded = false;


function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	var ostDict = getDictionary("vw_saldo402");
	ostDict.setOrderClause("ДОКУМЕНТЫ123__ИМЯ");
	ostDict.setPhotoEnabled(true);
	ostDict.setPhotoPath(tovarPhotoPath);		
	ostDict.setPhotoIdField("ТОВАР__КОД");
	ostDict.setIsSaldo(true);

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField("ТОВАР__КОД");
	document.setPhotoEnabled(true);

}


function EventBeforeHideForm(form)
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
}


function EventBeforeLinePrint(strNum)
{ // Вызывается до печати очередной строки в документе
// Здесь Вы можете вставить свой код
}


function EventAfterRowChanged()
{ // Событие происходит после перемещения на другую строку
// Здесь Вы можете вставить свой код
return "";
}


function EventCardCodeReaded(cardCode)
{ // Событие происходит после прочтения магнитной карты
// Здесь Вы можете вставить свой код
return "";
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
// Здесь Вы можете вставить свой код
	var цена = getValue("ТОВАР__ЦЕНА");
	setValue("P2__ЦЕНА", цена);
	return true;
}


function EventAfterShowForm(form)
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "P1__КОЛ" || barCodeReaded)		// Только при изменении количества 
	{
		EventAfterAddString();		// Обновим цену на всякий случай. Вдруг она изменилась с в промежуток времени между добавлением строки и проставлением количества
		if (getValue("P2__ЦЕНА") != 0)	// Если розничная цена указана
		{
			var кол = getOldValue("P1__КОЛ") + getValue("КР402__КОНКОЛ");		// Количество всего
			var сумма = getOldValue("P1__СУММА") + getValue("КР402__КОНСАЛЬДО");		// Сумма всего
			if (getValue("P1__КОЛ") > кол)
			{
				errorMessage = "Остаток меньше 0!";
			}
			setValue("P2__КОЛ", getValue("P1__КОЛ"));
			// Посчитаем первую проводку (по закупочной цене)
			var цена = 0;
			if (кол != 0)
				цена = сумма / кол;
			сумма =  getValue("P1__КОЛ") * цена;
			setValue("P1__ЦЕНА", цена);
			setValue("P1__СУММА", сумма);
			// Посчитаем вторую проводку (по розничной цене)
			цена = getValue("P2__ЦЕНА");
			сумма = getValue("P2__КОЛ") * цена;
			setValue("P2__СУММА", сумма);
		}
		else
		{
			if (getValue("P1__КОЛ") != 0)
			{
				errorMessage = "Розничная цена позиции [" + getValue("ТОВАР__ИМЯ") + "] не определена!";
				scriptResult = false;
			}
		}
	}
	return "";
}


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
// Здесь Вы можете вставить свой код
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
// Здесь Вы можете вставить свой код
return "";
}


function GetFilter()
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
// Здесь Вы можете вставить свой код
return "";
}


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
	getDictionary("товар").setMustShow(false);
	getDictionary("адрес").setMustShow(false);
	getDictionary("посладрес").setMustShow(false);
	getDictionary("посладрес").setDoSubmit(true);
	getDictionary("saldo402").setMustShow(false);
	getDictionary("vw_saldo402").setMustShow(true);
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
	return true;
}


function EventAfterShowNextDicts()
{ //Событие происходит после показа всех необходимых справочников при добавлении строки в документ;
// Здесь Вы можете вставить свой код
	var result = false;
	var tovarId = getDictionary("товар").getId();
	lastAddr.query("КОД_ТОВАР=" + tovarId);
	if (lastAddr.getRowCount() > 0)
	{
		var addrId = lastAddr.getValue("КОД_АДРЕС");
		addr.setId(addrId);
		addr.setFormTitle("Последний (рекомендуемый) адрес хранения");
		addr.getForm().clearAllComboBoxes();
	}
	else
	{
		addr.setFormTitle("Введите адрес хранения");
	}
	addr.exec();
	if (addr.isFormSelected())
	{
		addr.lock();
		setLastAddr(tovarId);

		getDictionary("saldo402").setId(getDictionary("vw_saldo402").getId());
		getDictionary("saldo402").lock();

		result = true;
	}
	return result;
}


function setLastAddr(tovarId)
{ // сохранить последний адрес хранения
	var addrName = addr.getName();
	var firstChar = addrName.substring(0, 1);
	if ( firstChar == "1" || firstChar == "2" || firstChar == "3")	// Если адрес начинается с 1, 2 или 3
	{
//		lastAddr.query("КОД_ТОВАР=" + tovarId);
		if (lastAddr.getRowCount() > 0)
			lastAddr.setValue("КОД_АДРЕС", addr.getId(), 0);
		else
			lastAddr.getId();	// В справочнике последних адресов нет сочетания для этой позиции товара и этого адреса
					// поэтому установим такое сочетание просто прочитав Id 
					// При этом код товара и код адреса в этом сочетании установятся автоматически
	}
}


function EventAfterLinePrint(strNum)
{ // Вызывается после печати очередной строки в документе
// Здесь Вы можете вставить свой код
}


function EventBeforeDeleteString()
{ // Событие происходит перед удалением строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventAfterCalculate()
{ // Событие происходит после вычисления в ячейке
// Здесь Вы можете вставить свой код
}


function EventExport()
{ // Событие происходит при нажатии кнопки <Экспорт>
// Здесь Вы можете вставить свой код
}


function EventCloseForm(form)
{ // Событие происходит перед удалением формы документа
// Здесь Вы можете вставить свой код
}


function EventPhotoLoaded()
{ // Событие происходит после загрузки фотографии из Интернета
// Здесь Вы можете вставить свой код
return "";
}


function EventAfterHideForm(form)
{ // Событие происходит после закрытия формы документа
// Здесь Вы можете вставить свой код
}


function EventKeyPressed(keyEvent)
{ // Событие происходит при нажатии любой кнопки на форме. Параметр keyEvent имеет тип QKeyEvent
// Здесь Вы можете вставить свой код
}


function PreparePictureUrl(object)
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
}


function EventImport()
{ // Событие происходит при нажатии кнопки <Импорт>
// Здесь Вы можете вставить свой код
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
//	app.debug(3, "function EventBarCodeReaded(barCode)");

	barCodeReaded = true;
	var addStr = true;
	var saldo = getDictionary("vw_saldo402");
	saldo.query("товар.ШТРИХКОД = '" + barCode + "'", true);
	
	if (saldo.getRowCount() == 1)
		saldo.lock(true);		// Если оказалась только одна позиция в остатках с таким штрих-кодом, то выберем ее
	else
	{				// Иначе откроем окно с остатками и предложим пользователю уточнить позицию
		if (saldo.getRowCount() == 0)
			app.showMessageOnStatusBar("В остатках не найдена позиция с таким штрих-кодом.");

		saldo.exec();
		if (!saldo.isFormSelected())
			addStr = false;	// Пользователь отказался от выбора позиции, добавлять строку не будем
		else
		{
		
			var tovarId = saldo.getValue("КОД_ТОВАР");
//	    		var barCodeMessage = new QMessageBox(form, "Внимание!", "Присвоить этот штрихкод выбранной позиции?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
//	    		if (barCodeMessage.exec() == QMessageBox.Yes)
			db.exec("UPDATE товар SET ШТРИХКОД = '" + barCode + "' WHERE КОД = " + tovarId);			
			
			saldo.lock(true);
		}
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
		document.saveChanges();
	}
	saldo.lock(false);			// Разблокируем справочник остатков, чтобы можно было в нем
	barCodeReaded = false;
}



function PrepareBarCodeData()
{ // Вызов этой функции происходит перед печатью штрих-кода. Функция должна вернуть значение штрих-кода.
	table.appendPrintValue("ТОВАР_КОД", table.getValue("ТОВАР__КОД"));
	table.appendPrintValue("ТОВАР_ИМЯ", table.getValue("ТОВАР__ИМЯ"));
	table.appendPrintValue("ТОВАР_ЦЕНА", table.getValue("ТОВАР__ЦЕНА"));
	return "00000" + table.getValue("ТОВАР__КОД");
}



function EventKeyPressed(key, modifiers)
{  // Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано
//	if (key == Qt.Key_F5 && modifiers == Qt.ControlModifier)
	if (key == Qt.Key_F5 && modifiers == 0)
	{
//		table.printLabel("Ценник", 1);
		labelQuan = table.getValue("P1__КОЛ");
		if (labelQuan > 0)
		{
			evaluateScript("печать_этикеток.js");
			return true;
		}
	}
	return false;
}

