var id = pictureId;
if (firmId == 117)		// Если это позиция из прайса Паскера
{
	table.setPhotoPath("паскер");
//	url = "http://pasker.ru/photo_lib/" + id + ".jpg";
	url = "http://pasker.ru/photo_lib/" + id + ".jpg";
}
else if (firmId == 419)
{
	table.setPhotoPath("курсавто");
	url = "http://kursavto.ru/files/autokurs2/photo/ka" + id + ".jpg";
}
else if (firmId == 224)
{
	table.setPhotoPath("заречье");
	url = "http://alexusjo.bget.ru/index.php?route=update/exchange2/get_image&pass=cTMzwvLvZKksC&w=-1&n=" + id + ".jpg";
//	url = "http://www.td-zar.ru/components/com_virtuemart/shop_image/product/" + id + ".jpg";
	
}
else if (firmId == 386)
{
	table.setPhotoPath("тис");
	var fName = "00000" + id;
	url = "http://trans-import.ru/pic/" + fName.slice(-5) + ".jpg";
}
else if (firmId == 420)
{
	table.setPhotoPath("тис-восток");
	url = "";
/*	
	if (table.isFieldExists("PHOTO_URL"))
	{
	  url = table.getValue("PHOTO_URL");
	}
*/	
}
else if (firmId == 416)
{
	table.setPhotoPath("гала");
	url = "";
	if (table.isFieldExists("PHOTO_URL"))
	{
	  var id = table.getValue("PHOTO_URL");
	  if (id.length > 0)
	    url = "http://image.galacentre.ru/" + id + ".jpg";
	}
}
else if (firmId == 426)
{
	table.setPhotoPath("магистраль-нн");
	var fName = "00000" + id;
	url = "http://www.magistral-nn.ru/upload/prod_images/catalog/" + fName.slice(-6) + ".jpg";
}
else if (firmId == 427)
{
	table.setPhotoPath("нормаль");
	if (table.isFieldExists("PHOTO_URL"))
	  url = table.getValue("PHOTO_URL");
	else
	  url = "";
}
else if (firmId == 193)
{
	table.setPhotoPath("юникс");
	var fName = "00000" + id;
	url = "http://www.unixmagazin.ru/assets/images/products/" + fName.slice(-6) + ".jpg";
}
else if (firmId == 410)
{
	table.setPhotoPath("бином");
	url = "";
}
else if (firmId == 434)
{
	table.setPhotoPath("арм");
	url = "";
}
else if (firmId == 440)
{
	table.setPhotoPath("нпн");
	url = "http://npn.su/img/foto/f" + id + ".jpg";
}
else
{
	table.setPhotoIdField("");
}
