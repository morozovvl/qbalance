var priceDict;
var form;
var firmId = 0;
var id;


function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	priceDict = app.getDictionary("vw_прайс");
	form.findChild("advanceNumeric").returnPressed.connect(advanceSet);
	table.setDoSubmit(true);
	table.setPhotoEnabled(true);
}


function advanceSet()
{
	setValue("P2__СУММА", form.findChild("advanceNumeric").text);
	table.getGrdTable().setFocus();
}


function EventBeforeHideForm(form)
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
	documents.setValue("Комментарий", getDictionary("vw_люди").getName());
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
	setValue("P1__ЦЕНА", priceDict.getValue("МИНЦЕНА"));
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
	setValue("ЦЕНА_РЕАЛИЗАЦИИ", цена)
	setValue("P1__СУММА", кол * цена);
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


function EventBeforeShowForm()
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
  form.findChild("advanceNumeric").setText(getValue("P2__СУММА"));
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
	var result = false;
	priceDict.exec();
	if (priceDict.isFormSelected())
	{
		getDictionary("прайс").setId(priceDict.getId());
		getDictionary("прайс").setMustShow(false);
		document.prepareValue("КОД_ФИРМЫ", priceDict.getValue("КОД_ФИРМЫ"));
		result = true;
	}
	return result;
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


function EventKeyPressed(key, modifiers)
{ // Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано
// Здесь Вы можете вставить свой код
return false;
}


function EventAfterShowNextDicts()
{ // Событие происходит после показа всех необходимых справочников при добавлении строки в документ
// Здесь Вы можете вставить свой код
//	getDictionary("прайс").setId(priceDict.getId());
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


function PreparePictureUrl()
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
	firmId = table.getValue("ПРАЙС__КОД_ФИРМЫ");
	id = table.getValue("ПРАЙС__КОДВПРАЙСЕ");
	table.setPhotoIdField("ПРАЙС__КОДВПРАЙСЕ");
	evaluateScript("getPictureUrl.js");	// Запустим локальный скрипт
	return url;
}


function EventImport()
{ // Событие происходит при нажатии кнопки <Импорт>
// Здесь Вы можете вставить свой код
}


function EventPreparePrintValues()
{ // Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа
// Здесь Вы можете вставить свой код
}


