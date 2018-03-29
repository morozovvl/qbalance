function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	var bankDict = getDictionary("банки");
	bankDict.setId(app.getConst("КодГлБанка"));
	form.getButtonSave().show();		// Включим кнопку "Выгрузить документ" на форме
	form.addQueryMenuAction("__все__заказы__", "Все заказы");
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
// Здесь Вы можете вставить свой код
	var цена = getValue("ПРАЙС__МИНЦЕНА");
	setValue("P1__ЦЕНА", цена);
	return true;
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
	if (id == "__все__заказы__")
	{
		var dictFirm = getDictionary("фирмы");
		if (dictFirm.getId() > 0)
		{
			var zakazDict = getDictionary("vw_заявка");
			zakazDict.query("КОД_ФИРМЫ = " + dictFirm.getId());
			zakazDict.exec();
			if (zakazDict.isFormSelected())
			{
				var progress = ProgressDialog("Заполнение заказа. Ожидайте...");
				progress.show();
				progress.setMaximum(zakazDict.rowCount());
				for (var i = 0; i < zakazDict.rowCount(); i++)
				{
					var quan = zakazDict.getValue("КОЛ", i);
					if (quan > 0)
					{
						var price = zakazDict.getValue("ЦЕНА", i);
						var sum = quan * price;
	    					document.prepareValue("P1__ДБКОД", zakazDict.getValue("КОД", i));
						document.prepareValue("P1__КРКОД", dictFirm.getId());
						document.prepareValue("P1__КОЛ", quan);
    						document.prepareValue("P1__ЦЕНА", price);
						document.prepareValue("P1__СУММА", sum);
						document.prepareValue("КОДЗАКАЗ", zakazDict.getValue("КОДЗАКАЗ", i));
						document.prepareValue("КОДДОКЗАКАЗ", zakazDict.getValue("КОДДОКЗАКАЗ", i));
						document.prepareValue("СТРДОКЗАКАЗ", zakazDict.getValue("СТРДОКЗАКАЗ", i));
				 		// Сохраним проводку на сервере
						document.appendDocString();
						db.exec("UPDATE заявка SET КОД_ДОКУМЕНТЫ129 = " + documents.getId() + " WHERE КОД = " + zakazDict.getValue("КОДЗАКАЗ", i) + ";");
						progress.setValue(i);
					}
				}
				progress.hide();
				documents.setValue("Комментарий", dictFirm.getName());
			}
		}
/*
		var command = "SELECT * FROM vw_заявка WHERE КОД_ФИРМЫ = " + dictFirm.getId();
		var zakazQuery = db.execQuery(command);
		if (zakazQuery.first())
		{
			var progress = ProgressDialog("Заполнение заказа. Ожидайте...");
			progress.show();
			progress.setMaximum(zakazQuery.size());
			do
			{
				var zakazRecord = zakazQuery.record();
				var quan = zakazRecord.value("КОЛ");
				if (quan > 0)
				{
					var price = zakazRecord.value("ЦЕНА");
					var sum = quan * price;
	    				document.prepareValue("P1__ДБКОД", zakazRecord.value("КОД_ПРАЙС"));
					document.prepareValue("P1__КРКОД", dictFirm.getId());
					document.prepareValue("P1__КОЛ", quan);
    					document.prepareValue("P1__ЦЕНА", price);
					document.prepareValue("P1__СУММА", sum);
					document.prepareValue("КОДЗАКАЗ", zakazRecord.value("КОДЗАКАЗ"));
					document.prepareValue("КОДДОКЗАКАЗ", zakazRecord.value("КОДДОКЗАКАЗ"));
					document.prepareValue("СТРДОКЗАКАЗ", zakazRecord.value("СТРДОКЗАКАЗ"));
			 		// Сохраним проводку на сервере
					document.appendDocString();
					db.exec("UPDATE заявка SET КОД_ДОКУМЕНТЫ129 = " + documents.getId() + " WHERE КОД = " + zakazRecord.value("КОДЗАКАЗ") + ";");
					progress.setValue(zakazQuery.at());
				}
			} while (zakazQuery.next());
			progress.hide();
			documents.setValue("Комментарий", dictFirm.getName());
		}
*/
	}
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
	var кол = getValue("P1__КОЛ");
	var цена = getValue("P1__ЦЕНА");
	var сумма = getValue("P1__СУММА");

	if (getCurrentFieldName() == "P1__СУММА" && кол != 0) 
	{
		цена = сумма / кол;
	}
	else 
	{
		сумма = кол * цена;
	}

	setValue("P1__КОЛ", кол);
	setValue("P1__ЦЕНА", цена);
	setValue("P1__СУММА", сумма);

	if (getCurrentFieldName() == "ЦЕНА_РЕАЛИЗАЦИИ" && цена != 0) 
	{
		var процент = (getValue("ЦЕНА_РЕАЛИЗАЦИИ") - цена) * 100 / цена;
		setValue("ПРОЦЕНТ", процент);
	}

	if (getCurrentFieldName() == "ПРОЦЕНТ") 
	{
		var цена_реализации = цена * (1 + getValue("ПРОЦЕНТ") / 100);
		setValue("ЦЕНА_РЕАЛИЗАЦИИ", цена_реализации);
	}
}


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
	if (documents.getValue("ЗАКРЫТ"))
		document.setEnabled(false);
}


function EventBeforeDeleteDocument()
{ // Событие происходит перед удалением документа
// Здесь Вы можете вставить свой код
	db.exec("UPDATE заявка SET КОД_ДОКУМЕНТЫ129 = 0 WHERE КОД_ДОКУМЕНТЫ129 = " + documents.getId() + ";");	
	return true;
}


function EventBeforeDeleteString()
{ // Событие происходит перед удалением строки из документа
// Здесь Вы можете вставить свой код
	db.exec("UPDATE заявка SET КОД_ДОКУМЕНТЫ129 = 0 WHERE КОД = " + getValue("КОДЗАКАЗ") + ";");	
	return true;
}


function EventExport()
{ // Событие происходит при нажатии кнопки <Экспорт>
// Здесь Вы можете вставить свой код
    app.setDirName("ZakazDir");
    var fileName = app.getOpenFileName(form, "Откройте файл для экспорта заказа в формате Паскер", "", "Документ Text(*.txt)");
    if (fileName != "")
    {    
	var file = new QFile(fileName);
    	if (file.open(QIODevice.OpenMode(QIODevice.WriteOnly, QIODevice.Text))) 
    	{
		QTextCodec.setCodecForLocale(QTextCodec.codecForName(new QByteArray().append("Windows-1251")));
		data = QTextCodec.codecForLocale().fromUnicode("Заказ ДАТА: [" + (new Date().toLocaleDateString()) + "], КЛИЕНТ: [], АДРЕС: [], ТЕЛЕФОНЫ: []\r\n");
		file.write(data);
		for (var i = 0; i < table.getRowCount(); i++)
  		{
			data = QTextCodec.codecForLocale().fromUnicode(getValue("ПРАЙС__КОДВПРАЙСЕ", i) + " " + getValue("ПРАЙС__ИМЯ", i) + "\r\n" + getValue("P1__КОЛ", i) + "\r\n");
			print(getValue("ПРАЙС__ИМЯ", i));
			file.write(data);
		}
		file.close();
		QTextCodec.setCodecForLocale(app.codec());
	}
    }
}


function EventPreparePrintValues()
{ // Событие происходит перед созданием документа печати и предназначено для создания новых данных для документа
   // Здесь Вы можете вставить свой код
  var сумма = 0;
  var итого = 0;
  for (var i = 1; i <= table.getRowCount(); i++)
  {
     сумма = getValue("P1__КОЛ", i - 1) * getValue("ЦЕНА_РЕАЛИЗАЦИИ", i - 1);
     table.appendPrintValue("таблица" + i + ".СУММА_РЕАЛИЗАЦИИ", сумма);
     итого = итого + сумма;
  }
  table.appendPrintValue("ИТОГО_РЕАЛИЗАЦИЯ", итого);
}

