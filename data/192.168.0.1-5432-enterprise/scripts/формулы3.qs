var form;
var firmId = 0;
var id;


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
//	form.findChild("advanceNumeric").returnPressed.connect(advanceSet);
	table.setDoSubmit(true);
	table.setPhotoEnabled(true);
	if (documents.getValue("ПРИНЯТ"))
		document.setEnabled(false);
}

/*
function advanceSet()
{
	setValue("P2__СУММА", form.findChild("advanceNumeric").text);
	table.getGrdTable().setFocus();
}
*/

function EventBeforeHideForm(form)
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
	if (!documents.getValue("ПРИНЯТ"))
	{
		var vw_peopleDict = getDictionary("vw_люди");
		documents.setValue("Комментарий", vw_peopleDict.getName());
		if (app.showYesNo("Это весь заказ?") == QMessageBox.Yes)
		{
			documents.setValue("ПРИНЯТ", true);

			var peopleDict = getDictionary("люди");
			peopleDict.setId(vw_peopleDict.getId());
			var phone = getDictionary("люди").getValue("ТЕЛЕФОН");
			if (phone.length > 0)
			{
				var message = "Принят заказ на сумму " + documents.getValue("СУММА") + " руб.";
				app.sendSMS(phone, message);
				app.getDictionary("vw_прайс").hide();
			}
		}
	}
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
// Здесь Вы можете вставить свой код
	setValue("P1__ЦЕНА", app.getDictionary("vw_прайс").getValue("МИНЦЕНА"));
	return true;
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код 
	var кол = getValue("P1__КОЛ");
	var цена = getValue("P1__ЦЕНА");
	setValue("ЦЕНА_РЕАЛИЗАЦИИ", цена)
	setValue("P1__СУММА", кол * цена);
}


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
// Здесь Вы можете вставить свой код
	documents.setValue("КОД_ЛЮДИ", getDictionary("vw_люди").getId());
}


function EventBeforeShowForm()
{ // Событие происходит перед открытием формы документа
// Здесь Вы можете вставить свой код
//  form.findChild("advanceNumeric").setText(getValue("P2__СУММА"));
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
	var result = false;
	var priceDict = app.getDictionary("vw_прайс");
	if (document.isVisible())
	{
		priceDict.exec();
		if (priceDict.isFormSelected())
		{
			getDictionary("прайс").setId(priceDict.getId());
			getDictionary("прайс").setMustShow(false);
			document.prepareValue("КОД_ФИРМЫ", priceDict.getValue("КОД_ФИРМЫ"));
			result = true;
		}
	}
	else
	{
		getDictionary("прайс").setId(priceDict.getId());
		result = true;
	}
	return result;
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


