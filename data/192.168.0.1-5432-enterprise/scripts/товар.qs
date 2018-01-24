var form;
var sales =		new Dictionary();
var defUnit = "";
var defGrId = 0;



function EventInitForm()
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	form = table.getFormWidget();
	if (form != null && !table.isDefaultForm())
	{
		 form.buttonCatalog.clicked.connect(ViewCatalog);
		 form.findChild("lineEditMinPrice").returnPressed.connect(cmdRequery);
		 form.findChild("lineEditMaxPrice").returnPressed.connect(cmdRequery);
		 form.findChild("lineEditBarCode").returnPressed.connect(cmdRequery);
		 form.buttonCalc.clicked.connect(RecalcAll);
		 form.buttonViewSales.clicked.connect(ViewSales);
		 form.buttonViewGroupSales.clicked.connect(ViewGroupSales);
		 form.buttonQuery.show();		// Включим кнопку "Загрузить документ" на форме
	}
}


function cmdRequery()
{
	table.getForm().cmdRequery()
}


function ViewCatalog()
{
	var nom_Articul = table.getValue("ШИФР_ПО_КАТАЛОГУ").trim();
	if (nom_Articul.length > 0)
	{
		var command = "firefox http://www.autoopt.ru/search/catalog/?q=" + nom_Articul + "&set_filter=y";
		app.runProcess(command, "Mozilla FireFox");
	}
}


function GetFilter(filter)
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
	filter = filter.replace(/\"товар\".\"ИМЯ\"/g, "(товар.ИМЯ || ' ' || товар.ШИФР_ПО_КАТАЛОГУ || ' ' || товар.АРТИКУЛ)");
	var minPrice = parseFloat(form.findChild("lineEditMinPrice").text);
	var maxPrice = parseFloat(form.findChild("lineEditMaxPrice").text);
	var barCode = form.findChild("lineEditBarCode").text.trim();
	if (minPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "ЦЕНА >= " + minPrice;
	}
	if (maxPrice > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "ЦЕНА <= " + maxPrice;
	}
	if (barCode.length > 0)
	{
		if (filter.length > 0)
			filter = filter + " AND ";
		filter = filter + "ШТРИХКОД LIKE '%" + barCode + "%'";
	}
	return filter;
}


function EventBeforeHideForm(form)
{  // Перед закрытием формы
	form.getFormWidget().findChild("lineEditBarCode").setText("");
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
	}
}


function RecalcAll()
{
	var progress = new ProgressDialog("Пересчет заказа. Ожидайте...");
	progress.show();
	progress.setMaximum( getRowCount());
	for (var i = 0; i < getRowCount(); i++)
	{
		db.exec("SELECT sp_заказатьтовар(" + getId(i) + ");");
		progress.setValue(i);
	}
	table.query();
	progress.hide();
}


function ViewSales()
{
  evaluateScript("viewsales.js", getId());
}


function ViewGroupSales()
{
  evaluateScript("viewgroupsales.js", getValue("ШИФР_ПО_КАТАЛОГУ"));
}


function EventBeforeAddString()
{
	defUnit = table.getValue("ЕДИЗМ");
	defGrId = table.getValue("КОД_ГРУППЫ");
}


function EventAfterAddString()
{
	table.setValue("ЕДИЗМ", defUnit);
	table.setValue("КОД_ГРУППЫ", defGrId);
}


function PrepareBarCodeData()
{ // Вызов этой функции происходит перед печатью штрих-кода. Функция должна вернуть значение штрих-кода.
	return "00000" + getId();
}


function EventCalcTable()
{
	scriptResult = true;
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "ЦЕНА" && db.getValue("SELECT COALESCE(SUM(КОНКОЛ), 0) AS КОЛ FROM сальдо WHERE СЧЕТ = '411' AND КОД IN (SELECT КОД FROM набор1 WHERE КОД_ТОВАР = " + getId() + ")") != 0)
	{
		errorMessage = "Нельзя изменять розничную цену напрямую, т.к. имеются остатки. Необходимо выполнить переоценку.";
		table.restoreOldValues();
		scriptResult = false;
	}
	if (getCurrentFieldName() == "ЗАПАС")
	{
		var quan = getValue("ЗАПАС");
		if (quan < 0)
			quan = 0;
		setValue("АВТЗАПАС", quan);
	}
}


function EventQuery()
{
	print("EnevtQuery Ok");
}
