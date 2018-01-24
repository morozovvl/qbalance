//db.exec("SELECT sp_analyze_sale();");
app.getDictionary("товар").query();
app.runScript("обработка.Подготовить заказ на основе прогноза продаж.js");
