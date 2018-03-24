var tovar;
var firmId = 0;
var agentName = "";
var id = 0;
var rowId;		// Строка, в которой находится первое наименование прайса
var url = "";
var pictureId = 0;

var exitKeyPressed;	// Флаг нажатия кнопки, прерывающей загрузку документа 

var colId;
var colName;
var colArticulOEM;
var colArticul;
var colUnit;
var colPrice;
var colUpack;
var colNalich;
var colProizv;
var colCountry;


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	if (app.isSA())
	{
		form.getButtonLoad().show();		// Включим кнопку "Загрузить документ" на форме
	}
	else
	{
		form.setEnabled(false);
		table.setReadOnly(true);
	}
	table.setPhotoEnabled(true);
	tovar = getDictionary("товар");
	if (!table.isDefaultForm())
	{
		 table.getFormWidget().findChild("lineEditMinPrice").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditMaxPrice").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditArticulOEM").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditArticul").returnPressed.connect(cmdRequery);
		 table.getFormWidget().findChild("lineEditProizv").returnPressed.connect(cmdRequery);
	}
}


function cmdRequery()
{
	table.getForm().cmdRequery()
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	filter = filter.replace(/\"прайс\".\"ИМЯ\"/g, "(прайс.КОДВПРАЙСЕ || прайс.ИМЯ || прайс.ШИФР_ПО_КАТАЛОГУ || прайс.АРТИКУЛ || прайс.ПРОИЗВОДИТЕЛЬ)");
	var val = table.getForm().getSearchValue('прайс').toString().trim();
	var priceId = parseInt(table.getForm().getSearchValue('прайс'));
	if (!isNaN(priceId) && priceId.toString() == val)
	{
		filter = "прайс.КОДВПРАЙСЕ = '" + priceId + "'";
		var firmName = table.getForm().getSearchValue('фирмы');
		if (firmName.length)
		{
			if (filter.length > 0)
				filter = filter + " AND ";
			filter = filter + "фирмы.ИМЯ ILIKE '%" + firmName + "%'";
		}
	}

	var minPrice = table.getFormWidget().findChild("lineEditMinPrice").text;
	if (minPrice.length > 0)
		minPrice = parseFloat(minPrice);
	var maxPrice = table.getFormWidget().findChild("lineEditMaxPrice").text;
	if (maxPrice.length > 0)
		maxPrice = parseFloat(maxPrice);
	var articul = table.getFormWidget().findChild("lineEditArticul").text.trim();
	var articulOEM = table.getFormWidget().findChild("lineEditArticulOEM").text.trim();
	var proizv = table.getFormWidget().findChild("lineEditProizv").text.trim();
	var priceDate = new Date();
	priceDate.setDate(priceDate.getDate() - app.getConst("АктуальностьПрайсов"));
	if (filter.length > 0)
		filter = filter + " AND ";
	filter = filter + "ДАТА >= '" + priceDate.toLocaleDateString() + "'";
	if (minPrice.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "МИНЦЕНА >= " + minPrice;
	}
	if (maxPrice.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "МИНЦЕНА <= " + maxPrice;
	}
	if (articul.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		articul = articul.replace(" ", "%");
		filter = filter + "прайс.АРТИКУЛ LIKE '%" + articul + "%'";
	}
	if (articulOEM.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		articulOEM = articulOEM.replace(" ", "%");
		filter = filter + "прайс.ШИФР_ПО_КАТАЛОГУ LIKE '%" + articulOEM + "%'";
	}
	if (proizv.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "прайс.ПРОИЗВОДИТЕЛЬ LIKE '%" + proizv + "%'";
	}
	return filter;
}


function EventImport(form)
{ // Событие происходит при нажатии кнопки <Загрузить документ>
	evaluateScript("loadPrice.js");
}


function PreparePictureUrl()
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
  // Функция должна вернуть url фотографии.
	
	firmId = table.getValue("КОД_ФИРМЫ");
	table.setPhotoIdField("КОДВПРАЙСЕ");
	pictureId = table.getValue("КОДВПРАЙСЕ");
	evaluateScript("getPictureUrl.js");	// Запустим локальный скрипт
	return url;
}


function EventAfterRowChanged()
{ // Событие происходит после перемещения на другую строку
//	CopyFile();					// Скопируем файл с фотографией
	// скопируем фотографию, если форма видимая
	var nomId = table.getValue("КОД_ТОВАР");
	if (nomId > 0)
	{
		var toFileName = tovar.getPhotoPath() + "/" + nomId + ".jpg";
		table.getPhotoFile(toFileName);
	}
}

function EventCalcTable()
{
	db.exec("DELETE FROM история WHERE ТАБЛИЦА = 'прайс' AND КОДСТРОКИ = " + table.getId() + ";");
}
