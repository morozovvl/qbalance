var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldTovarId	= "ТОВАР__КОД"; 
var sales =		new Dictionary();
var labelQuan = 0;


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	// Установим пути к фотографиям
	table.setPhotoPath(tovarPhotoPath);		
	table.setPhotoIdField(fieldTovarId);
	table.setPhotoNameField("ТОВАР__ИМЯ");
	table.getFormWidget().buttonViewSales.clicked.connect(ViewSales);
}


function EventPreparePrintValues()
{ // Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа
// Здесь Вы можете вставить свой код
    var searchExpression = table.getSearchExpression("адрес");
    table.appendPrintValue("адрес", searchExpression); 
   return true;
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	filter = filter.replace(/\"товар\".\"ИМЯ\"/g, "(товар.ИМЯ || товар.ШИФР_ПО_КАТАЛОГУ || товар.АРТИКУЛ)");
	return filter;
}


function ViewSales()
{
  evaluateScript("viewsales.js", getValue("КОД_ТОВАР"));
}


function PrepareBarCodeData()
{ // Вызов этой функции происходит перед печатью штрих-кода. Функция должна вернуть значение штрих-кода.
	table.appendPrintValue("ТОВАР_КОД", table.getValue("ТОВАР__КОД"));
	table.appendPrintValue("ТОВАР_ИМЯ", table.getValue("ТОВАР__ИМЯ"));
	table.appendPrintValue("ТОВАР_ЦЕНА", table.getValue("ТОВАР__ЦЕНА"));
	return "00000" + getValue(fieldTovarId);
}


function EventKeyPressed(key, modifiers)
{  // Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано
//	if (key == Qt.Key_F5 && modifiers == Qt.ControlModifier)
	if (key == Qt.Key_F5 && modifiers == 0)
	{
//		table.printLabel("Ценник", 1);
		labelQuan = table.getValue("КОНКОЛ");
		if (labelQuan > 0)
		{
			evaluateScript("печать_этикеток.js");
			return true;
		}
	}
	return false;
}



