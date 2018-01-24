var drvFR = 0;
var sumForm = app.createForm("суммавозвратапродажи");


if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    sumForm.exec()
    if (sumForm.isFormSelected())
    {
      var sum = sumForm.findChild("lineEditSum").text;
      
      drvFR.setProperty("StringForPrinting", "товар");
      drvFR.setProperty("Quantity", 1);
      drvFR.setProperty("Price", sum);
      drvFR.setProperty("Department", 1);
      drvFR.setProperty("Tax1", 0);
      drvFR.setProperty("Tax2", 0);
      drvFR.setProperty("Tax3", 0);
      drvFR.setProperty("Tax4", 0);
      drvFR.ReturnSale();
      
      drvFR.setProperty("StringForPrinting", "");
      drvFR.setProperty("Summ1", sum);
      drvFR.setProperty("Summ2", 0);
      drvFR.setProperty("Summ3", 0);
      drvFR.setProperty("Summ4", 0);
      drvFR.setProperty("DiscountOnCheck", 0);
      drvFR.setProperty("Tax1", 0);
      drvFR.setProperty("Tax2", 0);
      drvFR.setProperty("Tax3", 0);
      drvFR.setProperty("Tax4", 0);
      drvFR.CloseCheck();
    }
    drvFR.DisConnect();
  }
}
