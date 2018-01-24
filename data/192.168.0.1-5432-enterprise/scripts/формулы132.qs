function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	getDictionary("saldo411").setFilter("КОНКОЛ = 0");
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
}


function EventCardCodeReaded(cardCode)
{ // Событие происходит после прочтения магнитной карты
// Здесь Вы можете вставить свой код
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
// Здесь Вы можете вставить свой код
	setValue("P1__СУММА", getDictionary("saldo411").getValue("САЛЬДО__КОНСАЛЬДО"));
	document.calculate();
	return true;
}


function EventAfterShowForm(form)
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
}


function EventAppendFromQuery(queryName, record)
{ // Вызывается при добавлении каждой новой записи из запроса. Если готового запроса на сервере нет, то тогда вызывается один раз и скрипт сам должен создать и обработать запрос.
// Здесь Вы можете вставить свой код
	if (queryName == "__нулевые_остатки__")
	{
		var command = "SELECT КОД, КОНСАЛЬДО FROM сальдо WHERE СЧЕТ = '411' AND КОНКОЛ = 0 AND КОНСАЛЬДО <> 0";
		var zakazQuery = db.execQuery(command);
		if (zakazQuery.first())
		{
			var progress = ProgressDialog("Заполнение заказа. Ожидайте...");
			progress.show();
			progress.setMaximum(zakazQuery.size());
			do
			{
				var zakazRecord = zakazQuery.record();
	    			document.prepareValue("P1__КРКОД", zakazRecord.value("КОД"));
				document.prepareValue("P1__СУММА", zakazRecord.value("КОНСАЛЬДО"));
		 		// Сохраним проводку на сервере
				document.appendDocString();
				progress.setValue(zakazQuery.at());
			} while (zakazQuery.next());
			progress.hide();
		}
	}
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
	scriptResult = true;
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
// Здесь Вы можете вставить свой код
return filter;
}


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
// Здесь Вы можете вставить свой код
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
// Здесь Вы можете вставить свой код
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
// Здесь Вы можете вставить свой код
}


function EventBeforeRowChanged()
{ // Событие происходит до перемещения на другую строку
// Здесь Вы можете вставить свой код
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
}


