var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldTovarId	= "ТОВАР__КОД"; 


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	// Установим пути к фотографиям
	table.setPhotoPath(tovarPhotoPath);		
	table.setPhotoIdField(fieldTovarId);
	table.setPhotoNameField("ТОВАР__ИМЯ");
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


