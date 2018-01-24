var drvFR = 0;

if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
{
  var msg = new QMessageBox(app, "Внимание!", "Вы уверены, что хотите снять ФИСКАЛЬНЫЙ ОТЧЕТ С ГАШЕНИЕМ?", QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No), app);
  if (msg.exec() == QMessageBox.Yes)
  {
    drvFR = app.getDrvFR();
    if (drvFR.Connect())
    {
      drvFR.PrintReportWithCleaning();
      drvFR.PrintString("", 3);
      drvFR.DisConnect();
    }
  }
}
else
  QMessageBox.warning(app, "Внимание!", "Фискальный регистратор не подключен.");


