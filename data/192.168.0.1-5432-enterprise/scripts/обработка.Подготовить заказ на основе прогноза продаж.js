var modelNumber = 1;		// Номер математической модели прогноза

var forwardMonths = 1;
var lastYearsQuan = 3;
var lastMonths = 6;
var articulMap = {};
var currentDate = new Date();
var lastYear = new Date();
var currentYear;
var currentMonth;
var scenario = "";

var yearSoldMap = {};		// Продано за конкретный год
var yearSoldMapLength = 0;
var nomIdMap = {};		// Позиции, проданные за последний год
var totalLastYearSold = 0;
var nomNameMap = {};		// Позиции, проданные за последний год
var komplNomIdMap = {};
var bestNomIdMap = {};
var sortedNomIdMap = [];
var totOst = 0;
var soldQuan = 0;
var maxQuan = 0;
var forecastOk = true;
var forecastQuan = 0;
var bestTotalSold = 0;
var articul;
var nomId;
var nomPrice;
var articulAvgPrice = {};



currentDate.setDate(currentDate.getDate() + 15);
lastYear.setDate(currentDate.getDate() - 365);
currentYear = currentDate.getFullYear();
currentMonth = currentDate.getMonth() + 1;

var pastDateFrom = new Date(currentYear - lastYearsQuan, 0, 1);
var pastDateTo = new Date(currentDate);

//app.print(currentDate.toLocaleDateString());
//app.print(lastYear.toLocaleDateString());
app.print();
app.print();
app.print("Месяц для заказа: " + currentMonth + ". Запас вперед на, месяцев: " + forwardMonths);
app.print("Начало периода: " + pastDateFrom.toLocaleDateString() + "; Конец периода: " + pastDateTo.toLocaleDateString());

var nomDict = app.getDictionary("товар");

for (var i = 0; i < nomDict.rowCount(); i++)
{
  articul = nomDict.getValue("ШИФР_ПО_КАТАЛОГУ", i).trim();
  if (articul.length > 0 && nomDict.getValue("ЗАПАС", i) >= 0)
  {
    if (articul in articulMap)
    {
      articulMap[articul] = articulMap[articul] + 1;
      articulAvgPrice[articul] = articulAvgPrice[articul] + nomDict.getValue("ЦЕНА", i);
    }
    else
    {
      articulMap[articul] = 1;
      articulAvgPrice[articul] = nomDict.getValue("ЦЕНА", i);
    }
  }
}
nomId = 0;
nomPrice = 0;
AnalyseGroups();

articulMap = [];

for (var i = 0; i < nomDict.rowCount(); i++)
{
  articul = nomDict.getValue("ШИФР_ПО_КАТАЛОГУ", i).trim();
  nomId = nomDict.getValue("КОД", i);
  nomPrice = nomDict.getValue("ЦЕНА", i);
  if (articul.length == 0 && nomDict.getValue("ЗАПАС", i) >= 0)
  {
    AnalyseSingle(nomId, nomDict.getValue("ИМЯ", i));
  }
}


function AnalyseGroups()
{
  forecastOk = true;
  // Сначала посчитаем среднее количество проданного товара из этой группы за аналогичный период в прошлые года
  for(key in articulMap) 
  {
    articul = key;
    if (articulMap[key] >= 1)
    {
      var id;

      app.print();
      app.print("=======================Группа: " + key);
      
      var command = "SELECT s.ДАТА, s.КОД, t.ИМЯ, t.ЦЕНА, s.КРКОЛ-s.ДБКОЛ AS КОЛ \
		      FROM sp_calcgrouptovaroborot('" + key + "', '" + pastDateFrom.toLocaleDateString() + "', '" + pastDateTo.toLocaleDateString() + "') s \
		      INNER JOIN товар t ON s.КОД = t.КОД \
		      WHERE s.ОПЕРНОМЕР IN (1, 11, 71) AND t.ЗАПАС >= 0;";
      query = db.execQuery(command);
      
      nomPrice = articulAvgPrice[key] / articulMap[key];

      AnalyseSales(query);

      forecastOk = true;
      if (forecastQuan > 0)
      {
	// Выберем позиции, которые дают 80% оборота
	bestNomIdMap = {};
	sortedNomIdMap = [];
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
	    {
	      app.print(id + " " + nomNameMap[id] + " - " + nomIdMap[id] + " ед");
	    }
	  }
	}
	
	bestTotalSold = 0;
	for (var i = 0; i < sortedNomIdMap.length; i++)
	{
	  for(id in nomIdMap)
	  {
	    if (nomIdMap[id] == sortedNomIdMap[i])
	    {
	      bestNomIdMap[id] = nomIdMap[id];
	      bestTotalSold = bestTotalSold + nomIdMap[id]; 
	      if (bestTotalSold >= totalLastYearSold * 0.8)
	      {
		i = sortedNomIdMap.length;	// Это нужно, чтобы выйти из двойного цикла
		break;
	      }
	    }
	  }
	}

	// Определим, сколько и какие позиции мы будем заказывать
	db.exec("UPDATE товар SET АВТЗАПАС = 0 WHERE ШИФР_ПО_КАТАЛОГУ = '" + key + "';");

	komplNomIdMap = {};
	
	// Дополним остатки до полных комплектов
	query = db.execQuery("SELECT t.КОД AS КОД, ИМЯ, КОМПЛЕКТ, КОНКОЛ AS КОЛ \
			      FROM vw_saldo411_1 s RIGHT OUTER JOIN товар t ON s.КОД_ТОВАР = t.КОД \
			      WHERE t.ШИФР_ПО_КАТАЛОГУ = '" +  key + "' AND COALESCE(КОД_АДРЕС, 0) <> 512;");

	ViewKompl(query);

//	if (lastYearsQuan > 1)
//	{
	  SetAutoZapas();
//	}
//	else
//	  forecastOk = false;
      }
      else
      {
	forecastOk = false;
      }
      if (!forecastOk)
      {
	db.exec("UPDATE товар SET АВТЗАПАС = ЗАПАС WHERE ШИФР_ПО_КАТАЛОГУ = '" + key + "';");
	ShowForecastError();
      }
    }
  }
}


function AnalyseSingle(id, name)
{
      forecastOk = true;
      app.print();
      app.print("=======================Позиция: " + name);
      
      var command = "SELECT s.ДАТА, " + id + " AS КОД, '" + name + "' AS ИМЯ, s.КРКОЛ-s.ДБКОЛ AS КОЛ \
		      FROM sp_calctovaroborot(" + id + ", '" + pastDateFrom.toLocaleDateString() + "', '" + pastDateTo.toLocaleDateString() + "') s \
		      WHERE s.ОПЕРНОМЕР IN (1, 11, 71);";
      query = db.execQuery(command);

      AnalyseSales(query);

      forecastOk = true;
      if (forecastQuan > 0)
      {
	komplNomIdMap = {};
	
	// Дополним остатки до полных комплектов
	query = db.execQuery("SELECT t.КОД AS КОД, ИМЯ, КОМПЛЕКТ, КОНКОЛ AS КОЛ \
			      FROM vw_saldo411_1 s RIGHT OUTER JOIN товар t ON s.КОД_ТОВАР = t.КОД \
			      WHERE t.КОД = " +  id + " AND COALESCE(КОД_АДРЕС, 0) <> 512;");
	ViewKompl(query);

//	if (lastYearsQuan > 1)
//	{
	  bestNomIdMap = {};
	  bestNomIdMap[id] = forecastQuan;
	  bestTotalSold = forecastQuan;
	  
	  SetAutoZapas();
//	}
//	else
//	  forecastOk = false;
      }
      else
      {
	forecastOk = false;
      }
      if (!forecastOk)
      {
	db.exec("UPDATE товар SET АВТЗАПАС = CASE WHEN ЗАПАС > 0 THEN ЗАПАС ELSE 0 END WHERE КОД = " + id + ";");
	ShowForecastError();
      }
}


function AnalyseSales(query)
{
      yearSoldMap = {};		// Продано за конкретный год
      yearSoldMapLength = 0;
      nomIdMap = {};		// Позиции, проданные за последний год
      totalLastYearSold = 0;
      nomNameMap = {};		// Позиции, проданные за последний год

/*      
      pastDateFrom = currentDate;
      pastDateTo = currentDate;
      pastDateTo.setUTCDate(pastDateTo.getDate() + 1);
      print(currentDate.toLocaleDateString(), pastDateFrom.toLocaleDateString(), pastDateTo.toLocaleDateString())
*/

      var year;
      if (query.first())
      {
	while (query.isValid())
	{
	  var record = query.record();
	  // Подсчитаем продажи за аналогичный период прошлых лет
	  id = record.value("КОД");
	  if (!(id in nomNameMap))
	    nomNameMap[id] = record.value("ИМЯ");

	  if (record.value("ДАТА").getMonth() + 1 == currentMonth)
	  {
	    year = record.value("ДАТА").getFullYear();
	    if (record.value("КОЛ") > 0)
	    {
	      if (year in yearSoldMap)
		yearSoldMap[year] = yearSoldMap[year] + record.value("КОЛ");
	      else
	      {
		yearSoldMap[year] = record.value("КОЛ");
		yearSoldMapLength = yearSoldMapLength + 1;
	      }
	    }
	  }
	  // Подсчитаем продажи конкретных позиций за прошедший год
	  if (record.value("ДАТА") >= lastYear)
	  {
	    year = record.value("ДАТА").getFullYear();
	    if (id in nomIdMap)
	      nomIdMap[id] = nomIdMap[id] + record.value("КОЛ");
	    else
	    {
	      nomIdMap[id] = record.value("КОЛ");
	    }
	    totalLastYearSold = totalLastYearSold + record.value("КОЛ");
	  }
	  query.next();
	}
	if (yearSoldMapLength == 0)
	{
	  if (totalLastYearSold > 0)
	  {
	    yearSoldMapLength = 1;
	    yearSoldMap[year] = Math.round(totalLastYearSold * forwardMonths / 12);
	    if (yearSoldMap[year] == 0)
	      yearSoldMap[year] = 1;
	  }
	}
	
      }
      ShowPastSalesInfo();
}


function ViewKompl(query)	// Проверим комплектность
{
  if (query.first())
  {
    if (query.size())
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
	    if (!(id in bestNomIdMap))
	    {
/*	      
		forecastQuan = forecastQuan - kompl;
*/		
		db.exec("UPDATE товар SET ЗАПАС = CASE WHEN ЗАПАС < 0 THEN 0 ELSE ЗАПАС END, АВТЗАПАС = " + kompl + " WHERE КОД = " + id);
		app.print(record.value("ИМЯ") + " - " + ost + " ед (будет дополнено до " + kompl + ")");
	    }
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


function SetAutoZapas()
{
  if (forecastQuan > 0)
  {
    app.print();
    app.print("Предполагается продать за период:");
    totOst = 0;
    var oneAdded = false;
    for(id in bestNomIdMap)
    {
	if (forecastQuan == 0)
	  bestNomIdMap[id] = 0;
	else
	  {
	    bestNomIdMap[id] = Math.round(bestNomIdMap[id] * forecastQuan / bestTotalSold);
	    // Если в результате округления получился ноль, закажем хотя бы одну единицу товара. т.к. прогноз продаж не нулевой
	    if (bestNomIdMap[id] == 0 && !oneAdded)
	    {
	      bestNomIdMap[id] = 1;
	      oneAdded = true;
	    }
	    if (bestNomIdMap[id] > 0)
	      app.print(nomNameMap[id] + " - " + bestNomIdMap[id] + " ед")
	  }
    }

    for(id in bestNomIdMap)
    {
	var quan = bestNomIdMap[id];
	if (quan > forecastQuan)
	{
	  quan = forecastQuan;
	}
	forecastQuan = forecastQuan - quan;
	if (quan > 0)
	{
	  WriteLog(id, quan, modelNumber);
	  if (quan < komplNomIdMap[id])
	    quan = komplNomIdMap[id];
	  db.exec("UPDATE товар SET АВТЗАПАС = " + quan + " WHERE КОД = " + id);
	}
	else
	  break;
    }
  }
  else
  {
    app.print();
    app.print("Имеющихся остатков пока достаточно");
  }
}


function ShowPastSalesInfo()
{
  soldQuan = 0;
  maxQuan = 0;
  if (yearSoldMap.length)
  {
    app.print();
    app.print("Продано в прошлом за аналогичный период:");
  }
  var lastYear1 = 0;
  for(year in yearSoldMap) 
  {
    app.print(year + " год - " + yearSoldMap[year] + " ед");
    soldQuan = soldQuan + yearSoldMap[year];
    if (yearSoldMap[year] > maxQuan)
	maxQuan = yearSoldMap[year];
    if (year > lastYear1 && year != currentYear)
      lastYear1 = year;
  }
  var avgQuan = 0;
  forecastQuan = 0;
  if (yearSoldMapLength > 0)
  {
/*    
    if (yearSoldMapLength > 1)
      avgQuan = Math.round(soldQuan / lastYearsQuan);	
    else
    {
      if (lastYear1 == lastYear.getFullYear()) 
	avgQuan = Math.round(soldQuan / yearSoldMapLength);
    }
*/    
    avgQuan = Math.round(soldQuan / yearSoldMapLength);
//    forecastQuan = Math.round((maxQuan + avgQuan)/2);
    forecastQuan = avgQuan;
    scenario = "";
	
//	if (yearSoldMap[lastYear1] < forecastQuan)		// Если в последний год продано меньше, чем прогноз
//	{
//	  forecastQuan = yearSoldMap[lastYear1];			// то будем прогнозировать минимальный объем продаж
//	  scenario = " (Пессимистичный сценарий)";
//	}
	
    app.print("Макс.продажа = " + maxQuan + "; Сред.продажа = " + avgQuan + "; Прогноз.продаж = " + forecastQuan + scenario);
    
/*    
    if (nomPrice >= 500 && forecastQuan > 1 && forecastQuan < 12)	// Если стоимость позиции больше или равно 500 рублей и продается
    {									// около 1 шт, то уменьшим заказ в 2 раза
      forecastQuan = Math.round((forecastQuan / 2) - 0.05);
    }
*/    
  }
}


function ShowForecastError()
{
  app.print();
  app.print("Имеющихся данных не достаточно для прогноза. Заказ будет сделан на основании колонки ЗАПАС.");
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
