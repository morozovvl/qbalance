var saldo;		// справочник сальдо
var addr;		// справочник адресов
var lastAddr;	// справочник хранения последних адресов

var tovarPhotoPath 		= db.getDictionaryPhotoPath("товар");
var fieldDocumentTovarId		= "ДБНАБОР1__ТОВАР__КОД"; 
var fieldDocumentTovarName	= "ДБНАБОР1__ТОВАР__ИМЯ"; 



function EventInitForm()
{ // Событие происходит сразу после создания формы документа
	saldo = document.getSaldo("411");
	lastAddr = document.getDictionary("посладрес");
	addr = document.getDictionary("адрес");

	// Установим пути к фотографиям
	document.setPhotoPath(tovarPhotoPath);		
	document.setPhotoIdField(fieldDocumentTovarId);
	table.setPhotoNameField(fieldDocumentTovarName);
}


function EventBeforeAddString()
{ //Событие происходит перед добавлением строки в документ
	var result = false;
	saldo.exec();
	if (saldo.isFormSelected())
	{
		saldo.lock();
		var tovarId = saldo.getValue("КОД_ТОВАР");
		lastAddr.query("КОД_ТОВАР=" + tovarId);
		if (lastAddr.getRowCount() > 0)
		{
			var addrId = lastAddr.getValue("КОД_АДРЕС");
			addr.setFormTitle("Последний (рекомендуемый) адрес хранения");
			addr.getForm().clearAllComboBoxes();
		}
		else
		{
			addr.setFormTitle("Введите адрес хранения");
		}
		addr.setId(addrId);
		addr.exec();
		if (addr.isFormSelected())
		{
			addr.lock();
			result = true;
		}
	}
	return result;
}


function setLastAddr()
{ // сохранить последний адрес хранения
	var addrName = addr.getName();
	var firstChar = addrName.substring(0, 1);
	if ( firstChar == "1" || firstChar == "2" || firstChar == "3")	// Если адрес начинается с 1, 2 или 3
	{
		var tovarId = getValue("ДБНАБОР1__ТОВАР__КОД");
		lastAddr.query("КОД_ТОВАР=" + tovarId);
		if (lastAddr.getRowCount() > 0)
			lastAddr.setValue("КОД_АДРЕС", addr.getId());
		else
			lastAddr.getId();
	}
}


function EventAfterAddString()
{ //Событие происходит после добавления строки в документ
	setValue("P2__КРКОД", getValue("P1__КРКОД"));
}


function EventCalcTable()
{
	// Считаем значения в табличной части
	if (getCurrentFieldName() == "P1__КОЛ")		// Только при изменении количества 
	{
		var nQuan1 = getOldValue();
		var nTotQuan1 = getValue("КР411__КОНКОЛ") + nQuan1;
		var nTotSaldo1 = getValue("КР411__КОНСАЛЬДО") + getValue("P1__СУММА");
		var nTotSaldo2 = getValue("КР421__КОНСАЛЬДО") + getValue("P2__СУММА")
		var nPrice1 = getValue("КРНАБОР1__ТОВАР__ЦЕНА");
		if (nTotQuan1 != 0)
		{
	       		if (nQuan1 == 0 || nPrice1 == getValue("P1__ЦЕНА"))       // Перемещение еще не введено или введено, но цена эта же
			{
				nQuan1 = getValue("P1__КОЛ");
				nPrice1 = nTotSaldo1 / nTotQuan1;
				setValue("P1__ЦЕНА", nPrice1);
				setValue("P1__СУММА", nPrice1 * nQuan1);
				setValue("P2__СУММА", nQuan1 * nTotSaldo2 / nTotQuan1);
				if (nQuan1 > nTotQuan1)
					errorMessage = "Остаток ОТРИЦАТЕЛЬНЫЙ.";
				if (nQuan1 > 0)		// Если что-то переместили
					setLastAddr();	// сохраним последний адрес хранения
			}
			else
			{
		       	  	errorMessage = "Запрещено изменять строку, т.к. цена товара после создания этой строки была изменена. Изменение может привести к неверному вычислению сальдо.";
				scriptResult = false;
			}
		}
	}
}
