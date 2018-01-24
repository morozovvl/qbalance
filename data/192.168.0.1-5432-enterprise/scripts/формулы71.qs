var form;
var tovar;		// справочник товара
var addr;		// справочник адресов
var lastAddr;	// справочник хранения последних адресов


var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldDocumentTovarId	= "ТОВАР__КОД"; 
var fieldSaldoTovarId	= db.getObjectName("набор1.КОД_ТОВАР"); 
var tableGroup	= getDictionary("группы");

var drvFR = 0;
var lastMaxDocId = 0;


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
		drvFR = app.getDrvFR();

	form = table.getFormWidget();

	tovar = document.getDictionary("товар");
	lastAddr = document.getDictionary("посладрес");
	addr = document.getDictionary("адрес");

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField(fieldDocumentTovarId);
	document.setPhotoEnabled(true);

	table.setPhotoNameField("ТОВАР__ИМЯ");
	tableGroup.query();

	// Если это не системный администратор, то запретим удаление документов
	if (!app.isSA())
		documents.getFormWidget().findChild("buttonDelete").setVisible(false);
	lastMaxDocId = db.getValue("SELECT MAX(КОД) FROM документы WHERE (ОПЕР = 1 OR ОПЕР = 71) AND ДАТА < current_date;");
}


function EventBeforeAddString()
{ //Событие происходит перед добавлением строки в документ
	var result = true;
	var currentDate = new Date();
	if ((documents.getValue('ДАТА').toLocaleDateString() != currentDate.toLocaleDateString()))
	{
		QMessageBox.warning(form, "Внимание!", "Дата документа устарела. Начните вводить продажу в новом документе.");
		result = false;
	}
	else
	{
		result = false;
		tovar.exec();
		tovar.setMustShow(false);
		if (tovar.isFormSelected())
		{
			var tovarId = tovar.getId();
			lastAddr.query("КОД_ТОВАР=" + tovarId);
			if (lastAddr.getRowCount() > 0)
			{
				var addrId = lastAddr.getValue("КОД_АДРЕС");
				addr.setFormTitle("Последний (рекомендуемый) адрес хранения");
				addr.getForm().clearAllComboBoxes();
			}
			else
			{
				addr.setFormTitle("Введите адрес хранения");
			}
			addr.setId(addrId);
			addr.exec();
			addr.setMustShow(false);
			if (addr.isFormSelected())
			{
				result = true;
			}
		}	
	}
	return result;
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
	var цена = getValue("ТОВАР__ЦЕНА");
	setValue("P1__ЦЕНА", цена);
	return true;
}


function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
	return true;
}


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
	// Если это не системный администратор, то запретим редактирование документа продажи не сегодняшней датой
	var currentDate = new Date();
	if (!app.isSA() && (documents.getValue("СУММА") != 0 || documents.getValue('ДАТА').toLocaleDateString() != currentDate.toLocaleDateString()) && documents.getValue("ЧЕКОТБИТ"))
		document.setEnabled(false);
	else
		document.setEnabled(true);
}


function EventBeforeHideForm(form)
{ // Событие происходит перед закрытием формы документа
	PrintCheck();
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
	var кол = getValue("P1__КОЛ");
	var цена = getValue("P1__ЦЕНА");
	var сумма = getValue("P1__СУММА");
	if (getCurrentFieldName() == "P1__СУММА" && кол != 0)
  		цена = сумма / кол;
	else
		сумма = кол * цена;
	setValue("P1__КОЛ", кол);
	setValue("P1__ЦЕНА", цена);
	setValue("P1__СУММА", сумма);
}


function PrintCheck()
{
	checkType = 2;
	evaluateScript("printCheck.js");
}

