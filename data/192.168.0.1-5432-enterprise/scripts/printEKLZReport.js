var drvFR = 0;
var smenaForm = app.createForm("смена");


if (app.drvFRisValid() && smenaForm != null)			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    smenaForm.findChild("lineEditSmena").setText(drvFR.getProperty("SessionNumber") + 1)
    smenaForm.exec()
    if (smenaForm.isFormSelected())
    {
      drvFR.setProperty("SessionNumber", smenaForm.findChild("lineEditSmena").text);
      string = "";
      var result = drvFR.GetEKLZJournal();
      while (result == 0)
      {
	var str = drvFR.getProperty("EKLZData");
	if (str.substr(0, 7) == "ПРОДАЖА")
	  app.print();
	if (str.substr(0, 7) == "ВОЗВ.ПР")
	  app.print();
	if (str.substr(0, 10) == "ЗАКР.СМЕНЫ")
	  app.print();
	app.print(str);
	result = drvFR.GetEKLZData();
      }
      processStr(str);
    }
    drvFR.DisConnect();
  }
}
