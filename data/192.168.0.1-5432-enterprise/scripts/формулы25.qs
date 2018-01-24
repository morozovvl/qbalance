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
	if (queryName == "сальдо_накладных_расходов")
	{
/*
//		getDictionary("набор1").setId(record.КОД);
		getDictionary("товар").setValue(db.getValue("SELECT КОД_ТОВАР FROM набор1 WHERE КОД = " + record.КОД), "ЦЕНА", record.НОВЦЕНА);
		// Запишем кол-во, цену, сумму в проводку
    		document.prepareValue("P1__ДБКОД", record.КОД);
    		document.prepareValue("P1__КРКОД", record.КОД);
    		document.prepareValue("P1__КОЛ", record.КОЛ);
    		document.prepareValue("P1__ЦЕНА", record.ЦЕНА);
    		document.prepareValue("P1__СУММА", record.КОЛ*record.ЦЕНА);
    		document.prepareValue("P2__ДБКОД", record.КОД);
    		document.prepareValue("P2__КРКОД", record.КОД);
    		document.prepareValue("P2__КОЛ", record.КОЛ);
    		document.prepareValue("P2__ЦЕНА", record.НОВЦЕНА);
    		document.prepareValue("P2__СУММА", record.КОЛ*record.НОВЦЕНА);
		document.prepareValue("ЗАКЦЕНА", record.ЗАКЦЕНА);
		document.prepareValue("ПРОЦЕНТ", 100*(record.ЦЕНА - record.ЗАКЦЕНА) / record.ЗАКЦЕНА);
		document.prepareValue("НОВПРОЦЕНТ", 100*(record.НОВЦЕНА - record.ЗАКЦЕНА) / record.ЗАКЦЕНА);
		 // Сохраним проводку на сервере
		document.appendDocString();
*/
		var command = "SELECT v.КОД, v.ИМЯ, s.КОНСАЛЬДО AS САЛЬДО " +
			      "FROM sp_calcoborot('44', '01.01.2012', '31.01.2012') s INNER JOIN виды_расходов v ON s.КОД = v.КОД " +
			      "WHERE s.КОНСАЛЬДО <> 0 " +
			      "ORDER BY v.ИМЯ;"
	}
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
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


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
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


