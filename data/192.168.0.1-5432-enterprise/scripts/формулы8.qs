function EventInitForm(form)
{ // Событие происходит сразу после создания формы документа
// Здесь Вы можете вставить свой код
	getDictionary("набор1").setGetIdRefresh(false);		// Не будем обновлять связанные справочники набора во время получения ID набора, чтобы не было сообщений, что не определен связанный справочник
}


function EventAfterAddString()
{ // Событие происходит после добавления строки в документ
	var command = "SELECT * FROM vw_saldo411 WHERE КОД_ТОВАР = " + getValue("ТОВАР__КОД");
	var query = db.execQuery(command);
	while (query.next())
	{
		var setId = query.record().value("КОД");
		var quan = query.record().value("КОНКОЛ");
		var saldo = query.record().value("КОНСАЛЬДО");
		var price = saldo / quan;
		if (getValue("P1__ДБКОД") == setId)
		{
			setValue("P1__КОЛ", quan);
			setValue("P1__ЦЕНА", price);
			setValue("P1__СУММА", saldo);
    			setValue("P2__КОЛ", quan);
	    		setValue("P2__ЦЕНА", price);
			setValue("P2__СУММА", saldo);
		}
		else
		{
			document.prepareValue("P1__ДБКОД", setId);
    			document.prepareValue("P1__КРКОД", setId);
    			document.prepareValue("P1__КОЛ", quan);
	    		document.prepareValue("P1__ЦЕНА", price);
	    		document.prepareValue("P1__СУММА", saldo);
    			document.prepareValue("P2__ДБКОД", setId);
	    		document.prepareValue("P2__КРКОД", setId);
    			document.prepareValue("P2__КОЛ", quan);
	    		document.prepareValue("P2__ЦЕНА", price);
			document.prepareValue("P2__СУММА", saldo);
			document.appendDocString();
		}
	}
	return true;
}


function EventAppendFromQuery(id, record)
{ // Вызывается при добавлении новой записи из запроса
// Здесь Вы можете вставить свой код
	if (id == "vw_новыецены3" || id == "vw_новыецены_на_остатки"  || id == "vw_новыецены_на_остатки1")
	{
		var dictNom = getDictionary("товар");
		dictNom.setId(record.КОД_ТОВАР);
		dictNom.setValue("ЦЕНА", record.НОВЦЕНА);
		if (record.КОД_АДРЕС != 0)
		{
			var dictAddr = getDictionary("адрес");
			dictAddr.setId(record.КОД_АДРЕС);
		}
		if (record.КОД > 0 && record.ЗАКЦЕНА != 0)
		{
			// Запишем кол-во, цену, сумму в проводку
	    		document.prepareValue("P1__ДБКОД", record.КОД);
    			document.prepareValue("P1__КРКОД", record.КОД);
    			document.prepareValue("P1__КОЛ", record.КОЛ);
	    		document.prepareValue("P1__ЦЕНА", record.ЦЕНА);
    			document.prepareValue("P1__СУММА", record.КОЛ*record.ЦЕНА);
    			document.prepareValue("P2__ДБКОД", record.КОД);
	    		document.prepareValue("P2__КРКОД", record.КОД);
    			document.prepareValue("P2__КОЛ", record.КОЛ);
    			document.prepareValue("P2__ЦЕНА", record.НОВЦЕНА);
	    		document.prepareValue("P2__СУММА", record.КОЛ*record.НОВЦЕНА);
			document.prepareValue("ЗАКЦЕНА", record.ЗАКЦЕНА);
			document.prepareValue("ПРОЦЕНТ", 100*(record.ЦЕНА - record.ЗАКЦЕНА) / record.ЗАКЦЕНА);
			document.prepareValue("НОВПРОЦЕНТ", 100*(record.НОВЦЕНА - record.ЗАКЦЕНА) / record.ЗАКЦЕНА);
			 // Сохраним проводку на сервере
			document.appendDocString();
		}
	}
}


function EventCalcTable()
{ // Событие происходит после изменения ячейки в таблице
// Здесь Вы можете вставить свой код
	getDictionary("товар").setDoSubmit(false);		// Не сохранять изменение в справочнике раньше срока, а обновлять вместе с сохранением изменений документа (чтобы 								все изменения были одной транзакцией)
	var proc = 0;
	var price = 0;
	if (getCurrentFieldName() == "НОВПРОЦЕНТ")		 
	{
		proc = getValue("НОВПРОЦЕНТ");
		price = getValue("ЗАКЦЕНА") * (1 + proc / 100);
	}
	if (getCurrentFieldName() == "P2__ЦЕНА")
	{
		price = getValue("P2__ЦЕНА");
		if (getValue("ЗАКЦЕНА") > 0)
			proc = (price - getValue("ЗАКЦЕНА")) *  100 / getValue("ЗАКЦЕНА");
	}
	if (price != 0)
	{
		var rowCount = document.getRowCount();
		var tovarId = getValue("ТОВАР__КОД");
		for (var i = 0; i < rowCount; i++)
		{
			if (getValue("ТОВАР__КОД", i) == tovarId)
			{
				if (getValue("P2__КОЛ", i) == getValue("КР411__КОНКОЛ", i))
				{
					setValue("НОВПРОЦЕНТ", proc, i);
					setValue("P2__ЦЕНА", price, i);
					setValue("P2__СУММА", getValue("P2__КОЛ", i) * price, i);
				}
				else
				{
					errorMessage = "Остатки товара уже поменялись. Изменение цены в проводке может привести к неверному вычислению сальдо. Для переоценки товара создайте новый документ.";
					scriptResult = false;
					return;
				}
			}
		}
		getDictionary("товар").setValue(tovarId, "ЦЕНА", price);
	}
}


