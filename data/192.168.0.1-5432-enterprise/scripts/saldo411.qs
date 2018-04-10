var form;
var currentFilter = "";

function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	if (!table.isDefaultForm())
	{
		 form.buttonCatalog.clicked.connect(ViewCatalog);
		 form.findChild("lineEditMinPrice").returnPressed.connect(cmdRequery);
		 form.findChild("lineEditMaxPrice").returnPressed.connect(cmdRequery);
		 form.findChild("lineEditOstatok").returnPressed.connect(cmdRequery);
	}
	table.setPhotoNameField("ТОВАР__ИМЯ");
	getDictionary("адрес").getForm().setLeftPercent(false);	// Адрес будем искать по первым символам (выражение ILIKE '<часть или полный адрес>%')
}


function cmdRequery()
{
	table.getForm().cmdRequery()
}



function ViewCatalog()
{
	var nom_Articul = table.getValue("ТОВАР__ШИФР_ПО_КАТАЛОГУ").trim();
	if (nom_Articul.length > 0)
	{
		var command = "firefox http://acat.autodealer.ru/index.php?search=" + nom_Articul + "&ex=3&where=on";
		app.runProcess(command, "Mozilla FireFox");
		form.getFormWidget().setGridFocus();
	}
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	var fil = table.getSearchExpression("товар");
	fil = fil.replace(/^\s+/,'').replace(/\s+$/,'');
	if (fil.length > 0)
	{
		if (currentFilter.length > 0 && fil != currentFilter && fil.indexOf(currentFilter) == -1)
		{
			logSearchExpr(currentFilter);
		}
		currentFilter = fil;
	}
	filter = filter.replace(/\"товар\".\"ИМЯ\"/g, "(товар.ИМЯ || товар.ШИФР_ПО_КАТАЛОГУ || товар.АРТИКУЛ)");
	var minPrice = parseFloat(form.findChild("lineEditMinPrice").text);
	var maxPrice = parseFloat(form.findChild("lineEditMaxPrice").text);
	var ostatok = form.findChild("lineEditOstatok").text.trim();
	if (minPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "товар.ЦЕНА >= " + minPrice;
	}
	if (maxPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "товар.ЦЕНА <= " + maxPrice;
	}
	if (ostatok.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		if (!isNaN(parseInt(ostatok, 10)))
			filter = filter + "сальдо.КОНКОЛ = " + ostatok;
		else
			filter = filter + "сальдо.КОНКОЛ " + ostatok;
	}
	return filter;
}


function EventAfterHideForm(form)
{  // Перед закрытием формы
	if (!form.isFormSelected())
		logSearchExpr(currentFilter);
	currentFilter = "";
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
	if (table.getFormWidget().findChild("tableView").focus)
	{
		var currentBarCode = table.getValue("ШТРИХКОД");
		if (currentBarCode.length  > 0)
		{
			var addMsg = new QMessageBox(QMessageBox.Question, "Внимание!", "Изменить штрихкод?");
			addMsg.addButton(QMessageBox.Yes);
			addMsg.addButton(QMessageBox.No);
			addMsg.setDefaultButton(QMessageBox.No);
             		 	if (addMsg.exec() == QMessageBox.No)
				return;
		}
		table.setValue("ШТРИХКОД", barCode);
	}
	else
	{
		form.findChild("lineEditBarCode").setText(barCode);
		cmdRequery();
		cmdOk();
	}
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
}


function PrepareBarCodeData()
{ // Вызов этой функции происходит перед печатью штрих-кода. Функция должна вернуть значение штрих-кода.
	table.appendPrintValue("ТОВАР_КОД", table.getValue("ТОВАР__КОД"));
	table.appendPrintValue("ТОВАР_ИМЯ", table.getValue("ТОВАР__ИМЯ"));
	table.appendPrintValue("ТОВАР_ЦЕНА", table.getValue("ТОВАР__ЦЕНА"));
	return "00000" + table.getValue("ТОВАР__КОД");
}


function EventKeyPressed(key, modifiers)
{  // Событие происходит при нажатии кнопки на форме. Должно вернуть ИСТИНА, если нажатие обработано
	if (key == Qt.Key_F5 && modifiers == 0)
	{
		labelQuan = table.getValue("САЛЬДО__КОНКОЛ");
		if (labelQuan > 0)
		{
			evaluateScript("печать_этикеток.js");
			return true;
		}
	}
	return false;
}


function logSearchExpr(expr)
{
	if (document != 0 && expr.length > 0 && (document.getOperNumber() == 1 || document.getOperNumber() == 11))
	{
		db.exec("SELECT sp_поисктовара('" + expr + "', " + document.getDocId() + ");");
	}
}





