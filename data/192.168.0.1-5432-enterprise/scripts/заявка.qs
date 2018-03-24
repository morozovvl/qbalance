var nomDict;
var priceDict;
var form;
var sootvForm;
var ostDict;

var sootvFormName = "соответствие";
var url = "";
var firmId = 0;
var id = 0;

var fieldIdTovar = 	db.getObjectName("заявка.КОД_ТОВАР");
var fieldIdFirmTovar = 	db.getObjectName("заявка.КОДВПРАЙСЕ");
var fieldIdFirm = 	db.getObjectName("заявка.КОД_ФИРМЫ");
var priceSearch = 0;
var priceSearchColumnsInitialized = false;
var sales =		new Dictionary();
var salesGrdTable;
var newQuan = 0;
var pictureId = 0;
var currentRowId = 0;


function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	table.setOrderClause("ТОВАР__ИМЯ, ФИРМЫ__ИМЯ, ИМЯВПРАЙСЕ");

	nomDict = app.getDictionaries().getDictionary("товар");
//	nomDict.setForm("поиск_соответствий");
//	nomDict.getFormWidget().setWindowTitle("Товар");

//	priceDict = app.getDictionaries().getDictionary("прайс");
//	priceDict.setForm("поиск_соответствий");
//	priceDict.getFormWidget().setWindowTitle("Прайс");

	firmDict = app.getDictionaries().getDictionary("фирмы");
	sootvForm = app.createNewForm(sootvFormName);
	sootvForm = sootvForm.getFormWidget();
	
	if (!table.isDefaultForm())
	{
		form.buttonZakaz.clicked.connect(Zakaz);
		form.buttonSearch.clicked.connect(PriceSearch);
		form.buttonCalc.clicked.connect(RecalcAll);
		form.buttonViewSales.clicked.connect(ViewSales);
	}
	priceSearch = new Dictionary();
	priceSearch.open("", "аналоги");
	ostDict = app.getDictionaries().getDictionary("vw_saldo411_1");
//	ostDict.getForm().clearAllComboBoxes();
	salesGrdTable = form.findChild("salesTableView");
	salesGrdTable.setEssence(ostDict);
	salesGrdTable.setConfigName("salesTableView");
	salesGrdTable.setColumnsHeaders();
}


function Zakaz()
{
	db.exec("SELECT sp_распределитьзаказ();");
	table.query();
}


function PriceSearch()
{ // Функция для поиска соответствий в прайсе
	var command = "";
	var searchTable = "прайс";
	var firmId = 0;
	var firmDict = getDictionary("фирмы");
	var firmExpression = "";
	if (priceSearch.getRowCount() > 0)
	{
	  priceSearch.getSearchExpression("фирмы");
	  if (firmExpression.length > 0)
	  {
		firmDict.queryName(firmExpression);
		if (firmDict.getRowCount() == 1)
			  firmId = firmDict.getId();
	  }
	}
	
	var expression = table.getValue("ТОВАР__ИМЯ").trim() + " " + table.getValue("ТОВАР__ШИФР_ПО_КАТАЛОГУ").trim() + " " + table.getValue("ТОВАР__АРТИКУЛ").trim();
	priceSearch.setFormTitle(expression + " Цена:" + table.getValue("ТОВАР__ЦЕНА"));
	command = "SELECT p.*, s.ВЕС FROM search_in_price('" + expression + "', '" + searchTable + "') s INNER JOIN (SELECT p.*, f.ИМЯ AS ФИРМЫ_ИМЯ FROM прайс p INNER JOIN фирмы f ON p.КОД_ФИРМЫ = f.КОД WHERE f.ПРАЙС_АКТУАЛЕН) p ON s.КОД = p.КОД WHERE COALESCE(p.КОД_ТОВАР, 0) = 0"
	if (firmId > 0)
	  command = command + " AND p.КОД_ФИРМЫ = " + firmId;
	priceSearch.setSqlCommand(command);
	priceSearch.setOrderClause("s.ВЕС DESC, p.МИНЦЕНА ASC");
	priceSearch.query();
	priceSearch.getGrdTable().appendColumnDefinition(1, "ФИРМЫ_ИМЯ", "Поставщик", true);
	priceSearch.getGrdTable().appendColumnDefinition(2, "ИМЯ", "Наименование", true);
	priceSearch.getGrdTable().appendColumnDefinition(3, "АРТИКУЛ", "Артикул", true);
	priceSearch.getGrdTable().appendColumnDefinition(4, "ШИФР_ПО_КАТАЛОГУ", "Артикул ОЕМ", true);
	priceSearch.getGrdTable().appendColumnDefinition(5, "ЕДИЗМ", "Ед.Изм.", true);
	priceSearch.getGrdTable().appendColumnDefinition(6, "МИНЦЕНА", "Цена", true);
	priceSearch.getGrdTable().appendColumnDefinition(7, "ДАТА", "Дата", true);
	priceSearch.getGrdTable().appendColumnDefinition(8, "НАЛИЧИЕ", "Наличие", true);
	priceSearch.getGrdTable().appendColumnDefinition(9, "ВЕС", "Вес", true);
	priceSearch.exec();
	if (priceSearch.isFormSelected())
	{
		var priceId = priceSearch.getValue("КОД");
		var tovarId = getValue("КОД_ТОВАР");
		command = "UPDATE прайс SET КОД_ТОВАР = " + tovarId + " WHERE КОД = " + priceId + ";";
		db.exec(command);
	}
}


function ViewSales()
{
	evaluateScript("viewsales.js", getValue("КОД_ТОВАР"));
}


function ViewOst()
{
	var rowId = table.getId();
	if (currentRowId != rowId)
	{
		var id = table.getValue("ТОВАР__КОД");
		var articul = table.getValue("ТОВАР__ШИФР_ПО_КАТАЛОГУ").trim();
		if (articul.length > 0)
			ostDict.query("товар.ШИФР_ПО_КАТАЛОГУ = '" + articul + "' AND адрес.ИМЯ <> 'Брак'", true);
		else
			ostDict.query("товар.КОД = " + id + " AND адрес.ИМЯ <> 'Брак'", true);
		currentRowId = rowId;
	}
}


function PreparePictureUrl(object)
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
  // Функция должна вернуть url фотографии.
	url = "";
//	var nomId = getValue("КОД_ТОВАР");
	table.setPhotoPath(nomDict.getPhotoPath());	// Фотографии позиции заказа будем искать в каталоге фотографий справочника "Номенклатура" 
	table.setPhotoIdField("КОД_ТОВАР");
	url = table.getLocalPhotoFile();
	if (url.length == 0)
/*
	{
		table.setPhotoPath(nomDict.getPhotoPath());	// Фотографии позиции заказа будем искать в каталоге фотографий справочника "Номенклатура" 
		table.setPhotoIdField("КОД_ТОВАР");
		url = table.getLocalPhotoFile();
	}	
	else
*/
	{
		firmId = table.getValue("КОД_ФИРМЫ");
		if (firmId)
		{
			firmDict.setId(firmId);
			table.setPhotoPath(firmDict.getPhotoPath());	// Фотографии позиции заказа будем искать в каталоге фотографий справочника "Номенклатура" 
			pictureId = table.getValue("КОДВПРАЙСЕ");
			table.setPhotoIdField("КОДВПРАЙСЕ");
			evaluateScript("getPictureUrl.js");	// Запустим локальный скрипт
		}
	}
	return url;
}


function EventAfterRowChanged()
{ // Событие происходит после перемещения на другую строку
	var tovarId =  table.getValue(fieldIdTovar);
	var priceId =  table.getValue(fieldIdFirmTovar);
	if (tovarId > 0)
	{
/*
	 	if (priceId.length > 0)
		{
			firmId = table.getValue("КОД_ФИРМЫ");
			firmDict.setId(firmId);
			var fromFileName = app.getPhotosPath(firmDict.getValue("ФОТО_КАТАЛОГ")) + "/" + priceId + ".jpg";
			var toFileName = app.getPhotosPath(nomDict.getPhotoPath()) + "/" + tovarId + ".jpg";
			var localFileName = nomDict.getPhotoPath() + "/" + tovarId + ".jpg";
			CopyFile(fromFileName, toFileName, localFileName);
		}
*/
		ViewOst();
	}
}


function CopyFile(fromFileName, toFileName, localFileName)
{
	var fromFile = new QFile(fromFileName);
	var toFile = new QFile(toFileName);
	if (fromFile.exists() && !toFile.exists())
	{
		QFile.copy(fromFileName, toFileName);
		app.savePhotoToServer(toFileName, localFileName);
		table.getForm().showPhoto();
		app.showMessageOnStatusBar("Скопирована фотография из " + fromFileName);
	}
}


function EventCloseForm()
{
	salesGrdTable.close();
	priceSearch.close();
}


function RecalcAll()
{
	var progress = ProgressDialog("Пересчет заказа. Ожидайте...");
	progress.show();
	progress.setMaximum( getRowCount());
	for (var i = 0; i < getRowCount(); i++)
	{
		var id = getValue("КОД_ТОВАР", i);
		if (id > 0)
		{
			db.exec("SELECT sp_заказатьтовар(" + id + ");");
		}
		progress.setValue(i);
	}
	table.query();
	progress.hide();
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
	if (getCurrentFieldName() == "КОЛ")
	{
		var dictNom = getDictionary("товар");
		dictNom.setId(getValue("КОД_ТОВАР"));
		if (getValue("КОЛ") < 0)
		{
			dictNom.setValue("ЗАПАС", getValue("КОЛ"));
			scriptResult = false;
		}
		else
		{
			var id = getValue("ТОВАР__КОД");
			var остаток = db.getValue("SELECT КОНКОЛ FROM vw_saldo411_1 WHERE КОД_ТОВАР = " + id + " AND КОД_АДРЕС <> 512");
			if (остаток == undefined)
				остаток = 0;
			var новыйЗапас = getValue("КОЛ") + остаток;
			newQuan = getValue("КОЛ");
			dictNom.setValue("ЗАПАС", newQuan + остаток);
		}
	}
}


function EventAfterCalculate()
{
	setValue("КОЛ", newQuan);
}


function SwitchExtend()
{
	if (form.buttonExtend.text == "Сжатый")
	{
		form.buttonExtend.text("Расширенный");
		table.getGrdTable().hideGridSection("ЛЮДИ__ТЕЛЕФОН");
		table.getGrdTable().hideGridSection("ЛЮДИ__ИМЯ");
		table.getGrdTable().hideGridSection("ДАТАОБРАБОТКИ");
		table.getGrdTable().hideGridSection("МОДИФИЦИРОВАНО");
		table.getGrdTable().hideGridSection("ДАТАЗАЯВКИ");
		table.getGrdTable().hideGridSection("ПОСТОЯННО");
		table.getGrdTable().hideGridSection("ЗАКАЗАНО");
		table.getGrdTable().hideGridSection("ЦЕНА_ОБРАБОТАННАЯ");
		table.getGrdTable().hideGridSection("КОЛ_ОБРАБОТАННОЕ");
		table.getGrdTable().hideGridSection("НАЛИЧИЕ");
		table.getGrdTable().hideGridSection("ЕДИЗМВПРАЙСЕ");
		table.getGrdTable().hideGridSection("ИМЯВПРАЙСЕ");
		table.getGrdTable().hideGridSection("КОДВПРАЙСЕ");
		table.getGrdTable().hideGridSection("ФИРМЫ__ИМЯ");


	}
	else
	{
		form.buttonExtend.setText("Сжатый");
	}
}


function EventBeforeDeleteString()
{
	if (getValue("КОД_ДОКУМЕНТЫ129") > 0)
	{
		app.print("Запрещено удалять строку, т.к. заказ уже сформирован");
		return false;
	}
	return true;
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	if (filter.length > 0)
                    	filter = filter + " AND ";
	filter = filter + "КОД_ДОКУМЕНТЫ129 = 0";
	return filter;
}
