var tovarPhotoPath 	= db.getDictionaryPhotoPath("товар");
var fieldTovarId	= "ТОВАР__КОД"; 


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	// Установим пути к фотографиям
	table.setPhotoPath(tovarPhotoPath);		
	table.setPhotoIdField(fieldTovarId);

	table.setPhotoNameField("ТОВАР__ИМЯ");
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
// Здесь Вы можете вставить свой код
if (filter.length > 0)
	filter = filter + " AND ";
return filter + "\"докатрибуты123\".\"МОЖНОРАЗБИРАТЬ\"= true";
}
