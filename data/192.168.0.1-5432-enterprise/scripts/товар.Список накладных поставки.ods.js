if (table.getRowCount() > 0)
{
  var id = table.getId();
  var command = "SELECT d.*, p.КОДВПРАЙСЕ, p.ИМЯ \
		 FROM (SELECT d.*, a.КОД_ПРАЙС \
			FROM (SELECT ДАТА, НОМЕР, КОММЕНТАРИЙ, d.СУММА AS ДОКСУММА, КОЛ, ЦЕНА, p.СУММА, ДОККОД, СТР \
			      FROM (SELECT d.*, s.КОД AS КОД_НАБОР402 \
				    FROM набор402 s INNER JOIN документы d ON s.КОД_ДОКУМЕНТЫ123 = d.КОД \
				    WHERE КОД_ТОВАР = " + id + ") d INNER JOIN проводки p ON d.КОД = p.ДОККОД AND d.КОД_НАБОР402 = p.ДБКОД \
				    ) d INNER JOIN атрибуты123 a ON d.ДОККОД = a.ДОККОД AND d.СТР = a.СТР \
			      ) d INNER JOIN прайс p ON d.КОД_ПРАЙС = p.КОД \
		 ORDER BY ДАТА DESC";
  var query = db.execQuery(command);
  table.appendPrintValues("накладные", query);
}
