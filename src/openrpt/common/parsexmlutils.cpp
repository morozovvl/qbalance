/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2012 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include "parsexmlutils.h"
#include "reportpageoptions.h"
#include "memdbloader.h"

#include <QDomDocument>


//
// Class ORObject 
//
ORObject::ORObject() : _rotation(0) { }
ORObject::~ORObject() { }

bool ORObject::isLine() { return false; }
bool ORObject::isRect() { return false; }
bool ORObject::isLabel() { return false; }
bool ORObject::isField() { return false; }
bool ORObject::isText() { return false; }
bool ORObject::isBarcode() { return false; }
bool ORObject::isImage() { return false; }
bool ORObject::isGraph() { return false; }
bool ORObject::isCrossTab() { return false; }

ORLineData * ORObject::toLine() { return 0; }
ORRectData * ORObject::toRect() { return 0; }
ORLabelData * ORObject::toLabel() { return 0; }
ORFieldData * ORObject::toField() { return 0; }
ORTextData * ORObject::toText() { return 0; }
ORBarcodeData * ORObject::toBarcode() { return 0; }
ORImageData * ORObject::toImage() { return 0; }
ORGraphData * ORObject::toGraph() { return 0; }
ORCrossTabData * ORObject::toCrossTab() { return 0; }


//
// class OR*Data
//
bool ORLineData::isLine() { return TRUE; }
ORLineData * ORLineData::toLine() { return this; }

bool ORRectData::isRect() { return TRUE; }
ORRectData * ORRectData::toRect() { return this; }

bool ORLabelData::isLabel() { return TRUE; }
ORLabelData * ORLabelData::toLabel() { return this; }

bool ORFieldData::isField() { return TRUE; }
ORFieldData * ORFieldData::toField() { return this; }

bool ORTextData::isText() { return TRUE; }
ORTextData * ORTextData::toText() { return this; }

bool ORBarcodeData::isBarcode() { return TRUE; }
ORBarcodeData * ORBarcodeData::toBarcode() { return this; }

bool ORImageData::isImage() { return TRUE; }
ORImageData * ORImageData::toImage() { return this; }

bool ORGraphData::isGraph() { return TRUE; }
ORGraphData * ORGraphData::toGraph() { return this; }

bool ORCrossTabData::isCrossTab() { return TRUE; }
ORCrossTabData * ORCrossTabData::toCrossTab() { return this; }

ORDetailGroupSectionData::ORDetailGroupSectionData()
{
    name = QString::null;
    column = QString::null;
    pagebreak = BreakNone;
    _subtotCheckPoints.clear();
    head = 0;
    foot = 0;
}

ORDetailGroupSectionData::~ORDetailGroupSectionData() {
    if (head != 0)
        delete head;
    if (foot != 0)
        delete foot;
}

ORDetailSectionData::ORDetailSectionData()
{
    name = QString::null;
    pagebreak = BreakNone;
    detail = 0;
}

ORDetailSectionData::~ORDetailSectionData() {
	qDeleteAll(groupList);
}

ORReportData::ORReportData()
{
    title = QString::null;
    name = QString::null;

    //queries = QuerySourceList();

    pghead_first = pghead_odd = pghead_even = pghead_last = pghead_any = NULL;
    pgfoot_first = pgfoot_odd = pgfoot_even = pgfoot_last = pgfoot_any = NULL;
    rpthead = rptfoot = NULL;
}

ORReportData::~ORReportData() {
    qDeleteAll(sections);
    if (pghead_first)
        delete pghead_first;
    if (pghead_odd)
        delete pghead_odd;
    if (pghead_even)
        delete pghead_even;
    if (pghead_last)
        delete pghead_last;
    if (pghead_any)
        delete pghead_any;
    if (pgfoot_first)
        delete pgfoot_first;
    if (pgfoot_odd)
        delete pgfoot_odd;
    if (pgfoot_even)
        delete pgfoot_even;
    if (pgfoot_last)
        delete pgfoot_last;
    if (pgfoot_any)
        delete pgfoot_any;
    if (rpthead)
        delete rpthead;
    if (rptfoot)
        delete rptfoot;
}

ORWatermarkData::ORWatermarkData()
{
    opacity = 25;
    useDefaultFont = true;
    font = QFont("Arial");
    staticText = true;
    text = QString::null;
    valid = false;
}

ORBackgroundData::ORBackgroundData()
{
    enabled = false;
    staticImage = true;
    image = QString::null;
    opacity = 25;
    mode = "clip";
    align = Qt::AlignLeft | Qt::AlignTop;
}

//
// functions
//

bool parseReportRect(const QDomElement & elemSource, ORRectData & rectTarget)
{
  QDomNodeList params = elemSource.childNodes();
  int          coorCounter = 0;

  QPen border = rectTarget.border();

  for ( int paramCounter = 0; paramCounter < params.count(); paramCounter++ )
  {
    QDomElement elemParam = params.item(paramCounter).toElement();

    if (elemParam.tagName() == "x")
    {
      rectTarget.x = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "y")
    {
      rectTarget.y = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "width")
    {
      rectTarget.width = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "height")
    {
      rectTarget.height = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "weight")
      border.setWidth(elemParam.text().toInt());
    else if (elemParam.tagName() == "color")
    {
      QColor color = parseColor(elemParam);
      QPen pen = rectTarget.pen();
      pen.setColor(color);
      rectTarget.setPen(pen);
    }
    else if (elemParam.tagName() == "bgcolor")
    {
      QColor color = parseColor(elemParam);
      QBrush brush = rectTarget.brush();
      brush.setColor(color);
      brush.setStyle(Qt::SolidPattern);
      rectTarget.setBrush(brush);
    }
    else if (elemParam.tagName() == "bordercolor")
    {
      QColor color = parseColor(elemParam);
      border.setColor(color);
    }
    else if (elemParam.tagName() == "borderwidth")
    {
      int width = elemParam.text().toInt();
      border.setWidth(width);
    }
    else if (elemParam.tagName() == "borderstyle")
    {
      Qt::PenStyle style = static_cast<Qt::PenStyle>(elemParam.text().toInt());
      border.setStyle(style);
    }
    else if (elemParam.tagName() == "rotation")
    {
      rectTarget.setRotation(elemParam.text().toFloat());
    }
    else
      qDebug("Tag not Parsed at <line>:%s\n", elemParam.tagName().toLatin1().data());
  }

  rectTarget.setBorder(border);

  if (coorCounter == 4)
    return TRUE;
  return FALSE;
}

bool parseReportRect(const QDomElement & elemSource, QRect & rectTarget, ORObject &o)
{
  ORRectData rData;
  bool res = parseReportRect(elemSource, rData);
  if(res)
  {
    rectTarget = QRect (rData.x, rData.y, rData.width, rData.height);
	o.setPen(rData.pen());
	o.setBrush(rData.brush());
	o.setRotation(rData.rotation());
    o.setBorder(rData.border());
  }
  return res;
}

bool parseReportRect(const QDomElement & elemSource, QRect & rectTarget)
{
  ORObject o;
  return parseReportRect(elemSource, rectTarget, o);
}


QColor parseColor(const QDomNode &n)
{
    QColor res = Qt::black;

    QDomNodeList qnl = n.childNodes();
    for(int qi = 0; qi < qnl.count(); qi++) {
        QDomNode qit = qnl.item(qi);
        if(qit.nodeName() == "red")
            res.setRed(qit.firstChild().nodeValue().toInt());
        else if(qit.nodeName() == "green")
            res.setGreen(qit.firstChild().nodeValue().toInt());
        else if(qit.nodeName() == "blue")
            res.setBlue(qit.firstChild().nodeValue().toInt());
    }

    return res;
}

bool parseReportFont(const QDomElement & elemSource, QFont & fontTarget)
{
  if (elemSource.tagName() == "font")
  {
    QDomNode  nodeCursor = elemSource.firstChild();

    while (!nodeCursor.isNull())
    {
      if (nodeCursor.isElement())
      {
        QDomElement elemThis = nodeCursor.toElement();
        int intTemp;
        bool valid;

        if (elemThis.tagName() == "face")
          fontTarget.setFamily(elemThis.text());
        else if (elemThis.tagName() == "size")
        {
          intTemp = elemThis.text().toInt(&valid);
          if (valid)
            fontTarget.setPointSize(intTemp);
          else
            qDebug("Text not Parsed at <font>:%s\n", elemThis.text().toLatin1().data());
        }
        else if (elemThis.tagName() == "weight")
        {
          if (elemThis.text() == "normal")
            fontTarget.setWeight(50);
          else if (elemThis.text() == "bold")
            fontTarget.setWeight(75);
          else
          {
            // This is where we want to convert the string to an int value
            // that should be between 1 and 100
            intTemp = elemThis.text().toInt(&valid);
            if(valid && intTemp >= 1 && intTemp <= 100)
              fontTarget.setWeight(intTemp);
            else
              qDebug("Text not Parsed at <font>:%s\n", elemThis.text().toLatin1().data());
          }
        }
		else if (elemThis.tagName() == "italic")
		{
			fontTarget.setItalic(TRUE);
		}
        else
        {
          // we have encountered a tag that we don't understand.
          // for now we will just inform a debugger about it
          qDebug("Tag not Parsed at <font>:%s\n", elemThis.tagName().toLatin1().data());
        } 
      }
      nodeCursor = nodeCursor.nextSibling();
    }
    return TRUE;
  }
  return FALSE;
}

bool parseReportData(const QDomElement & elemSource, ORDataData & dataTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_query = FALSE;
  bool valid_column = FALSE;

  for( int paramCounter = 0; paramCounter < params.count(); paramCounter++ )
  {
    QDomElement elemParam = params.item(paramCounter).toElement();
    if (elemParam.tagName() == "query")
    {
      dataTarget.query = elemParam.text();
      valid_query = TRUE;
    }
    else if(elemParam.tagName() == "column")
    {
      dataTarget.column = elemParam.text();
      valid_column = TRUE;
    }
    else
      qDebug("Tag not Parsed at <data>:%s\n", elemParam.tagName().toLatin1().data());
  }
  if(valid_query && valid_column)
    return TRUE;

  return FALSE;
}

bool parseReportKey(const QDomElement & elemSource, ORKeyData & dataTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_query = FALSE;
  bool valid_column = FALSE;

  for( int paramCounter = 0; paramCounter < params.count(); paramCounter++ )
  {
    QDomElement elemParam = params.item(paramCounter).toElement();
    if (elemParam.tagName() == "query")
    {
      dataTarget.query = elemParam.text();
      valid_query = TRUE;
    }
    else if(elemParam.tagName() == "column")
    {
      dataTarget.column = elemParam.text();
      valid_column = TRUE;
    }
    else
      qDebug("Tag not Parsed at <key>:%s\n", elemParam.tagName().toLatin1().data());
  }
  if(valid_query)
    return TRUE;

  return FALSE;
}

bool parseReportLine(const QDomElement & elemSource, ORLineData & lineTarget)
{
  QDomNodeList params = elemSource.childNodes();
  int          coorCounter = 0;
  QPen pen;

  for ( int paramCounter = 0; paramCounter < params.count(); paramCounter++ )
  {
    QDomElement elemParam = params.item(paramCounter).toElement();

    if (elemParam.tagName() == "xstart")
    {
      lineTarget.xStart = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "ystart")
    {
      lineTarget.yStart = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "xend")
    {
      lineTarget.xEnd = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "yend")
    {
      lineTarget.yEnd = (int)elemParam.text().toDouble();
      coorCounter++;
    }
    else if (elemParam.tagName() == "weight")
      pen.setWidth(elemParam.text().toInt());
    else if (elemParam.tagName() == "style")
      pen.setStyle(static_cast<Qt::PenStyle>(elemParam.text().toInt()));
    else if (elemParam.tagName() == "color")
      pen.setColor(parseColor(elemParam));
    else
      qDebug("Tag not Parsed at <line>:%s\n", elemParam.tagName().toLatin1().data());
  }

  lineTarget.setPen(pen);

  if (coorCounter == 4)
    return TRUE;

  return FALSE;
}

bool parseReportLabel(const QDomElement & elemSource, ORLabelData & labelTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_rect = FALSE;
  bool valid_string = FALSE;

  labelTarget.align = 0;

  for (int paramCounter = 0; paramCounter < params.count(); paramCounter++)
  {
    QDomElement elemParam = params.item(paramCounter).toElement();

    if (elemParam.tagName() == "rect")
		valid_rect = parseReportRect(elemParam, labelTarget.rect, labelTarget);
    else if (elemParam.tagName() == "font")
      parseReportFont(elemParam, labelTarget.font);
    else if (elemParam.tagName() == "string")
    {
      labelTarget.string = elemParam.text();
      valid_string = TRUE;
    }
    else if (elemParam.tagName() == "left")
      labelTarget.align |= Qt::AlignLeft;
    else if (elemParam.tagName() == "right")
      labelTarget.align |= Qt::AlignRight;
    else if (elemParam.tagName() == "vcenter")
      labelTarget.align |= Qt::AlignVCenter;
    else if (elemParam.tagName() == "hcenter")
      labelTarget.align |= Qt::AlignHCenter;
    else if (elemParam.tagName() == "top")
      labelTarget.align |= Qt::AlignTop;
    else if (elemParam.tagName() == "bottom")
      labelTarget.align |= Qt::AlignBottom;
    else
     qDebug("Tag not Parsed at <label>:%s\n", elemParam.tagName().toLatin1().data());
  }
  if(valid_rect && valid_string)
    return TRUE;
  return FALSE;
}

bool parseReportField(const QDomElement & elemSource, ORFieldData & fieldTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_rect = FALSE;
  bool valid_data = FALSE;

  fieldTarget.align = 0;
  fieldTarget.trackTotal = FALSE;
  fieldTarget.sub_total = FALSE;
  fieldTarget.builtinFormat = FALSE;
  fieldTarget.format = QString::null;
  fieldTarget.lines = 1;
  fieldTarget.columns = 1;
  fieldTarget.xSpacing = 0;
  fieldTarget.ySpacing = 0;
  fieldTarget.triggerPageBreak = false;
  fieldTarget.leftToRight = false;

  for (int paramCounter = 0; paramCounter < params.count(); paramCounter++)
  {
    QDomElement elemParam = params.item(paramCounter).toElement();

    if (elemParam.tagName() == "rect")
      valid_rect = parseReportRect(elemParam, fieldTarget.rect, fieldTarget);
    else if (elemParam.tagName() == "font")
      parseReportFont(elemParam, fieldTarget.font);
    else if (elemParam.tagName() == "left")
      fieldTarget.align |= Qt::AlignLeft;
    else if (elemParam.tagName() == "right")
      fieldTarget.align |= Qt::AlignRight;
    else if (elemParam.tagName() == "vcenter")
      fieldTarget.align |= Qt::AlignVCenter;
    else if (elemParam.tagName() == "hcenter")
      fieldTarget.align |= Qt::AlignHCenter;
    else if (elemParam.tagName() == "top")
      fieldTarget.align |= Qt::AlignTop;
    else if (elemParam.tagName() == "bottom")
      fieldTarget.align |= Qt::AlignBottom;
	else if (elemParam.tagName() == "wordwrap")
      fieldTarget.align |= Qt::TextWordWrap;
    else if (elemParam.tagName() == "lines")
      fieldTarget.lines = elemParam.text().toInt();
    else if (elemParam.tagName() == "columns")
      fieldTarget.columns = elemParam.text().toInt();
    else if (elemParam.tagName() == "xSpacing")
      fieldTarget.xSpacing = elemParam.text().toDouble();
    else if (elemParam.tagName() == "ySpacing")
      fieldTarget.ySpacing = elemParam.text().toDouble();
    else if (elemParam.tagName() == "triggerPageBreak")
      fieldTarget.triggerPageBreak = true;
    else if (elemParam.tagName() == "leftToRight")
      fieldTarget.leftToRight = true;
    else if (elemParam.tagName() == "data")
      valid_data = parseReportData(elemParam, fieldTarget.data);
	else if (elemParam.tagName() == "format")
	{
		fieldTarget.builtinFormat = (elemParam.attribute("builtin")=="true"?TRUE:FALSE);
		fieldTarget.format = elemParam.text();
	}
    else if (elemParam.tagName() == "tracktotal")
    {
      // NB for compatibility with reports V <= 3.0 format info is also read from the total tag
      if(!fieldTarget.builtinFormat)
        fieldTarget.builtinFormat = (elemParam.attribute("builtin")=="true"?TRUE:FALSE);
      fieldTarget.sub_total = (elemParam.attribute("subtotal")=="true"?TRUE:FALSE);
	  if(!elemParam.text().isEmpty()) 
		fieldTarget.format = elemParam.text();
      if(!fieldTarget.format.isEmpty())
        fieldTarget.trackTotal = TRUE;
    }
    else
     qDebug("Tag not Parsed at <field>:%s\n", elemParam.tagName().toLatin1().data());
  }
  if(valid_rect && valid_data)
    return TRUE;
  return FALSE;
}

bool parseReportText(const QDomElement & elemSource, ORTextData & textTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_rect = FALSE;
  bool valid_data = FALSE;

  textTarget.align = 0;
  textTarget.bottompad = 0;

  for (int paramCounter = 0; paramCounter < params.count(); paramCounter++)
  {
    QDomElement elemParam = params.item(paramCounter).toElement();

    if (elemParam.tagName() == "rect")
      valid_rect = parseReportRect(elemParam, textTarget.rect, textTarget);
    else if (elemParam.tagName() == "font")
      parseReportFont(elemParam, textTarget.font);
    else if (elemParam.tagName() == "left")
      textTarget.align |= Qt::AlignLeft;
    else if (elemParam.tagName() == "right")
      textTarget.align |= Qt::AlignRight;
    else if (elemParam.tagName() == "vcenter")
      textTarget.align |= Qt::AlignVCenter;
    else if (elemParam.tagName() == "hcenter")
      textTarget.align |= Qt::AlignHCenter;
    else if (elemParam.tagName() == "top")
      textTarget.align |= Qt::AlignTop;
    else if (elemParam.tagName() == "bottom")
      textTarget.align |= Qt::AlignBottom;
    else if (elemParam.tagName() == "data")
      valid_data = parseReportData(elemParam, textTarget.data);
    else if (elemParam.tagName() == "bottompad")
      textTarget.bottompad = elemParam.text().toInt();
    else
     qDebug("Tag not Parsed at <text>:%s\n", elemParam.tagName().toLatin1().data());
  }
  if(valid_rect && valid_data)
    return TRUE;
  return FALSE;
}

bool parseReportBarcode(const QDomElement & elemSource, ORBarcodeData & barcodeTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_rect = FALSE;
  bool valid_data = FALSE;

  barcodeTarget.format = "3of9";
  barcodeTarget.align = 0; // left alignment [default]
  barcodeTarget.narrowBarWidth = ORBarcodeData::defaultNarrowBarWidth();

  for(int paramCounter = 0; paramCounter < params.count(); paramCounter++)
  {
    QDomElement elemParam = params.item(paramCounter).toElement();
    if(elemParam.tagName() == "rect")
      valid_rect = parseReportRect(elemParam, barcodeTarget.rect, barcodeTarget);
    else if(elemParam.tagName() == "data")
      valid_data = parseReportData(elemParam, barcodeTarget.data);
    else if(elemParam.tagName() == "maxlength")
      barcodeTarget.maxlength = elemParam.text().toInt();
    else if(elemParam.tagName() == "format")
      barcodeTarget.format = elemParam.text();
    else if(elemParam.tagName() == "left")
      barcodeTarget.align = 0;
    else if(elemParam.tagName() == "center")
      barcodeTarget.align = 1;
    else if(elemParam.tagName() == "right")
      barcodeTarget.align = 2;
    else if(elemParam.tagName() == "narrowBarWidth")
        barcodeTarget.narrowBarWidth = elemParam.text().toDouble();
    else
      qDebug("Tag not parsed at <barcode>:%s", elemParam.tagName().toLatin1().data());
  }

  if(valid_rect && valid_data)
    return TRUE;
  return FALSE;
}

bool parseReportImage(const QDomElement & elemSource, ORImageData & imageTarget)
{
  QDomNodeList params = elemSource.childNodes();
  bool valid_rect = FALSE;
  bool valid_data = FALSE;
  bool valid_inline = FALSE;

  imageTarget.mode = "clip";

  for(int paramCounter = 0; paramCounter < params.count(); paramCounter++)
  {
    QDomElement elemParam = params.item(paramCounter).toElement();
    if(elemParam.tagName() == "rect")
      valid_rect = parseReportRect(elemParam, imageTarget.rect, imageTarget);
    else if(elemParam.tagName() == "data")
      valid_data = parseReportData(elemParam, imageTarget.data);
    else if(elemParam.tagName() == "mode")
      imageTarget.mode = elemParam.text();
    else if(elemParam.tagName() == "map")
    {
      // ok we have an inline image here
      imageTarget.format = elemParam.attribute("format");
      imageTarget.inline_data = elemParam.firstChild().nodeValue();
      valid_inline = TRUE;
    }
    else
      qDebug("Tag not parsed at <image>:%s", elemParam.tagName().toLatin1().data());
  }

  if(valid_rect && ( valid_data || valid_inline ) )
    return TRUE;
  return FALSE;
}

bool parseReportColorDefData(const QDomElement & elemSource, ORColorDefData & coldefTarget)
{
  if(elemSource.tagName() != "colordef")
    return false;

  coldefTarget.name = QString::null;
  coldefTarget.red = coldefTarget.green = coldefTarget.blue = 0;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "name")
      coldefTarget.name = elemThis.text();
    else if(elemThis.tagName() == "red")
      coldefTarget.red = elemThis.text().toInt();
    else if(elemThis.tagName() == "green")
      coldefTarget.green = elemThis.text().toInt();
    else if(elemThis.tagName() == "blue")
      coldefTarget.blue = elemThis.text().toInt();
    else
      qDebug("While parsing colordef encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }
  if(coldefTarget.name.length() > 0)
    return TRUE;
  return FALSE;
}

bool parseReportTitleData(const QDomElement & elemSource, ORTitleData & titleTarget)
{
  if(elemSource.tagName() != "title")
    return FALSE;

  titleTarget.string = QString::null;
  titleTarget.font_defined = FALSE;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "string")
      titleTarget.string = elemThis.text();
    else if(elemThis.tagName() == "font")
      titleTarget.font_defined = parseReportFont(elemThis, titleTarget.font);
    else
      qDebug("While parsing title encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  return TRUE;
}

bool parseReportStyleData(const QDomElement & elemSource, ORStyleData & styleTarget)
{
  if(elemSource.tagName() != "style")
    return FALSE;

  styleTarget.bar = styleTarget.line = styleTarget.point = FALSE;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "bar")
      styleTarget.bar = TRUE;
    else if(elemThis.tagName() == "line")
      styleTarget.line = TRUE;
    else if(elemThis.tagName() == "point")
      styleTarget.point = TRUE;
    else
      qDebug("While parsing title encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  if(styleTarget.bar == FALSE && styleTarget.line == FALSE && styleTarget.point == FALSE)
    return FALSE;

  return TRUE;
}

bool parseReportDataAxisData(const QDomElement & elemSource, ORDataAxisData & axisTarget)
{
  if(elemSource.tagName() != "dataaxis")
    return FALSE;

  axisTarget.title.string = QString::null;
  axisTarget.title.font_defined = FALSE;
  axisTarget.column = QString::null;
  axisTarget.font_defined = FALSE;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "title")
      parseReportTitleData(elemThis, axisTarget.title);
    else if(elemThis.tagName() == "column")
      axisTarget.column = elemThis.text();
    else if(elemThis.tagName() == "font")
      axisTarget.font_defined = parseReportFont(elemThis, axisTarget.font);
    else
      qDebug("While parsing dataaxis encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  return TRUE;
}

bool parseReportValueAxisData(const QDomElement & elemSource, ORValueAxisData & axisTarget)
{
  if(elemSource.tagName() != "valueaxis")
    return FALSE;

  double ival = 0.0;
  bool valid = FALSE;

  axisTarget.title.string = QString::null;
  axisTarget.title.font_defined = FALSE;
  axisTarget.min = 0.0;
  axisTarget.max = 100.0;
  axisTarget.autominmax = TRUE;
  axisTarget.font_defined = FALSE;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "title")
      parseReportTitleData(elemThis, axisTarget.title);
    else if(elemThis.tagName() == "min")
    {
      ival = elemThis.text().toDouble(&valid);
      if(valid)
        axisTarget.min = ival;
    }
    else if(elemThis.tagName() == "max")
    {
      ival = elemThis.text().toDouble(&valid);
      if(valid)
        axisTarget.max = ival;
    }
    else if(elemThis.tagName() == "autominmax")
    {
      QString amn = elemThis.text().toLower();
      if(amn == "t" || amn == "true" || amn == "")
        axisTarget.autominmax = TRUE;
      else
        axisTarget.autominmax = FALSE;
    }
    else if(elemThis.tagName() == "font")
      axisTarget.font_defined = parseReportFont(elemThis, axisTarget.font);
    else
      qDebug("While parsing valueaxis encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  return TRUE;
}

bool parseReportSeriesData(const QDomElement & elemSource, ORSeriesData & seriesTarget)
{
  if(elemSource.tagName() != "series")
    return FALSE;

  seriesTarget.name = QString::null;
  seriesTarget.color = QString::null;
  seriesTarget.column = QString::null;
  seriesTarget.style.bar = TRUE;
  seriesTarget.style.line = FALSE;
  seriesTarget.style.point = FALSE;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "name")
      seriesTarget.name = elemThis.text();
    else if(elemThis.tagName() == "color")
      seriesTarget.color = elemThis.text();
    else if(elemThis.tagName() == "column")
      seriesTarget.column = elemThis.text();
    else if(elemThis.tagName() == "style")
    {
      if(!parseReportStyleData(elemThis, seriesTarget.style))
      {
          seriesTarget.style.bar = TRUE;
          seriesTarget.style.line = FALSE;
          seriesTarget.style.point = FALSE;
      }
    }
    else
      qDebug("While parsing series encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  
  if(seriesTarget.name.length() > 0 &&
     seriesTarget.color.length() > 0 &&
     seriesTarget.column.length() > 0)
    return TRUE;
  return FALSE;
}

bool parseReportGraphData(const QDomElement & elemSource, ORGraphData & graphTarget)
{
  if(elemSource.tagName() != "graph")
    return FALSE;

  bool have_data = FALSE;
  bool have_rect = FALSE;
  bool have_series = FALSE;

  graphTarget.title.string = QString::null;
  graphTarget.dataaxis.title.string = QString::null;
  graphTarget.dataaxis.title.font_defined = FALSE;
  graphTarget.dataaxis.column = QString::null;
  graphTarget.dataaxis.font_defined = FALSE;
  graphTarget.valueaxis.title.string = QString::null;
  graphTarget.valueaxis.min = 0;
  graphTarget.valueaxis.max = 100;
  graphTarget.valueaxis.autominmax = TRUE;
  graphTarget.valueaxis.font_defined = FALSE;

  //graphTarget.series.setAutoDelete(TRUE);

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "data")
      have_data = parseReportData(elemThis, graphTarget.data);
    else if(elemThis.tagName() == "font")
      parseReportFont(elemThis, graphTarget.font);
    else if(elemThis.tagName() == "rect")
      have_rect = parseReportRect(elemThis, graphTarget.rect);
    else if(elemThis.tagName() == "title")
      parseReportTitleData(elemThis, graphTarget.title);
    else if(elemThis.tagName() == "dataaxis")
    {
      if(!parseReportDataAxisData(elemThis, graphTarget.dataaxis))
      {
        graphTarget.dataaxis.title.string = QString::null;
        graphTarget.dataaxis.title.font_defined = FALSE;
        graphTarget.dataaxis.column = QString::null;
        graphTarget.dataaxis.font_defined = FALSE;
      }
    }
    else if(elemThis.tagName() == "valueaxis")
    {
      if(!parseReportValueAxisData(elemThis, graphTarget.valueaxis))
      {
        graphTarget.valueaxis.title.string = QString::null;
        graphTarget.valueaxis.min = 0;
        graphTarget.valueaxis.max = 100;
        graphTarget.valueaxis.autominmax = TRUE;
        graphTarget.valueaxis.font_defined = FALSE;
      }
    }
    else if(elemThis.tagName() == "series")
    {
      ORSeriesData * orsd = new ORSeriesData();
      if(parseReportSeriesData(elemThis, *orsd))
      {
        graphTarget.series.append(orsd);
        have_series = TRUE;
      }
      else
        delete orsd;
      orsd = 0;
    }
    else
      qDebug("While parsing graph encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  if(have_data && have_rect && have_series)
    return TRUE;
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
bool parseReportCrossTabElementData(const QString& elementName,
                                    const QDomElement& elemSource,
                                    ORCrossTabQueryData& queryData)
{
  if(elemSource.tagName() != elementName)
    return FALSE;

  queryData.m_query  = QString::null;
  queryData.m_hAlign = QString::null;
  queryData.m_vAlign = QString::null;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "queryColumn")
      queryData.m_query = elemThis.text();
    else if(elemThis.tagName() == "HAlign")
      queryData.m_hAlign = elemThis.text();
    else if(elemThis.tagName() == "VAlign")
      queryData.m_vAlign = elemThis.text();
    else
      qDebug("While parsing CrossTab Element data encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
bool parseReportTable(const QDomElement& elemSource,
                      ORCrossTabTablePropertiesData& queryData)
{
  if(elemSource.tagName() != "table")
    return FALSE;

  queryData.m_cellLeftMargin = 0.00;
  queryData.m_cellRightMargin = 0.00;
  queryData.m_cellTopMargin = 0.00;
  queryData.m_cellBottomMargin = 0.00;
  queryData.m_showColumnHeaderOnEachPart = true;
  queryData.m_showRowHeaderOnEachPart    = true;
  queryData.m_wrapPolicyColumnsFirst     = false;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "wrappolicy")
    {
      if ("columns" == elemThis.text())
      {
        queryData.m_wrapPolicyColumnsFirst = true;
      }
      else
      {
        queryData.m_wrapPolicyColumnsFirst = false;
      }
    }
    else if(elemThis.tagName() == "showcolumnheaderagain")
    {
      if ("yes" == elemThis.text())
      {
        queryData.m_showColumnHeaderOnEachPart = true;
      }
      else
      {
        queryData.m_showColumnHeaderOnEachPart = false;
      }
    }
    else if(elemThis.tagName() == "showrowheaderagain")
    {
      if ("yes" == elemThis.text())
      {
        queryData.m_showRowHeaderOnEachPart = true;
      }
      else
      {
        queryData.m_showRowHeaderOnEachPart = false;
      }
    }
    else if(elemThis.tagName() == "CellMargins")
    {
      QDomNodeList rnl = elemThis.childNodes();
      double l = 0.0;
      double r = 0.0;
      double t = 0.0;
      double b = 0.0;
      for(int ri = 0; ri < rnl.count(); ri++)
      {
        QDomElement childElement = rnl.item(ri).toElement();
        QString n = childElement.nodeName();
        if(n == "Left")
        {
            l = childElement.firstChild().nodeValue().toDouble();
        }
        else if(n == "Right")
        {
            r = childElement.firstChild().nodeValue().toDouble();
        }
        else if(n == "Top")
        {
            t = childElement.firstChild().nodeValue().toDouble();
        }
        else if(n == "Bottom")
        {
            b = childElement.firstChild().nodeValue().toDouble();
        } else {
            qDebug("While parsing cell margins encountered unknown element: %s", n.toLatin1().data());
        }
      }
      queryData.m_cellLeftMargin = l;
      queryData.m_cellRightMargin = r;
      queryData.m_cellTopMargin = t;
      queryData.m_cellBottomMargin = b;
    }
    else
    {
      qDebug("While parsing CrossTab table encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
    }
  }

  return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
bool parseReportCrossTabData(const QDomElement & elemSource, ORCrossTabData & crossTabTarget)
{
  if(elemSource.tagName() != "crosstab")
    return false;

  bool have_rect  = false;
  bool have_font  = false;
  bool have_table = false;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "data")
    {
      (void)parseReportData(elemThis, crossTabTarget.data);
      // Not using column property of data section. Therefore the function
      // will return false.
    }
    else if(elemThis.tagName() == "font")
    {
      have_font = parseReportFont(elemThis, crossTabTarget.font);
    }
    else if(elemThis.tagName() == "rect")
    {
      have_rect = parseReportRect(elemThis, crossTabTarget.rect, crossTabTarget);
    }
    else if(elemThis.tagName() == "table")
    {
      have_table = parseReportTable(elemThis, crossTabTarget.m_tableProperties);
    }
    else if(elemThis.tagName() == "column")
    {
      if(!parseReportCrossTabElementData("column", elemThis, crossTabTarget.m_column))
      {
        crossTabTarget.m_column.m_query  = QString::null;
        crossTabTarget.m_column.m_hAlign = QString::null;
        crossTabTarget.m_column.m_vAlign = QString::null;
      }
    }
    else if(elemThis.tagName() == "row")
    {
      if(!parseReportCrossTabElementData("row", elemThis, crossTabTarget.m_row))
      {
        crossTabTarget.m_row.m_query  = QString::null;
        crossTabTarget.m_row.m_hAlign = QString::null;
        crossTabTarget.m_row.m_vAlign = QString::null;
      }
    }
    else if(elemThis.tagName() == "value")
    {
      if(!parseReportCrossTabElementData("value", elemThis, crossTabTarget.m_value))
      {
        crossTabTarget.m_value.m_query  = QString::null;
        crossTabTarget.m_value.m_hAlign = QString::null;
        crossTabTarget.m_value.m_vAlign = QString::null;
      }
    }
    else
      qDebug("While parsing graph encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  return (have_rect && have_font);
}

bool parseReportBackground(const QDomElement & elemSource, ORBackgroundData & bgTarget)
{
  if(elemSource.tagName() != "background")
    return FALSE;

  bgTarget.enabled = false;
  bgTarget.staticImage = true;
  bgTarget.image = QString::null;
  bgTarget.data.query = QString::null;
  bgTarget.data.column = QString::null;
  bgTarget.opacity = 25;
  bgTarget.mode = "clip";
  bgTarget.rect = QRect();

  int halign = Qt::AlignLeft;
  int valign = Qt::AlignTop;
  bool valid_rect = true;

  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++)
  {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "image")
      bgTarget.image = elemThis.text();
    else if(elemThis.tagName() == "mode")
      bgTarget.mode = elemThis.text();
    else if(elemThis.tagName() == "data")
      bgTarget.staticImage = !parseReportData(elemThis, bgTarget.data);
    else if(elemThis.tagName() == "left")
      halign = Qt::AlignLeft;
    else if(elemThis.tagName() == "hcenter")
      halign = Qt::AlignHCenter;
    else if(elemThis.tagName() == "right")
      halign = Qt::AlignRight;
    else if(elemThis.tagName() == "top")
      valign = Qt::AlignTop;
    else if(elemThis.tagName() == "vcenter")
      valign = Qt::AlignVCenter;
    else if(elemThis.tagName() == "bottom")
      valign = Qt::AlignBottom;
    else if(elemThis.tagName() == "rect")
      valid_rect = parseReportRect(elemThis, bgTarget.rect);
    else if(elemThis.tagName() == "opacity")
    {
      bool valid = false;
      int i = elemThis.text().toInt(&valid);
      if(valid) {
        if(i < 0)
          i = 0;
        if(i > 255)
          i = 255;
        bgTarget.opacity = i;
      }
    }
    else
      qDebug("While parsing background encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  bgTarget.align = halign | valign;
  bgTarget.enabled = (valid_rect && ((bgTarget.staticImage && !bgTarget.image.isEmpty())
                       || (!bgTarget.staticImage && !bgTarget.data.query.isEmpty()
                                                 && !bgTarget.data.column.isEmpty())));
  return bgTarget.enabled;
}

bool parseReportWatermark(const QDomElement & elemSource, ORWatermarkData & wmTarget)
{
  if(elemSource.tagName() != "watermark")
    return FALSE;

  wmTarget.text = QString::null;
  wmTarget.opacity = 25;
  wmTarget.staticText = true;
  wmTarget.useDefaultFont = true;
  wmTarget.valid = false;
  
  QDomNodeList nlist = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < nlist.count(); nodeCounter++) {
    QDomElement elemThis = nlist.item(nodeCounter).toElement();
    if(elemThis.tagName() == "text")
      wmTarget.text = elemThis.text();
    else if(elemThis.tagName() == "data")
      wmTarget.staticText = !parseReportData(elemThis, wmTarget.data);
    else if(elemThis.tagName() == "font")
      wmTarget.useDefaultFont = !parseReportFont(elemThis, wmTarget.font);
    else if(elemThis.tagName() == "opacity")
    {
      bool valid = false;
      int i = elemThis.text().toInt(&valid);
      if(valid) {
        if(i < 0)
          i = 0;
        if(i > 255)
          i = 255;
        wmTarget.opacity = i;
      }
    }
    else
      qDebug("While parsing watermark encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }

  wmTarget.valid = ((wmTarget.staticText && !wmTarget.text.isEmpty())
                     || (!wmTarget.staticText && !wmTarget.data.query.isEmpty()
                                              && !wmTarget.data.column.isEmpty()));

  return wmTarget.valid;
}

bool parseReportSection(const QDomElement & elemSource, ORSectionData & sectionTarget)
{
  sectionTarget.name = elemSource.tagName();

  if(sectionTarget.name != "rpthead" && sectionTarget.name != "rptfoot" &&
     sectionTarget.name != "pghead" && sectionTarget.name != "pgfoot" &&
     sectionTarget.name != "grouphead" && sectionTarget.name != "groupfoot" &&
     sectionTarget.name != "head" && sectionTarget.name != "foot" &&
     sectionTarget.name != "detail" )
    return false;

  sectionTarget.extra = QString::null;
  sectionTarget.height = 0.0;

  QDomNodeList section = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < section.count(); nodeCounter++)
  {
    QDomElement elemThis = section.item(nodeCounter).toElement();
    if(elemThis.tagName() == "height")
    {
      bool valid;
      qreal height = elemThis.text().toDouble(&valid);
      if(valid)
        sectionTarget.height = height;
    }
    else if(elemThis.tagName() == "firstpage") {
      if(sectionTarget.name == "pghead" || sectionTarget.name == "pgfoot")
        sectionTarget.extra = elemThis.tagName();
    }
    else if(elemThis.tagName() == "odd")
    {
      if(sectionTarget.name == "pghead" || sectionTarget.name == "pgfoot")
        sectionTarget.extra = elemThis.tagName();
    }
    else if(elemThis.tagName() == "even")
    {
      if(sectionTarget.name == "pghead" || sectionTarget.name == "pgfoot")
        sectionTarget.extra = elemThis.tagName();
    }
    else if(elemThis.tagName() == "lastpage")
    {
      if(sectionTarget.name == "pghead" || sectionTarget.name == "pgfoot")
        sectionTarget.extra = elemThis.tagName();
    }
    else if(elemThis.tagName() == "label")
    {
      ORLabelData * label = new ORLabelData();
      if(parseReportLabel(elemThis, *label) == TRUE)
        sectionTarget.objects.append(label);
      else
        delete label;
    }
    else if(elemThis.tagName() == "field")
    {
      ORFieldData * field = new ORFieldData();
      if(parseReportField(elemThis, *field) == TRUE)
      {
        sectionTarget.objects.append(field);
        if(field->trackTotal)
          sectionTarget.trackTotal.append(field->data);
      }
      else
        delete field;
    }
    else if(elemThis.tagName() == "text")
    {
      ORTextData * text = new ORTextData();
      if(parseReportText(elemThis, *text) == TRUE)
        sectionTarget.objects.append(text);
      else
        delete text;
    }
    else if(elemThis.tagName() == "line")
    {
      ORLineData * line = new ORLineData();
      if(parseReportLine(elemThis, *line) == TRUE)
        sectionTarget.objects.append(line);
      else
        delete line;
    }
    else if(elemThis.tagName() == "rect")
    {
        ORRectData * rect = new ORRectData();
        if(parseReportRect(elemThis, *rect) == TRUE)
        {
          // to maintain compatibility with older version that don't support borders,
          // for which rect border color is recorded in the "pen" element
          QPen borderPen = rect->border();
          borderPen.setColor(rect->pen().color());
          rect->setBorder(borderPen);

          sectionTarget.objects.prepend(rect);
        }
        else
            delete rect;
    }
    else if(elemThis.tagName() == "barcode")
    {
      ORBarcodeData * bc = new ORBarcodeData();
      if(parseReportBarcode(elemThis, *bc) == TRUE)
        sectionTarget.objects.append(bc);
      else
        delete bc;
    }
    else if(elemThis.tagName() == "image")
    {
      ORImageData * img = new ORImageData();
      if(parseReportImage(elemThis, *img) == TRUE)
        sectionTarget.objects.prepend(img);
      else
        delete img;
    }
    else if(elemThis.tagName() == "graph")
    {
      ORGraphData * graph = new ORGraphData();
      if(parseReportGraphData(elemThis, *graph) == TRUE)
        sectionTarget.objects.append(graph);
      else
        delete graph;
    }
    else if(elemThis.tagName() == "crosstab")
    {
      ORCrossTabData * crossTab = new ORCrossTabData();
      if(parseReportCrossTabData(elemThis, *crossTab) == TRUE)
        sectionTarget.objects.append(crossTab);
      else
        delete crossTab;
    }
    else if(elemThis.tagName() == "key")
    {
      // we can ignore this as it will be handled elsewhere
      // we just catch this so we don't get an error
    }
    else
      qDebug("While parsing section encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }
  return TRUE;
}

bool parseReportDetailSection(const QDomElement & elemSource, ORDetailSectionData & sectionTarget)
{
  if(elemSource.tagName() != "section")
    return FALSE;

  bool have_name = FALSE;
  bool have_detail = FALSE;
  bool have_key = FALSE;

  ORSectionData * old_head = 0;
  ORSectionData * old_foot = 0;

  QDomNodeList section = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < section.count(); nodeCounter++)
  {
    QDomElement elemThis = section.item(nodeCounter).toElement();
    if(elemThis.tagName() == "name")
    {
      sectionTarget.name = elemThis.text();
      have_name = TRUE;
    }
    else if(elemThis.tagName() == "pagebreak")
    {
      if(elemThis.attribute("when") == "at end")
        sectionTarget.pagebreak = ORDetailSectionData::BreakAtEnd;
    }
    else if(elemThis.tagName() == "grouphead")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        old_head = sd;
        sectionTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "groupfoot")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        old_foot = sd;
        sectionTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "group")
    {
      QDomNodeList nl = elemThis.childNodes();
      QDomNode node;
      ORDetailGroupSectionData * dgsd = new ORDetailGroupSectionData();
      for(int i = 0; i < nl.count(); i++)
      {
        node = nl.item(i);
        if(node.nodeName() == "name")
          dgsd->name = node.firstChild().nodeValue();
        else if(node.nodeName() == "column")
          dgsd->column = node.firstChild().nodeValue();
        else if(node.nodeName() == "pagebreak")
        {
          QDomElement elemThis = node.toElement();
          QString n = elemThis.attribute("when");
          if("after foot" == n)
            dgsd->pagebreak = ORDetailGroupSectionData::BreakAfterGroupFoot;
        }
        else if(node.nodeName() == "head")
        {
          ORSectionData * sd = new ORSectionData();
          if(parseReportSection(node.toElement(), *sd) == TRUE)
          {
            dgsd->head = sd;
            sectionTarget.trackTotal += sd->trackTotal;
            for(int it = 0; it < sd->trackTotal.count(); ++it)
              dgsd->_subtotCheckPoints[sd->trackTotal.at(it)] = 0.0;
          }
          else
            delete sd;
        }
        else if(node.nodeName() == "foot")
        {
          ORSectionData * sd = new ORSectionData();
          if(parseReportSection(node.toElement(), *sd) == TRUE)
          {
            dgsd->foot = sd;
            sectionTarget.trackTotal += sd->trackTotal;
            for(int it = 0; it < sd->trackTotal.count(); ++it)
              dgsd->_subtotCheckPoints[sd->trackTotal.at(it)] = 0.0;
          }
          else
            delete sd;
        }
        else
          qDebug("While parsing group section encountered an unknown element: %s", node.nodeName().toLatin1().data());
      }
      sectionTarget.groupList.append(dgsd);
    }
    else if(elemThis.tagName() == "detail")
    {
      // find and read in the key data of this element
      have_key = parseReportKey(elemThis.namedItem("key").toElement(), sectionTarget.key);

      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        sectionTarget.detail = sd;
        sectionTarget.trackTotal += sd->trackTotal;
        have_detail = TRUE;
      }
      else
        delete sd;
    }
    else
      qDebug("While parsing detail section encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
  }
  if(old_head || old_foot)
  {
    ORDetailGroupSectionData * gsec = new ORDetailGroupSectionData();
    gsec->name = sectionTarget.name;
    gsec->column = sectionTarget.key.column;
    gsec->head = old_head;
    gsec->foot = old_foot;
    sectionTarget.groupList.append(gsec);
  }
  return (have_name && have_detail && have_key);
}

bool parseReport(const QDomElement & elemSource, ORReportData & reportTarget, QSqlDatabase db)
{
  if(elemSource.tagName() != "report")
  {
    qDebug("QDomElement passed to parseReport() was not <report> tag");
    return FALSE;
  }

  double d = 0.0;
  bool valid = FALSE;

  QDomNodeList section = elemSource.childNodes();
  for(int nodeCounter = 0; nodeCounter < section.count(); nodeCounter++)
  {
    QDomElement elemThis = section.item(nodeCounter).toElement();
    if(elemThis.tagName() == "title")
      reportTarget.title = elemThis.text();
    else if(elemThis.tagName() == "name")
      reportTarget.name = elemThis.text();
    else if(elemThis.tagName() == "description")
      reportTarget.description = elemThis.text();
    else if(elemThis.tagName() == "parameter")
    {
      parseReportParameter(elemThis, reportTarget);
    }
    else if(elemThis.tagName() == "watermark")
      parseReportWatermark(elemThis, reportTarget.wmData);
    else if(elemThis.tagName() == "background")
      parseReportBackground(elemThis, reportTarget.bgData);
    else if(elemThis.tagName() == "size")
    {
      if(elemThis.firstChild().isText())
        reportTarget.page.setPageSize(elemThis.firstChild().nodeValue());
      else
      {
        //bad code! bad code!
        // this code doesn't check the elemts and assums they are what
        // they should be.
        QDomNode n1 = elemThis.firstChild();
        QDomNode n2 = n1.nextSibling();
        if(n1.nodeName() == "width")
        {
          reportTarget.page.setCustomWidth(n1.firstChild().nodeValue().toDouble() / 100.0);
          reportTarget.page.setCustomHeight(n2.firstChild().nodeValue().toDouble() / 100.0);
        }
        else
        {
          reportTarget.page.setCustomWidth(n2.firstChild().nodeValue().toDouble() / 100.0);
          reportTarget.page.setCustomHeight(n1.firstChild().nodeValue().toDouble() / 100.0);
        }
        reportTarget.page.setPageSize("Custom");
      }
    }
    else if(elemThis.tagName() == "labeltype")
      reportTarget.page.setLabelType(elemThis.firstChild().nodeValue());
    else if(elemThis.tagName() == "portrait")
      reportTarget.page.setPortrait(TRUE);
    else if(elemThis.tagName() == "landscape")
      reportTarget.page.setPortrait(FALSE);
    else if(elemThis.tagName() == "topmargin")
    {
      d = elemThis.text().toDouble(&valid);
      if(!valid || d < 0.0)
      {
        qDebug("Error converting topmargin value: %s",elemThis.text().toLatin1().data());
        d = 50.0;
      }
      reportTarget.page.setMarginTop((d / 100.0));
    }
    else if(elemThis.tagName() == "bottommargin")
    {
      d = elemThis.text().toDouble(&valid);
      if(!valid || d < 0.0)
      {
        qDebug("Error converting bottommargin value: %s",elemThis.text().toLatin1().data());
        d = 50.0;
      }
      reportTarget.page.setMarginBottom((d / 100.0));
    }
    else if(elemThis.tagName() == "leftmargin")
    {
      d = elemThis.text().toDouble(&valid);
      if(!valid || d < 0.0)
      {
        qDebug("Error converting leftmargin value: %s",elemThis.text().toLatin1().data());
        d = 50.0;
      }
      reportTarget.page.setMarginLeft(d/100.0);
    }
    else if(elemThis.tagName() == "rightmargin")
    {
      d = elemThis.text().toDouble(&valid);
      if(!valid || d < 0.0)
      {
        qDebug("Error converting rightmargin value: %s",elemThis.text().toLatin1().data());
        d = 50.0;
      }
      reportTarget.page.setMarginRight(d/100.0);
    }
    else if(elemThis.tagName() == "querysource")
    {
      // we need to read in the query sources
      QString qsname = elemThis.namedItem("name").toElement().text();
      QString qsquery = elemThis.namedItem("sql").toElement().text();
      bool qsloadfromdb = (elemThis.attribute("loadFromDb") == QString("true"));
      QString qsmgroup = elemThis.namedItem("mqlgroup").toElement().text();
      QString qsmname  = elemThis.namedItem("mqlname").toElement().text();
      reportTarget.queries.add(new QuerySource(qsname,qsquery, qsloadfromdb, qsmgroup, qsmname));
    }
    else if(elemThis.tagName() == "rpthead")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        reportTarget.rpthead = sd;
        reportTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "rptfoot")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        reportTarget.rptfoot = sd;
        reportTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "pghead")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE)
      {
        if(sd->extra == "firstpage")
          reportTarget.pghead_first = sd;
        else if(sd->extra == "odd")
          reportTarget.pghead_odd = sd;
        else if(sd->extra == "even")
          reportTarget.pghead_even = sd;
        else if(sd->extra == "lastpage")
          reportTarget.pghead_last = sd;
        else if(sd->extra == QString::null)
          reportTarget.pghead_any = sd;
        else
        {
          qDebug("don't know which page this page header is for: %s",sd->extra.toLatin1().data());
          delete sd;
        }
        reportTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "pgfoot")
    {
      ORSectionData * sd = new ORSectionData();
      if(parseReportSection(elemThis, *sd) == TRUE) {
        if(sd->extra == "firstpage")
          reportTarget.pgfoot_first = sd;
        else if(sd->extra == "odd")
          reportTarget.pgfoot_odd = sd;
        else if(sd->extra == "even")
          reportTarget.pgfoot_even = sd;
        else if(sd->extra == "lastpage")
          reportTarget.pgfoot_last = sd;
        else if(sd->extra == QString::null)
          reportTarget.pgfoot_any = sd;
        else
        {
          qDebug("don't know which page this page footer is for: %s",sd->extra.toLatin1().data());
          delete sd;
        }
        reportTarget.trackTotal += sd->trackTotal;
      }
      else
        delete sd;
    }
    else if(elemThis.tagName() == "section")
    {
      ORDetailSectionData * dsd = new ORDetailSectionData();
      if(parseReportDetailSection(elemThis, *dsd) == TRUE)
      {
        reportTarget.sections.append(dsd);
        reportTarget.trackTotal += dsd->trackTotal;
      }
      else
        delete dsd;
    }
    else if(elemThis.tagName() == "colordef")
    {
      ORColorDefData coldef;
      if(parseReportColorDefData(elemThis, coldef) == TRUE)
      {
        QColor col(coldef.red, coldef.green, coldef.blue);
        reportTarget.color_map[coldef.name] = col;
      }
    }
    else if(elemThis.tagName() == "database")
    {
      MemDbLoader mdb;
      bool ok = mdb.load(elemThis, db);
      if(!ok)
        qDebug("%s", mdb.lastError().toLatin1().data());
    }
    else if(elemThis.tagName() == "grid")
    {
      // Do nothing. This is used by the OpenRPT designer itself and we can ignore it here.
    }
    else
    {
      qDebug("While parsing report encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
    }
  }

  return TRUE;
}


bool parseReportParameter(const QDomElement & elemSource, ORReportData & reportTarget)
{
  if(elemSource.tagName() != "parameter")
    return FALSE;

  ORParameter param;
  
  param.name = elemSource.attribute("name");
  if(param.name.isEmpty())
    return FALSE;

  param.type = elemSource.attribute("type");
  param.defaultValue  = elemSource.attribute("default");
  param.listtype = elemSource.attribute("listtype");
  param.active = (elemSource.attribute("active") == "true");
  QList<QPair<QString,QString> > pairs;
  if(param.listtype.isEmpty())
    param.description = elemSource.text();
  else
  {
    QDomNodeList section = elemSource.childNodes();
    for(int nodeCounter = 0; nodeCounter < section.count(); nodeCounter++)
    {
      QDomElement elemThis = section.item(nodeCounter).toElement();
      if(elemThis.tagName() == "description")
        param.description = elemThis.text();
      else if(elemThis.tagName() == "query")
        param.query = elemThis.text();
      else if(elemThis.tagName() == "item")
        param.values.append(qMakePair(elemThis.attribute("value"), elemThis.text()));
      else
        qDebug("While parsing parameter encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
    }
  }

  reportTarget.definedParams.insert(param.name, param);

  return TRUE;
}

