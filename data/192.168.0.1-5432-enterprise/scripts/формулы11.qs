var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldDocumentTovarId	= "ТОВАР__КОД"; 
var fieldSaldoTovarId	= db.getObjectName("набор1.КОД_ТОВАР"); 
var debtSum = 0;
var limit = 0;



function EventAfterCalculate()
{ // Событие происходит после вычисления в ячейке
// Здесь Вы можете вставить свой код
}


function EventAfterHideForm()
{ // Событие происходит после закрытия формы документа
// Здесь Вы можете вставить свой код
}


function EventAfterShowForm()
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
	ShowDebt();
}


function ShowDebt()
{
	var contrAgentId =  getDictionary("организации").getId();
	limit = getDictionary("организации").getValue("ЛИМИТ");
	if (contrAgentId > 0)
	{
		debtSum = db.getValue("SELECT COALESCE(КОНСАЛЬДО, 0) FROM сальдо WHERE СЧЕТ = '60' AND КОД = " + contrAgentId);
		if (typeof debtSum == 'undefined')
			debtSum = 0;
		table.getFormWidget().findChild("myNumericEditDebt").setText(debtSum);
	}
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
	var result = false;
	if (debtSum < limit)
		result = true;
//	else
//		app.showError("Задолженность превышает лимит!");
	return result;
}


function EventBeforeHideForm()
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
	documents.setValue("КОММЕНТАРИЙ", getDictionary("организации").getValue("имя"));
}


function EventBeforeShowForm()
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
}


function EventCloseForm()
{ // Событие происходит перед удалением формы документа
// Здесь Вы можете вставить свой код
}


function EventExport()
{ // Событие происходит при нажатии кнопки <Экспорт>
// Здесь Вы можете вставить свой код
}


function EventImport()
{ // Событие происходит при нажатии кнопки <Импорт>
// Здесь Вы можете вставить свой код
}


function EventInitForm()
{ // Событие происходит сразу после создания формы документа

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField(fieldDocumentTovarId);

	// Установим фотографии для справочника остатков товара
	document.getSaldo("411").setPhotoIdField(fieldSaldoTovarId);
	document.getSaldo("411").setPhotoPath(tovarPhotoPath);
	document.getSaldo("411").setFilter("адрес.ИМЯ NOT ILIKE '%Брак%'");

	var bankDict = getDictionary("банки");
	bankDict.setId(app.getConst("КодГлБанка"));
}


function EventKeyPressed(keyEvent)
{ // Событие происходит при нажатии любой кнопки на форме. Параметр keyEvent имеет тип QKeyEvent
// Здесь Вы можете вставить свой код
}


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
	ShowDebt();
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
// Здесь Вы можете вставить свой код
}


function PreparePictureUrl(object)
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
	var цена = getValue("ТОВАР__ЦЕНА");
	setValue("P1__ЦЕНА", цена);
}



function EventCalcTable()
{
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "P1__КОЛ")		// Только при изменении количества 
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
			if (debtSum > limit)
			{
				errorMessage = "Задолженность превышает лимит!";
//				scriptResult = false;
//				table.restoreOldValues();
			}
		}
		else
		{
			if (getValue("P1__КОЛ") != 0)
			{
				errorMessage = "Розничная цена позиции [" + getValue("ТОВАР__ИМЯ") + "] не определена!";
				scriptResult = false;
			}
		}
		ShowDebt();
	}
}







