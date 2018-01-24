function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
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
return true;
}


function EventAfterShowForm(form)
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
}


function EventAppendFromQuery(queryName, record)
{ // Вызывается при добавлении каждой новой записи из запроса. Если готового запроса на сервере нет, то тогда вызывается один раз и скрипт сам должен создать и обработать запрос.
// Здесь Вы можете вставить свой код
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
	var кол = getValue("P1__КОЛ");
	var цена = getValue("P1__ЦЕНА");
	var сумма = getValue("P1__СУММА");

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


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
// Здесь Вы можете вставить свой код
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
// Здесь Вы можете вставить свой код
return "";
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
//	app.debug(3, "function EventBarCodeReaded(barCode)");
//	barCodeReaded = true;
	var addStr = true;
	var nomDict = getDictionary("товар");
	nomDict.query("товар.ШТРИХКОД = '" + barCode + "'", true);
	
	if (nomDict.getRowCount() == 1)
		nomDict.lock(true);		// Если оказалась только одна позиция в остатках с таким штрих-кодом, то выберем ее
	else
	{				// Иначе откроем окно с остатками и предложим пользователю уточнить позицию
		nomDict.exec();
		if (!nomDict.isFormSelected())
			addStr = false;	// Пользователь отказался от выбора позиции, добавлять строку не будем
		else
		{
			var tovarId = nomDict.getId();
	    		var barCodeMessage = new QMessageBox(form, "Внимание!", "Присвоить этот штрихкод выбранной позиции?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), form);
	    		if (barCodeMessage.exec() == QMessageBox.Yes)
				db.exec("UPDATE товар SET ШТРИХКОД = '" + barCode + "' WHERE КОД = " + tovarId);			
			nomDict.lock(true);
		}
	}
	if (addStr)
	{
		var row = document.locateValue("P1__ДБКОД", nomDict.getId());
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
	nomDict.lock(false);			// Разблокируем справочник остатков, чтобы можно было в нем
	barCodeReaded = false;
}


function GetFilter()
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
// Здесь Вы можете вставить свой код
return "";
}


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
return true;
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


function EventAfterShowNextDicts()
{ // Событие происходит после показа всех необходимых справочников при добавлении строки в документ
// Здесь Вы можете вставить свой код
return true;
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


function EventPreparePrintValues()
{ // Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа
// Здесь Вы можете вставить свой код
return true;
}


