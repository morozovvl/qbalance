var firmId = 416;	// Код фирмы Гала
var fileName;

scriptResult = 1;

if (app.getScript().length > 0)                 // Если в параметрах приложения задано выполнение этого скрипта
  fileName = app.getScriptParameter();          // То имя файла с документами возьмем тоже из параметров
else
{
  app.setDirName("galaPhotoAnalyse");
  fileName = app.getOpenFileName(app, "Откройте документ с дампом памяти таблицы Гала", "", "Документ mem (*.mem)");
}
var file = new QFile(fileName);
if (file.open(QIODevice.OpenMode(QIODevice.ReadOnly, QIODevice.Text))) 
{
  var fileData = file.readAll();
  var text = new QTextStream(file);
  var searchString = new QByteArray("$U]");
  var rowCount = fileData.count(searchString);
  var progress = ProgressDialog("Дешифровка фотографий Гала. Ожидайте...");
  progress.show();
  progress.setMaximum(rowCount);
  var index = 0;
  for (var i = 0; i < rowCount; i++)
  {
    index = fileData.indexOf(searchString, index);
    var len = fileData.mid(index+4, 1).toHex().toInt();
    var strArray = fileData.mid(index+5, len);
    var pictureId = "";
    for (var j = 0; j < strArray.size(); j++)
    {
      pictureId = pictureId + String.fromCharCode(strArray.at(j));
    }
    len = fileData.mid(index+26, 1).toHex().toInt();
    var strArray = fileData.mid(index+27, len);
    var id = "";
    for (var j = 0; j < strArray.size(); j++)
    {
      id = id + String.fromCharCode(strArray.at(j));
    }
    id = id.replace(/^0/g, "");
    var command = "UPDATE прайс SET \"PHOTO_URL\" = '" + pictureId + "' WHERE КОД_ФИРМЫ = " + firmId + " AND КОДВПРАЙСЕ = '" + id + "';";
    print(command);
    db.appendCommand(command);
    
    index++;
    progress.setValue(i);
  }
  db.execCommands();
  progress.hide();
  file.close();
}
app.print("В дампе " + fileName + " найдено " + rowCount + " позиции");
