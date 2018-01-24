var modelNumber = 2;		// Номер математической модели прогноза

var forwardMonths = 1;		// Общий прогноз будет делаться на столько-то месяцев вперед
var lastYearsQuan = 3;		// Анализ будет проводиться за последние 3 года
var articulMap = {};
var currentDate = new Date();
var lastYear = new Date();
var progress;
var currentYear;
var currentMonth;
var lastMonth;
var nomIdMap = {};		// Позиции, проданные за последний год
var nomNameMap = {};
var nomZapasMap = {};
var bestNomIdMap = {};
var totalLastYearSold;
var bestTotalSold = 0;
var salesType = 0;		// Тип продаж
var progressCounter = 0;


//---------------------------------------------------------------------------------------------
var nomDict = app.getDictionary("товар");
nomDict.exec();
if (nomDict.isFormSelected())
{
//  currentDate.setDate(currentDate.getDate()-30);
  lastYear.setDate(currentDate.getDate() - 365);
  currentYear = currentDate.getFullYear();

  var pastDateTo = new Date(currentDate);
  currentDate.setDate(currentDate.getDate() - lastYearsQuan * 365);
  var pastDateFrom = new Date(currentDate);

  currentDate.setDate(currentDate.getDate() + 15);
  lastMonth = currentDate.getMonth();
  currentMonth = lastMonth + 1;
  if (currentMonth > 12)
  {
    currentMonth = 1;
    currentYear = currentYear + 1;
  }
  
  app.print();
  app.print();
  app.print("Месяц для заказа: " + currentMonth + ". Запас вперед на, месяцев: " + forwardMonths);
  app.print("Период с " + pastDateFrom.toLocaleDateString() + " по " + pastDateTo.toLocaleDateString());
  
  progress = ProgressDialog("Пересчет по аналогам. Ожидайте...");
  progress.show();

  for (var i = 0; i < nomDict.rowCount(); i++)
  {
    articul = nomDict.getValue("ШИФР_ПО_КАТАЛОГУ", i).trim();
    if (nomDict.getValue("ЗАПАС", i) >= 0)
    {
      if (articul.length > 0)
      {
	if (articul in articulMap)
	  articulMap[articul] = articulMap[articul] + 1;
	else
	{
	  articulMap[articul] = 1;
	  progressCounter++;
	}
      }
      else
	progressCounter++;
    }
  }
  nomId = 0;
  progress.setMaximum(progressCounter);
  progressCounter = 0;
  
  AnalyseGroups();
  
  if (!progress.isEscapeKeyPressed())
  {
    progress.setTitle("Пересчет по одиночным позициям. Ожидайте...");
    articulMap = [];
    for (var i = 0; i < nomDict.rowCount(); i++)
    {
      articul = nomDict.getValue("ШИФР_ПО_КАТАЛОГУ", i).trim();
      if (articul.length == 0 && nomDict.getValue("ЗАПАС", i) >= 0)
      {
	nomId = nomDict.getValue("КОД", i);
	AnalyseSingle(nomId, nomDict.getValue("ИМЯ", i));
	progress.setValue(progressCounter++);
	if (progress.isEscapeKeyPressed())
	  break;
      }
    }
  }
  progress.hide();
}


function AnalyseGroups()
{
  for(key in articulMap) 
  {
    if (articulMap[key] >= 1)
    {
      app.print();
      app.print("=======================Группа: " + key);
      
      var command = "SELECT s.ДАТА, s.КОД, t.ИМЯ, t.ЦЕНА, t.ЗАПАС, s.ОПЕРНОМЕР, SUM(s.ДБКОЛ) AS ДБКОЛ, SUM(s.КРКОЛ) AS КРКОЛ, 0 AS ОСТАТОК \
		    FROM (SELECT s.ДАТА, s.КОД, CASE WHEN s.ОПЕРНОМЕР = 71 THEN 1 ELSE s.ОПЕРНОМЕР END AS ОПЕРНОМЕР, \
		    CASE WHEN s.ОПЕРНОМЕР = 71 THEN 0::NUMERIC(10, 3) ELSE s.ДБКОЛ END AS ДБКОЛ, \
		    CASE WHEN s.ОПЕРНОМЕР = 71 THEN -s.ДБКОЛ ELSE s.КРКОЛ END AS КРКОЛ \
		    FROM sp_calcgrouptovaroborot('" + key + "', '01.01.2010', '" + pastDateTo.toLocaleDateString() + "') s) s \
			  INNER JOIN товар t ON s.КОД = t.КОД \
		    GROUP BY s.ДАТА, s.КОД, t.ИМЯ, t.ЦЕНА, t.ЗАПАС, s.ОПЕРНОМЕР \
		    ORDER BY s.ДАТА";
      AnalyseSales(command, 0, key);
    }
    progress.setValue(progressCounter++);
    if (progress.isEscapeKeyPressed())
      break;
  }
}


function AnalyseSingle(id, name)
{
      app.print();
      app.print("=======================Позиция: " + name);
      
      var command = "SELECT s.ДАТА, t.КОД, t.ИМЯ, t.ЦЕНА, t.ЗАПАС, s.ОПЕРНОМЕР, SUM(s.ДБКОЛ) AS ДБКОЛ, SUM(s.КРКОЛ) AS КРКОЛ, 0 AS ОСТАТОК \
		    FROM (SELECT s.ДАТА, CASE WHEN s.ОПЕРНОМЕР = 71 THEN 1 ELSE s.ОПЕРНОМЕР END AS ОПЕРНОМЕР, \
		    CASE WHEN s.ОПЕРНОМЕР = 71 THEN 0::NUMERIC(10, 3) ELSE s.ДБКОЛ END AS ДБКОЛ, \
		    CASE WHEN s.ОПЕРНОМЕР = 71 THEN -s.ДБКОЛ ELSE s.КРКОЛ END AS КРКОЛ \
		    FROM sp_calctovaroborot(" + id + ", '01.01.2010', '" + pastDateTo.toLocaleDateString() + "') s) s \
			INNER JOIN товар t ON t.КОД = " + id + "\
		    GROUP BY s.ДАТА, t.КОД, t.ИМЯ, t.ЦЕНА, t.ЗАПАС, s.ОПЕРНОМЕР \
		    ORDER BY s.ДАТА";
      AnalyseSales(command, id, "");
}


function AnalyseSales(command, id, groupKey)
{
  
      nomIdMap = {};
      nomNameMap = {};
      bestNomIdMap = {};
      nomZapasMap = {};
      
      totalLastYearSold = 0;
      statInvalid = false;
      var ost = 0;
	
      var query = new Dictionary();
      if (query.open(command, ""))
      {
	query.query();
	
	var totalSold = 0;
	
	var salesByYears = {};
	var salesByYearsAndMonths = {};
	var forecastQuan = 0;
	var forecastSales = {};

	var E = 0;			// Матожидание
	var D = 0;			// Дисперсия
	var sigma = 0;			// Средне-квадратическое отклонение
      
	for (var month = 1; month <= 12; month++)
	{
	  forecastSales[month] = 0;
	}
	
	for (var i = 0; i < query.rowCount(); i++)
	{
	  var year = query.getValue("ДАТА", i).getFullYear();
	  var month = query.getValue("ДАТА", i).getMonth() + 1;
	  var yearAndMonth = year + "." + month;
	  ost = ost + query.getValue("ДБКОЛ", i) - query.getValue("КРКОЛ", i);
	  query.setValue("ОСТАТОК", ost, i);
//	  print(yearAndMonth, ";", query.getValue("ДБКОЛ", i), ";", query.getValue("КРКОЛ", i), ";", query.getValue("ОСТАТОК", i));
	  if (query.getValue("ОПЕРНОМЕР", i) == 1 || query.getValue("ОПЕРНОМЕР", i) == 11)
	  {
	    var sold = query.getValue("КРКОЛ", i);
	    if (sold < 0)
	      sold = 0;
	    // Сгруппируем продажи по годам
	    if (salesByYears[year] == undefined)
	      salesByYears[year] = sold;
	    else
	      salesByYears[year] = salesByYears[year] + sold;

	    // Сгруппируем продажи по годам и месяцам
	    if (salesByYearsAndMonths[yearAndMonth] == undefined)
	      salesByYearsAndMonths[yearAndMonth] = sold;
	    else
	      salesByYearsAndMonths[yearAndMonth] = salesByYearsAndMonths[yearAndMonth] + sold;
	    totalSold = totalSold + sold;
	    // Подсчитаем продажи конкретных позиций за прошедший год
	    if (query.getValue("ДАТА", i) >= lastYear)
	    {
	      var code = query.getValue("КОД", i);
	      if (code in nomIdMap)
		nomIdMap[code] = nomIdMap[code] + sold;
	      else
	      {
		nomIdMap[code] = sold;
		nomNameMap[code] = query.getValue("ИМЯ", i);
		nomZapasMap[code] = query.getValue("ЗАПАС", i);
	      }
	      totalLastYearSold = totalLastYearSold + sold;
	    }
	  }
	}

//	if (totalSold >= 24)
	if (totalLastYearSold > 12)
	{
	  salesType = 1;					// Это не редкие продажи
	  var alignmentSalesByMonths = {};
	  var seasonCoefficients = {}
	  var i = 0;
	  var s = 0;
	  var lastSale = 0;
	  var salesMonths = 0;					// Месяцы, в течение которых производились продажи
	  // Скопируем массив продаж для сглаживания
	  var alignmentSales3 = {};
	  for (year in salesByYears)
	  {
	    for (var month = 1; month <= 12; month++)
	    {
	      var yearAndMonth = year + "." + month;
	      if (salesByYearsAndMonths[yearAndMonth] == undefined)
		salesByYearsAndMonths[yearAndMonth] = 0;
	      alignmentSales3[i] = salesByYearsAndMonths[yearAndMonth];
	      s = s + salesByYearsAndMonths[yearAndMonth];
	      if (s > 0)
	      {
		salesMonths = salesMonths + 1;
	      }
	      if (year == currentYear && month == lastMonth)
		break;
	      i++;
	    }
	  }
	
	  // Метод сглаживания - скользящее среднее по 3 точкам
	  for (var j = 1; j < i - 2; j++)
	  {
	    alignmentSales3[j] = Math.round((alignmentSales3[j-1] + alignmentSales3[j] + alignmentSales3[j+1]) / 3);
	  }
	
	  i = 0;
	  var alignmentTotalSold = 0;
	  for (year in salesByYears)
	  {
	    for (var month = 1; month <= 12; month++)
	    {
	      if (alignmentSalesByMonths[month] == undefined)
		alignmentSalesByMonths[month] = 0;
	      alignmentSalesByMonths[month] = alignmentSalesByMonths[month] + alignmentSales3[i];
	      alignmentTotalSold = alignmentTotalSold + alignmentSales3[i];
	      lastSale = alignmentSales3[i];
	      if (year == currentYear && month == lastMonth)
		break;
	      i++;
	    }
	  }
	// Вычислим сезонные коэффциенты
	  for (var month = 1; month <= 12; month++)
	  {
	    if (alignmentTotalSold > 0 && alignmentSalesByMonths[month] != undefined)
	      seasonCoefficients[month] = alignmentSalesByMonths[month] * 12 / alignmentTotalSold;
	    else
	    {
	      alignmentSalesByMonths[month] = 0;
	      seasonCoefficients[month] = 0;
	    }
	  }
	
	  var totalSoldByYears = 0;
	  app.print("Продажи по годам:");
	  for (year in salesByYears)
	  {
	    if (year >= currentYear - lastYearsQuan && year < currentYear)
	    {
	      app.print("Год " + year + ": " + salesByYears[year]);
	      totalSoldByYears = totalSoldByYears + salesByYears[year];
	    }
	  }
	  var avgYearSold = Math.round(totalSoldByYears / lastYearsQuan);
	  app.print("Средние продажи в год: " + avgYearSold);
	  app.print("Сезонные коэффициенты:");
	  for (var month = 1; month <= 12; month++)
	  {
	    app.print(seasonCoefficients[month]);
	  }
	  var coef = 1;
	  if (avgYearSold > 0 &&  seasonCoefficients[lastMonth] > 0 && lastSale > 0)
	    coef = lastSale * 12 / avgYearSold;
//	  print(coef, lastSale, avgYearSold, seasonCoefficients[lastMonth]);
	  app.print("Коэффициент последних продаж: " + coef);
	  app.print("Прогноз продаж на предстоящие " + forwardMonths + " месяцев:");
	  for (var i = 0; i < forwardMonths; i++)
	  {
	    var month = currentMonth + i;
	    if (month > 12)
	      month = month - 12;
	    if (seasonCoefficients[month] == undefined)
	      seasonCoefficients[month] = 0;
//	    forecastSales[month] = Math.round(avgYearSold * seasonCoefficients[month] / 12);
	    forecastSales[month] = Math.round(coef * avgYearSold * seasonCoefficients[month] / 12);
	    if (forecastSales[month] == 0 && salesMonths > 0)
	      forecastSales[month] = Math.round(totalLastYearSold / 12);
	    forecastQuan = forecastQuan + forecastSales[month];
	    app.print("Месяц " + month + ": " + forecastSales[month]);
	  }
	}
	else		// Если продаж меньше 24 за год, тогда попробуем применить вероятностный подход
	{
	  salesType = 2;		// Это редкие продажи
///*	    
	  if (totalLastYearSold >= 1)
	  {
    
	    var totalSold = 0;
	    var monthsProbabilities = {};
	    var alignedMonthsProbabilities = {};
	    var salesByMonths = {};
	  
	    app.print("За год продается меньше 12 единиц. Применим вероятностный подход.");
	  
	    for (year in salesByYears)
	    {
	      for (var month = 1; month <= 12; month++)
	      {
//		if (year >= currentYear - lastYearsQuan && year < currentYear)
		if (year >= currentYear - lastYearsQuan)		  
		{
		  var yearAndMonth = year + "." + month;
		  var monthSales = salesByYearsAndMonths[yearAndMonth];
		  if (monthSales == undefined || monthSales < 0)
		    monthSales = 0;
		  // Сгруппируем продажи по месяцам 
		  if (salesByMonths[month] == undefined)
		    salesByMonths[month] = monthSales;
		  else
		    salesByMonths[month] = salesByMonths[month] + monthSales;
		  totalSold = totalSold + monthSales;
		}
		i++;
	      }
	    }
	    
	    // Посчитаем вероятности продаж по месяцам
	    for (var month = 1; month <= 12; month++)
	    {
	      if (totalSold > 0)
		monthsProbabilities[month] = salesByMonths[month] / totalSold;
	      else
		monthsProbabilities[month] = 0;
	      app.print(salesByMonths[month] + ";" + monthsProbabilities[month]);
	    }
	    
	    // Посчитаем матожидание и дисперсию
	    for (var month = 1; month <= 12; month++)
	    {
	      E = E + month * monthsProbabilities[month];
	    }
	    for (var month = 1; month <= 12; month++)
	    {
	      D = D + monthsProbabilities[month] * Math.pow(month - E, 2);
	    }
	    
	    if (D > 0)
	    {
	      // Сгладим вероятности методом скользящей средней
	      alignedMonthsProbabilities[1] = (monthsProbabilities[12] + monthsProbabilities[1] + monthsProbabilities[2]) / 3;
	      for (var month = 2; month < 12; month++)
	      {
		alignedMonthsProbabilities[month] = (monthsProbabilities[month-1] + monthsProbabilities[month] + monthsProbabilities[month+1]) / 3;
	      }
	      alignedMonthsProbabilities[12] = (monthsProbabilities[11] + monthsProbabilities[12] + monthsProbabilities[1]) / 3;

	      app.print("Сглаженные вероятности:");
	      for (var month = 1; month <= 12; month++)
	      {
		app.print(alignedMonthsProbabilities[month]);
	      }

	      // Найдем первый месяц, в котором продажи минимальные
	      var firstNullMonth = 1;
	      for (var month = 1; month <= 12; month++)
	      {
		if (alignedMonthsProbabilities[month] < alignedMonthsProbabilities[firstNullMonth])
		{
		  firstNullMonth = month;
		}
	      }
	      // Посчитаем матожидание и дисперсию
	      E = 0;
	      D = 0;
	      for (var i = 0; i < 12; i++)
	      {
		var probMonth = firstNullMonth + i;
		var month = probMonth;
		if (month > 12)
		  month = month - 12;
		E = E + probMonth * alignedMonthsProbabilities[month];
	      }
	      for (var i = 0; i < 12; i++)
	      {
		var probMonth = firstNullMonth + i;
		var month = probMonth;
		if (month > 12)
		  month = month - 12;
		D = D + alignedMonthsProbabilities[month] * Math.pow(probMonth - E, 2);
	      }
	    }
	    if (E > 12)
	      E = E - 12;
	    E = Math.round(E*100)/100;
	    D = Math.round(D*100)/100;
	    app.print("Матожидание = " + E);
//	    app.print("Дисперсия = " + D);
	    sigma = Math.sqrt(D);
	    sigma = Math.round(sigma*100)/100;
	    app.print("Ср.квадр.отклонение = " + sigma);
	  
	    if (sigma >= 2.5)
	    {
//	      if (ost > 0)
//	      {
//		app.print("Продается редко в течение года. Не будем заказывать, т.к. имеется остаток в количестве " + ost + " ед.");
//		forecastSales[currentMonth] = 0;
//	      }
//	      else
//	      {
		app.print("Продается редко в течение года. Закажем 1 ед.");
		forecastSales[currentMonth] = 1;
//	      }
	      forecastQuan = forecastSales[currentMonth];
	    }
	    else if (sigma > 0)
	    {
	      app.print("Всего продано за последний год " + totalLastYearSold);
	      forecastQuan = 0;
	      var prob = 0;
	      for (var i = 0; i < forwardMonths; i++)
	      {
		var month = currentMonth + i;
		if (month > 12)
		  month = month - 12;
		prob = prob + alignedMonthsProbabilities[month];
		forecastSales[month] = Math.round(prob*totalLastYearSold);
		forecastQuan = forecastQuan + forecastSales[month];
	      }
	      app.print("Вероятность продать в предстоящие " + forwardMonths + " месяца: " + prob);
	      if (forecastQuan < 1 && prob >= 0.08)
		forecastQuan = 1;
	    }
	    else
//*/	      
	      forecastQuan = 1;
	   }
	   else
	      forecastQuan = 0;
	}
	
	if (forecastQuan > 0)
	    setMostPopularPositions(forecastQuan);
	
	if (id == 0)
	    db.exec("UPDATE товар SET АВТЗАПАС = 0 WHERE ШИФР_ПО_КАТАЛОГУ = '" + key + "' AND ЦЕНА > 0;");
	else
	    db.exec("UPDATE товар SET АВТЗАПАС = 0 WHERE КОД = " + id + " AND ЦЕНА > 0;");
	
//	if (forecastQuan > 0)
//	{
	  var ostQuery;
	  if (id == 0)
	  {
	    ostQuery = db.execQuery("SELECT t.КОД AS КОД, ИМЯ, КОМПЛЕКТ, КОНКОЛ AS КОЛ \
				    FROM товар t LEFT OUTER JOIN (SELECT * FROM vw_saldo411_1 WHERE КОД_АДРЕС <> 512) s ON s.КОД_ТОВАР = t.КОД \
				    WHERE t.ШИФР_ПО_КАТАЛОГУ = '" + key + "';");
	  }
	  else
	  {
	    ostQuery = db.execQuery("SELECT t.КОД AS КОД, ИМЯ, КОМПЛЕКТ, КОНКОЛ AS КОЛ \
				    FROM товар t LEFT OUTER JOIN (SELECT * FROM vw_saldo411_1 WHERE КОД_АДРЕС <> 512) s ON s.КОД_ТОВАР = t.КОД \
				    WHERE t.КОД = " +  id + ";");
	  }
	  ViewKompl(ostQuery);
//	}
	
	SetAutoZapas(forecastQuan);

// Запишем результаты в базу данных	
	var command = "";
	var recQuan;
	if (id == 0)
	  recQuan = db.getValue("SELECT COUNT(*) FROM анализ_продаж WHERE ШИФР_ПО_КАТАЛОГУ = '" + groupKey + "'");
	else
	  recQuan = db.getValue("SELECT COUNT(*) FROM анализ_продаж WHERE КОД_ТОВАР = " + id);
	if (recQuan == 0)
	{
	  var command1 = "МАТОЖИДАНИЕ,СИГМА,ПРОДАНО_ПОСЛ_ГОД,ТИП_ПРОДАЖ,";
	  var command2 = E + "," + sigma + "," + totalLastYearSold + "," + salesType + ",";
	  for (var i = 0; i < forwardMonths; i++)
	  {
	    var month = currentMonth + i;
	    if (month > 12)
	      month = month - 12;
	    command1 = command1 + "ПРОГНОЗ_" + month + ",";
	    command2 = command2 + forecastSales[month] + ",";
	  }
	  command1 = command1.slice(0, -1);
	  command2 = command2.slice(0, -1);
	  command = "INSERT INTO анализ_продаж (КОД_ТОВАР, ШИФР_ПО_КАТАЛОГУ," + command1 + ") VALUES (" + id + ",'" + groupKey + "'," + command2 + ")";
	}
	else
	{
	  var command1 = "МАТОЖИДАНИЕ=" + E + ",СИГМА=" + sigma + ",ПРОДАНО_ПОСЛ_ГОД=" + totalLastYearSold + ",ТИП_ПРОДАЖ=" + salesType + ",";
	  for (var i = 0; i < forwardMonths; i++)
	  {
	    var month = currentMonth + i;
	    if (month > 12)
	      month = month - 12;
	    command1 = command1 + "ПРОГНОЗ_" + month + "=" + forecastSales[month] + ",";
	  }
	  command1 = command1.slice(0, -1);
	  command = "UPDATE анализ_продаж SET " + command1 + " WHERE ";
	  if (id == 0)
	    command = command + "ШИФР_ПО_КАТАЛОГУ = '" + groupKey + "'";
	  else
	    command = command + "КОД_ТОВАР = " + id;
	}
	db.exec(command);
	
//	app.printReport("АнализПродажПоНеделям.ods", query);
	
      }
      query.close();
}


function setMostPopularPositions(forecastQuan)
{
  // Выберем позиции, которые дают 80% оборота
  var sortedNomIdMap = [];
  app.print();
  app.print("Определим самые оборачиваемые позиции. За последний год продано:");
  for(id in nomIdMap)
  {
    if (sortedNomIdMap.indexOf(nomIdMap[id]) == -1)
      sortedNomIdMap.push(nomIdMap[id]);
  }
  sortedNomIdMap.sort(function(a,b){return b - a});
      
  for (var i = 0; i < sortedNomIdMap.length; i++)
  {
    for(id in nomIdMap)
    {	  
      if (nomIdMap[id] == sortedNomIdMap[i])
	app.print(id + " " + nomNameMap[id] + " - " + nomIdMap[id] + " ед");
    }
  }
	
  bestTotalSold = 0;
  for (var i = 0; i < sortedNomIdMap.length; i++)
  {
    for(id in nomIdMap)
    {
      if (nomIdMap[id] == sortedNomIdMap[i] && nomZapasMap[id] >= 0)
      {
	bestNomIdMap[id] = nomIdMap[id];
	bestTotalSold = bestTotalSold + nomIdMap[id]; 
	if (bestTotalSold >= totalLastYearSold * 0.9)
	{
	  i = sortedNomIdMap.length;	// Это нужно, чтобы выйти из двойного цикла
	  break;
	}
      }
    }
  }
  for(id in bestNomIdMap)
  {
    bestNomIdMap[id] = Math.round(bestNomIdMap[id] * forecastQuan / bestTotalSold);
/*    
    // Если в результате округления получился ноль, закажем хотя бы одну единицу товара. т.к. прогноз продаж не нулевой
    if (bestNomIdMap[id] == 0)
    {
      bestNomIdMap[id] = 1;
    }
*/    
  }
}


function ViewKompl(query)	// Проверим комплектность
{
  komplNomIdMap = {};
	
  if (query.first())
  {
    var totOst = 0;

    if (query.isValid())
    {
	app.print();
	app.print("Имеются остатки и дополнения до комплекта:");
    }
    
    while (query.isValid())
    {
	var record = query.record();
	var id = record.value("КОД");
	var ost = record.value("КОЛ");
	var kompl = record.value("КОМПЛЕКТ");
	totOst = totOst + ost;
	if (ost > 0)
	{
	  if (ost < kompl)
	  {
//	    if (!(id in bestNomIdMap))
//	    {
		db.exec("UPDATE товар SET ЗАПАС = CASE WHEN ЗАПАС < 0 THEN 0 ELSE ЗАПАС END, АВТЗАПАС = " + kompl + " WHERE КОД = " + id);
		app.print(record.value("ИМЯ") + " - " + ost + " ед (будет дополнено до " + kompl + ")");
//	    }
	  }
	  else
	  {
	    app.print(record.value("ИМЯ") + " - " + ost + " ед (остаток)");
	  }
	}
	komplNomIdMap[id] = kompl;
	query.next();
    }
  }
}


function SetAutoZapas(forecastQuan)
{
  if (forecastQuan > 0)
  {
    app.print();
    app.print("Предполагается продать за период всего:");
  }
  for(id in bestNomIdMap)
  {
    if (forecastQuan >= 0)
    {
      var quan = bestNomIdMap[id];
      if (quan < komplNomIdMap[id])
	quan = komplNomIdMap[id];
      if (quan >= 0)
      {
	WriteLog(id, quan, modelNumber);
	db.exec("UPDATE товар SET АВТЗАПАС = " + quan + " WHERE КОД = " + id);
	if (quan > 0)
	  app.print(nomNameMap[id] + " - " + quan + " ед")
      }
      forecastQuan = forecastQuan - quan;
    }
    else
      break;
  }
}


function WriteLog(nomId, quan, modelNumber)
{
    var command = "SELECT * FROM журнал_прогнозов";
    var WHEREclause = " WHERE ";
    WHEREclause = WHEREclause + "НОМЕР_МОДЕЛИ = " + modelNumber + " AND КОД_ТОВАР = " + nomId;
    WHEREclause = WHEREclause + " AND ГОД = " + currentYear + " AND МЕСЯЦ = " + currentMonth;
    command = command + WHEREclause;
    var query = db.execQuery(command);
    if (query.first())		// Если в журнале уже есть запись для этого периода
      command = "UPDATE журнал_прогнозов SET ПРОГНОЗПРОДАЖ = " + quan + WHEREclause;
    else
      command = "INSERT INTO журнал_прогнозов (НОМЕР_МОДЕЛИ, КОД_ТОВАР, ГОД, МЕСЯЦ, ПРОГНОЗПРОДАЖ) VALUES (" + modelNumber + ", " + nomId + ", " + currentYear + ", " + currentMonth + ", " + quan + ");";
    db.exec(command);
}

