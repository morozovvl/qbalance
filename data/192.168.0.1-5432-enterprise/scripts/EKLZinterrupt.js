var drvFR = 0;

if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    var result = drvFR.EKLZInterrupt();
    drvFR.DisConnect();
  }
}
