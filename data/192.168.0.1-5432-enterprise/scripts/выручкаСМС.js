var drvFR = 0;

if (app.drvFRisValid())			// Если фискальный регистратор присутствует в системе
{
  drvFR = app.getDrvFR();
  if (drvFR.Connect())
  {
    drvFR.Beep();
    drvFR.DisConnect();
  }
}
