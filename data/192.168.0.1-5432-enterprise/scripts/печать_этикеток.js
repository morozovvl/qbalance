var quanFormName = "количество_этикеток";
var quanForm = app.createForm(quanFormName);
if (quanForm != null)
{
  var lineEdit = quanForm.findChild("spinBoxQuantity");
//  lineEdit.setMaximum(10);
  lineEdit.setValue(labelQuan);
  quanForm.exec();
  if (quanForm.isFormSelected())
  {
	table.printLabel("Ценник", lineEdit.text);
  }
}
else
	app.showError("Не найдена форма" + quanFormName);
