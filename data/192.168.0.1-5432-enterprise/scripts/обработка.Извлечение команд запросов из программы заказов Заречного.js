var fileName;

scriptResult = 1;

if (app.getScript().length > 0)                 // Если в параметрах приложения задано выполнение этого скрипта
  fileName = app.getScriptParameter();          // То имя файла с документами возьмем тоже из параметров
else
{
  app.setDirName("ZarechDumpDir");  
  fileName = app.getOpenFileName(app, "Откройте документ с дампом памяти программы Заречного", "", "Документ mem (*.mem)");
}
var file = new QFile(fileName);
if (file.open(QIODevice.OpenMode(QIODevice.ReadOnly))) 
{
  var fileData = file.readAll();
//  var searchString = new QByteArray(QByteArray.fromHex("53454C45435420"));
//  var searchString1 = new QByteArray(QString.toUtf8("select "));
//  var rowCount = fileData.count(searchString);
//  var progress = ProgressDialog("Извлечение запросов. Ожидайте...");
//  progress.show();
//  progress.setMaximum(rowCount);
  var index = 0;
  var i = 0;
  while (true)
  {
    index = fileData.indexOf("SELECT ", index);
    var strArray = fileData.mid(index, fileData.indexOf('/x0', index + 1) - index);
    var commandText = "";
    for (var j = 0; j < strArray.size(); j++)
    {
      commandText = commandText + String.fromCharCode(strArray.at(j));
    }
    print(commandText);
//    progress.setValue(i);
    if (index < 0)
      break;
    else
      index++;
    i++;
  }
  var index = 0;
  while (true)
  {
    index = fileData.indexOf("select ", index);
    var strArray = fileData.mid(index, fileData.indexOf('/x0', index + 1) - index);
    var commandText = "";
    for (var j = 0; j < strArray.size(); j++)
    {
      commandText = commandText + String.fromCharCode(strArray.at(j));
    }
    print(commandText);
//    progress.setValue(i);
    if (index < 0)
      break;
    else
      index++;
    i++;
  }
/*  
  var index = 0;
  while (true)
  {
    index = fileData.indexOf(searchString1, index);
    var len = fileData.mid(index-1, 1).toHex().toInt();
    var strArray = fileData.mid(index, len);
    var commandText = "";
    for (var j = 0; j < strArray.size(); j++)
    {
      commandText = commandText + String.fromCharCode(strArray.at(j));
    }
    print(commandText);
    progress.setValue(i);
    if (index < 0)
      break;
    else
      index++;
    i++;
  }
*/  
//  progress.hide();
  file.close();
}
