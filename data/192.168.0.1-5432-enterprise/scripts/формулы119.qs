var form;
var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldDocumentTovarId	= "ТОВАР__КОД"; 
var fieldSaldoTovarId	= db.getObjectName("набор1.КОД_ТОВАР"); 


function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
return true;
}


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	form.findChild("lineEditComment").returnPressed.connect(EventBeforeHideForm);

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField(fieldDocumentTovarId);
	document.setPhotoEnabled(true);


	// Установим фотографии для справочника остатков товара
	document.getSaldo("411").setPhotoIdField(fieldSaldoTovarId);
	document.getSaldo("411").setPhotoPath(tovarPhotoPath);
	
	table.setPhotoNameField("ТОВАР__ИМЯ");


}


function EventBeforeHideForm()
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
	documents.setValue("КОММЕНТАРИЙ", form.findChild("lineEditComment").text);
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
	setValue("P1__ЦЕНА", getValue("ТОВАР__ЦЕНА"));
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
// Здесь Вы можете вставить свой код
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "P1__КОЛ")		// Только при изменении количества 
	{
		EventAfterAddString();		// Обновим цену на всякий случай. Вдруг она изменилась с в промежуток времени между добавлением строки и проставлением количества
		var кол = getOldValue("P1__КОЛ");
		var всегоКол1 = getValue("КР411__КОНКОЛ") + кол;
		var всегоСальдо1 = getValue("КР411__КОНСАЛЬДО") + getOldValue("P1__СУММА");
		var всегоСальдо2 = getOldValue("P2__СУММА") -  getValue("КР421__КОНСАЛЬДО");
		var цена = getValue("ТОВАР__ЦЕНА");
		if (всегоКол1 != 0 && цена == getValue("P1__ЦЕНА"))
		{
			кол = getValue("P1__КОЛ");
			setValue("P1__ЦЕНА", цена);
			setValue("P1__СУММА", кол * цена);
			setValue("P2__КОЛ", кол);
			var цена2 = (всегоСальдо1 - всегоСальдо2) / всегоКол1;
			setValue("P2__ЦЕНА", цена2);
			setValue("P2__СУММА", кол * цена2);
			if (кол > всегоКол1)
			{
				errorMessage = "Остаток меньше 0!";
			}
		}
	}
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


function EventBeforeShowForm()
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
	form.findChild("lineEditComment").setText(documents.getValue("КОММЕНТАРИЙ").toString());
	// Если это не системный администратор, то запретим редактирование документа продажи не сегодняшней датой
	var currentDate = new Date();
	if (app.isSA() || (documents.getValue('ДАТА').toLocaleDateString() == currentDate.toLocaleDateString()))
		document.setEnabled(true);
	else
		document.setEnabled(false);

}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
	if (form.findChild("lineEditComment").text.length == 0)
	{
		QMessageBox.warning(form, "Документ", "Укажите в комментарии, куда списывается товар.");
		return false;
	}
	return true;
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


