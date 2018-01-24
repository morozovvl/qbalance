function EventAfterDeleteString()
{ // Событие происходит после удаления строки из документа
// Здесь Вы можете вставить свой код
	return true;
}


function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	var bankDict = getDictionary("банки");
	bankDict.setId(app.getConst("КодГлБанка"));
	form.getButtonSave().show();		// Включим кнопку "Выгрузить документ" на форме
	form.addQueryMenuAction("__все__заказы__", "Все заказы");
}


function EventBeforeHideForm(form)
{ // Событие происходит перед закрытием формы документа
// Здесь Вы можете вставить свой код
}


function EventBeforeLinePrint(strNum)
{ // Вызывается до печати очередной строки в документе
// Здесь Вы можете вставить свой код
}


function EventAfterRowChanged()
{ // Событие происходит после перемещения на другую строку
// Здесь Вы можете вставить свой код
return "";
}


function EventCardCodeReaded(cardCode)
{ // Событие происходит после прочтения магнитной карты
// Здесь Вы можете вставить свой код
return "";
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
// Здесь Вы можете вставить свой код
	var цена = getValue("ПРАЙС__МИНЦЕНА");
	setValue("P1__ЦЕНА", цена);
	return true;
}


function EventAfterShowForm(form)
{ // Событие происходит после открытия формы документа
// Здесь Вы можете вставить свой код
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
	if (id == "__все__заказы__")
	{
		var dictFirm = getDictionary("фирмы");
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


function EventParametersChanged()
{ // Событие происходит в момент изменения постоянного справочника документа
// Здесь Вы можете вставить свой код
}


function EventSetEnabled(enabled)
{ // Событие предназначено для изменения возможности доступа к элементам пользовательской формы
// Здесь Вы можете вставить свой код
return "";
}


function EventBarCodeReaded(barCode)
{ // Событие происходит после прочтения штрих-кода
// Здесь Вы можете вставить свой код
return "";
}


function GetFilter()
{ // Вызов этой функции происходит перед запросом к БД. Функция должна вернуть дополнительный фильтр к запросу.
// Здесь Вы можете вставить свой код
return "";
}


function EventBeforeShowForm(form)
{ // Событие происходит перед открытием формы документа
	if (documents.getValue("ЗАКРЫТ"))
		document.setEnabled(false);
}


function EventBeforeAddString()
{ // Событие происходит перед добавлением строки в документ
// Здесь Вы можете вставить свой код
return true;
}


function EventAfterLinePrint(strNum)
{ // Вызывается после печати очередной строки в документе
// Здесь Вы можете вставить свой код
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


function EventAfterCalculate()
{ // Событие происходит после вычисления в ячейке
// Здесь Вы можете вставить свой код
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
/*
		var str = "Заказ ДАТА: [" + (new Date().toLocaleDateString()) + "], КЛИЕНТ: [], АДРЕС: [], ТЕЛЕФОНЫ: []";
		print(str);
//		QTextCodec.setCodecForLocale(QTextCodec.codecForName(new QByteArray().append("Windows-1251")));
//		var data = QTextCodec.codecForLocale().fromUnicode(str);
		var codec = QTextCodec.codecForName(new QByteArray().append("Windows-1251"));
//		var data = codec.fromUnicode(str);
//		file.write(data);

		data = QTextCodec.codecForLocale().fromUnicode("\r\n");
		file.write(data);
		for (var i = 0; i < table.getRowCount(); i++)
  		{
			data = QTextCodec.codecForLocale().fromUnicode(getValue("ПРАЙС__КОДВПРАЙСЕ", i) + " " + getValue("ПРАЙС__ИМЯ", i) + "\r\n" + getValue("P1__КОЛ", i) + "\r\n");
			file.write(data);
		}
*/
		var data = "Заказ ДАТА: [" + (new Date().toLocaleDateString()) + "], КЛИЕНТ: [], АДРЕС: [], ТЕЛЕФОНЫ: []";
		print(data);
//		file.write(data);
		for (var i = 0; i < table.getRowCount(); i++)
  		{
//			data = QTextCodec.codecForLocale().fromUnicode(getValue("ПРАЙС__КОДВПРАЙСЕ", i) + " " + getValue("ПРАЙС__ИМЯ", i) + "\r\n" + getValue("P1__КОЛ", i) + "\r\n");
			data = getValue("ПРАЙС__КОДВПРАЙСЕ", i) + " " + getValue("ПРАЙС__ИМЯ", i) + "\r\n" + getValue("P1__КОЛ", i);			
//			file.write(data);
			print(data);
		}
		file.close();
//		QTextCodec.setCodecForLocale(app.codec());
	}
    }
}


function EventAfterShowNextDicts()
{ // Событие происходит после показа всех необходимых справочников при добавлении строки в документ
// Здесь Вы можете вставить свой код
return true;
}


function EventCloseForm(form)
{ // Событие происходит перед удалением формы документа
// Здесь Вы можете вставить свой код
}


function EventPhotoLoaded()
{ // Событие происходит после загрузки фотографии из Интернета
// Здесь Вы можете вставить свой код
return "";
}


function EventAfterHideForm(form)
{ // Событие происходит после закрытия формы документа
// Здесь Вы можете вставить свой код
}


function EventKeyPressed(keyEvent)
{ // Событие происходит при нажатии любой кнопки на форме. Параметр keyEvent имеет тип QKeyEvent
// Здесь Вы можете вставить свой код
}


function PreparePictureUrl(object)
{ // Вызов этой функции происходит перед открытием фотографии. Здесь имеется возможность загрузить фотографию для текущего объекта object из Интернета. Функция должна вернуть url фотографии.
// Здесь Вы можете вставить свой код
}


function EventImport()
{ // Событие происходит при нажатии кнопки <Импорт>
// Здесь Вы можете вставить свой код
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

