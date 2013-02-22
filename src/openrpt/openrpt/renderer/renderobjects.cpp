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

#include <QPainter>

#include "renderobjects.h"
#include "parsexmlutils.h"

//
// ORODocument
//
ORODocument::ORODocument(const QString & pTitle)
  : _title(pTitle)
{
}

ORODocument::~ORODocument()
{
  while(!_pages.isEmpty())
  {
    OROPage * p = _pages.takeFirst();
    p->_document = 0;
    delete p;
  }
}

void ORODocument::setTitle(const QString & pTitle)
{
  _title = pTitle;
}

OROPage* ORODocument::page(int pnum)
{
  return _pages.at(pnum);
}

void ORODocument::addPage(OROPage* p)
{
  if(p == 0)
    return;

  // check that this page is not already in another document

  p->_document = this;
  _pages.append(p);
}

void ORODocument::setPageOptions(const ReportPageOptions & options)
{
  _pageOptions = options;
}

//
// OROPage
//
OROPage::OROPage(ORODocument * pDocument)
  : _document(pDocument)
{
  _wmOpacity = 25;
  _bgPos = QPointF(0, 0);
  _bgSize = QSizeF(1, 1);
  _bgScale = false;
  _bgScaleMode = Qt::IgnoreAspectRatio;
  _bgAlign = Qt::AlignLeft | Qt::AlignTop;
  _bgOpacity = 25;
}

OROPage::~OROPage()
{
  if(_document != 0)
  {
    _document->_pages.removeAt(page());
    _document = 0;
  }

  while(!_primitives.isEmpty())
  {
    OROPrimitive* p = _primitives.takeFirst();
    p->_page = 0;
    delete p;
  }
}

int OROPage::page() const
{
  if(_document != 0)
  {
    for(int i = 0; i < _document->_pages.size(); i++)
    {
      if(_document->_pages.at(i) == this)
        return i;
    }
  }
  return -1;
}

OROPrimitive* OROPage::primitive(int idx)
{
  return _primitives.at(idx);
}

void OROPage::addPrimitive(OROPrimitive* p)
{
  if(p == 0)
    return;

  // check that this primitve is not already in another page

  p->_page = this;
  _primitives.append(p);
}

void OROPage::setWatermarkText(const QString & txt)
{
  _wmText = txt;
}

void OROPage::setWatermarkFont(const QFont & fnt)
{
  _wmFont = fnt;
}

void OROPage::setWatermarkOpacity(unsigned char o)
{
  _wmOpacity = o;
}

void OROPage::setBackgroundImage(const QImage & img)
{
  _bgImage = img;
}

void OROPage::setBackgroundPosition(const QPointF & p)
{
  _bgPos = p;
}

void OROPage::setBackgroundSize(const QSizeF & s)
{
  _bgSize = s;
}

void OROPage::setBackgroundScale(bool b)
{
  _bgScale = b;
}

void OROPage::setBackgroundScaleMode(Qt::AspectRatioMode m)
{
  _bgScaleMode = m;
}

void OROPage::setBackgroundAlign(int a)
{
  _bgAlign = a;
}

void OROPage::setBackgroundOpacity(unsigned char o)
{
  _bgOpacity = o;
}

//
// OROPrimitive
//
OROPrimitive::OROPrimitive(ORObject *o, int pType)
  : _type(pType), _pen(o->pen()), _border(o->border()), _brush(o->brush()), _rotation(o->rotation())
{
  _page = 0;
}

OROPrimitive::~OROPrimitive()
{
  if(_page != 0)
  {
    _page->_primitives.removeAt(_page->_primitives.indexOf(this));
    _page = 0;
  }
}

void OROPrimitive::setPosition(const QPointF & p)
{
  _position = p;
}

void OROPrimitive::setRotationAxis(const QPointF p)
{
	_rotationAxis = p;
}

void OROPrimitive::drawRect(QRectF rc, QPainter* painter, int printResolution)
{
  if(border().width()==0 && type()!=ORORect::Rect && brush()==Qt::NoBrush)
  {
    return; // nothing to draw
  }

  QPen pen = border();
  pen.setWidthF((pen.widthF() / 100) * printResolution);
  painter->save();
  painter->setPen(border().width()==0 && type()!=ORORect::Rect ? Qt::NoPen : pen);
  painter->setBrush(brush());
  painter->drawRect(rc);
  painter->restore();
}

//
// OROTextBox
//
const int OROTextBox::TextBox = 1;
OROTextBox::OROTextBox(ORObject *o)
  : OROPrimitive(o, OROTextBox::TextBox)
{
  _flags = 0;
}

OROTextBox::~OROTextBox()
{
}

void OROTextBox::setSize(const QSizeF & s)
{
  _size = s;
}

void OROTextBox::setText(const QString & s)
{
  _text = s;
}

void OROTextBox::setFont(const QFont & f)
{
  _font = f;
}

void OROTextBox::setFlags(int f)
{
  _flags = f;
}

//
// OROLine
//
const int OROLine::Line = 2;

OROLine::OROLine(ORObject *o)
  : OROPrimitive(o, OROLine::Line)
{
} 

OROLine::~OROLine()
{
}

void OROLine::setStartPoint(const QPointF & p)
{
  setPosition(p);
}

void OROLine::setEndPoint(const QPointF & p)
{
  _endPoint = p;
}

//
// OROImage
//
const int OROImage::Image = 3;

OROImage::OROImage(ORObject *o)
  : OROPrimitive(o, OROImage::Image)
{
  _scaled = false;
  _transformFlags = Qt::FastTransformation;
  _aspectFlags = Qt::IgnoreAspectRatio;
}

OROImage::~OROImage()
{
}

void OROImage::setImage(const QImage & img)
{
  _image = img;
}

void OROImage::setSize(const QSizeF & sz)
{
  _size = sz;
}

void OROImage::setScaled(bool b)
{
  _scaled = b;
}

void OROImage::setTransformationMode(int tm)
{
  _transformFlags = tm;
}

void OROImage::setAspectRatioMode(int arm)
{
  _aspectFlags = arm;
}

//
// ORORect
//
const int ORORect::Rect = 4;

ORORect::ORORect(ORObject *o)
  : OROPrimitive(o, ORORect::Rect)
{
}

ORORect::~ORORect()
{
}

void ORORect::setSize(const QSizeF & s)
{
  _size = s;
}

void ORORect::setRect(const QRectF & r)
{
  setPosition(r.topLeft());
  setSize(r.size());
}



