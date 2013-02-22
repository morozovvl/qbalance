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

#include "orprintrender.h"
#include "renderobjects.h"
#include "pagesizeinfo.h"

static void renderBackground(QImage &, const QImage &, const QRect &, bool, Qt::AspectRatioMode, int, unsigned int);
static void renderWatermark(QImage &, const QString &, const QFont &, const unsigned int, double, double, double, double);

ORPrintRender::ORPrintRender()
{
  _printer = 0;
  _painter = 0;
}

ORPrintRender::~ORPrintRender()
{
}

void ORPrintRender::setPrinter(QPrinter * pPrinter)
{
  _printer = pPrinter;
}

void ORPrintRender::setPainter(QPainter * pPainter)
{
  _painter = pPainter;
}

bool ORPrintRender::setupPrinter(ORODocument * pDocument, QPrinter * pPrinter)
{
  if(pDocument == 0 || pPrinter == 0)
    return false;

  pPrinter->setCreator("OpenRPT Print Renderer");
  pPrinter->setDocName(pDocument->title());
  pPrinter->setFullPage(true);
  pPrinter->setOrientation((pDocument->pageOptions().isPortrait() ? QPrinter::Portrait : QPrinter::Landscape));
  pPrinter->setPageOrder(QPrinter::FirstPageFirst);

  PageSizeInfo psi = PageSizeInfo::getByName(pDocument->pageOptions().getPageSize());
  if(psi.isNull())
  {
    // TODO:
    //psi = PageSizeInfo::findNearest((int)(pDocument->pageOptions().getCustomWidth() * 100), (int)(pDocument->pageOptions().getCustomHeight() * 100));
    //if(psi.isNull())
    //  pPrinter->setPageSize(QPrinter::Custom);
    //else
    //  pPrinter->setPageSize((QPrinter::PageSize)psi.qpValue());
    pPrinter->setPaperSize(QSizeF(pDocument->pageOptions().getCustomWidth(), pDocument->pageOptions().getCustomHeight()), QPrinter::Inch);
  }
  else
    pPrinter->setPageSize((QPrinter::PageSize)psi.qpValue());

  return true;
}

bool ORPrintRender::render(ORODocument * pDocument)
{
  if(pDocument == 0 || _printer == 0)
    return false;

  _printer->setFullPage(true);

  bool deleteWhenComplete = false;
  bool endWhenComplete = false;

  QPainter localPainter;
  if(_painter == 0)
  {
    deleteWhenComplete = true;
    _painter = &localPainter;
  } 

  if(!_painter->isActive())
  {
    endWhenComplete = true;
    if(!_painter->begin(_printer))
      return false;
  }

  qreal xDpi = _printer->logicalDpiX();
  qreal yDpi = _printer->logicalDpiY();

  int fromPage = _printer->fromPage();
  if(fromPage > 0)
    fromPage -= 1;
  int toPage = _printer->toPage();
  if(toPage == 0 || toPage > pDocument->pages())
    toPage = pDocument->pages();

  for(int copy = 0; copy < _printer->numCopies(); copy++)
  {
    for(int page = fromPage; page < toPage; page++)
    {
      if(page > 0)
        _printer->newPage();

      int pageToPrint = page;
      if(_printer->pageOrder() == QPrinter::LastPageFirst)
        pageToPrint = toPage - 1 - page;

      QSize margins(_printer->paperRect().left() - _printer->pageRect().left(), _printer->paperRect().top() - _printer->pageRect().top());
      renderPage(pDocument, pageToPrint, _painter, xDpi, yDpi, margins, _printer->resolution());
    }
  }

  if(endWhenComplete)
    _painter->end();

  if(deleteWhenComplete)
    _painter = 0;

  return true;
}

void renderBackground(QImage & dest, const QImage & bgImage, const QRect & bgRect, bool bgScale, Qt::AspectRatioMode bgScaleMode, int bgAlign, unsigned int bgOpacity)
{
  QImage img = bgImage;
  if(img.isNull())
    return;

  if(bgScale)
    img = img.scaled(bgRect.size(), bgScaleMode, Qt::SmoothTransformation);

  // determine where the upper left hand corner of the image should
  // be located to have it aligned as specified within the area for
  // the image.
  int sx = bgRect.left(); // default to LEFT
  int sy = bgRect.top(); // default to TOP

  if((Qt::AlignHorizontal_Mask & bgAlign) == Qt::AlignRight)
    sx = bgRect.right() - img.width();
  else if((Qt::AlignHorizontal_Mask & bgAlign) == Qt::AlignHCenter)
    sx = bgRect.center().x() - (img.width() / 2);
  else
    sx = bgRect.left(); // default to LEFT

  if((Qt::AlignVertical_Mask & bgAlign) == Qt::AlignBottom)
    sy = bgRect.bottom() - img.height();
  else if((Qt::AlignVertical_Mask & bgAlign) == Qt::AlignVCenter)
    sy = bgRect.center().y() - (img.height() / 2);
  else
    sy = bgRect.top(); // default to TOP

  // now we need to render the image on our destination image
  double opacity = bgOpacity / 255.0;
  double opacity_inv = 1.0 - opacity;
  int dx = 0;
  int dy = 0;
  QRgb s = 0;
  QRgb d = 0;
  for(int y = 0; y < img.height(); y++) {
    for(int x = 0; x < img.width(); x++) {
      dx = sx + x;
      dy = sy + y;
      if(bgRect.contains(dx, dy)) {
        s = img.pixel(x, y);
        if((s & 0x00ffffff) == 0x00ffffff) continue; // if it's white just skip it
        d = dest.pixel(dx, dy);
        dest.setPixel(dx, dy, qRgb( (int)((qRed(s) * opacity) + (qRed(d) * opacity_inv)),
                                    (int)((qGreen(s) * opacity) + (qGreen(d) * opacity_inv)),
                                    (int)((qBlue(s) * opacity) + (qBlue(d) * opacity_inv)) ));
      }
    }
  }
}

#include <math.h>
#include <QFontDatabase>

void renderWatermark(QImage & image, const QString & wmText, const QFont & wmFont, const unsigned int wmOpacity, double pA, double pB, double pC, double pD)
{
  const double pi = 3.14159265358979323846;

  double w = ((double)image.width() - pA);
  double h = ((double)image.height() - pB);
  double theta = (pi/-2.0) + atan(w / h);
  double l = sqrt((w * w) + (h * h));

  const double sintheta = sin(theta);
  const double costheta = cos(theta);

  double margin_width = pC;
  double margin_height = pD;

  int offset = (int)(l * 0.05);
  int l2 = (int)(l * 0.9);

  int x = (int)(sintheta * h) + offset;
  int y = (int)(costheta * h);

  QFont fnt = wmFont;
  QFontMetrics fm = QFontMetrics(fnt);
  QFontInfo fi(fnt);
  QString family = fi.family();
  QList<int> sizes = QFontDatabase().pointSizes(family);
  qSort(sizes);

  for(int i = sizes.size() - 1; i > 0; i--)
  {
    fnt.setPointSize(sizes[i]);
    fm = QFontMetrics(fnt);
    if(fm.boundingRect(wmText).width() < l2)
      break;
  }
  int fh = fm.height();

  y = y - (fh/2);

  //NB QPixmap not safe outside of main thread, using QImage instead
  QImage wm(image.width(), image.height(), QImage::Format_RGB32);
  wm.fill(0xFFFFFFFF);
  QPainter pPainter;
  pPainter.begin(&wm);
  pPainter.setFont(fnt);
  pPainter.translate(margin_width, margin_height);
  pPainter.rotate((theta/pi)*180);
  pPainter.drawText(x, y, l2, fh, Qt::AlignCenter, wmText);
  pPainter.end();

  double opacity = wmOpacity / 255.0;
  double opacity_inv = 1.0 - opacity;

  QRgb s = 0;
  QRgb d = 0;
  for(y = 0; y < image.height(); y++) {
    for(x = 0; x < image.width(); x++) {
      s = wm.pixel(x, y);
      if((s & 0x00ffffff) == 0x00ffffff) continue; // if it's white just skip it
      d = image.pixel(x, y);
      image.setPixel(x, y, qRgb( (int)((qRed(s) * opacity) + (qRed(d) * opacity_inv)),
                                 (int)((qGreen(s) * opacity) + (qGreen(d) * opacity_inv)),
                                 (int)((qBlue(s) * opacity) + (qBlue(d) * opacity_inv)) ));
    }
  }
}

void ORPrintRender::renderPage(ORODocument * pDocument, int pageNb, QPainter *painter, qreal xDpi, qreal yDpi, QSize margins, int printResolution)
{
  OROPage * p = pDocument->page(pageNb);

  if(((!p->backgroundImage().isNull()) && (p->backgroundOpacity() != 0)) ||
     ((!p->watermarkText().isEmpty()) && (p->watermarkOpacity() != 0)))
  {
    // Do some simple processing used by both Background and Watermark
    const int resolution = 100;
    bool doBgWm = false;
    int printMarginWidth = margins.width();
    int printMarginHeight = margins.height();

    QString pageSize = pDocument->pageOptions().getPageSize();
    int pageWidth = 0;
    int pageHeight = 0;
    if(pageSize == "Custom") {
      // if this is custom sized sheet of paper we will just use those values
      pageWidth = (int)(pDocument->pageOptions().getCustomWidth() * resolution);
      pageHeight = (int)(pDocument->pageOptions().getCustomHeight() * resolution);
    } else {
      // lookup the correct size information for the specified size paper
      PageSizeInfo pi = PageSizeInfo::getByName(pageSize);
      if(!pi.isNull())
      {
        pageWidth = (int)((pi.width() / 100.0) * resolution);
        pageHeight = (int)((pi.height() / 100.0) * resolution);
      }
    }
    if(!pDocument->pageOptions().isPortrait()) {
      int tmp = pageWidth;
      pageWidth = pageHeight;
      pageHeight = tmp;
    }
    if(pageWidth < 1 || pageHeight < 1) {
      // whoops we couldn't find it.... we will use the values from the painter
      // and add in the margins of the printer to get what should be the correct
      // size of the sheet of paper we are printing to.
      pageWidth = (int)(((painter->viewport().width() + printMarginWidth + printMarginWidth) / xDpi) * resolution);
      pageHeight = (int)(((painter->viewport().height() + printMarginHeight + printMarginHeight) / yDpi) * resolution);
    }

    QImage image = QImage(pageWidth, pageHeight, QImage::Format_RGB32);
    QPainter gPainter;
    if(gPainter.begin(&image))
      gPainter.fillRect(gPainter.viewport(), QColor(Qt::white));

    // Render Background
    if((!p->backgroundImage().isNull()) && (p->backgroundOpacity() != 0))
    {
      doBgWm = true;
      QPointF ps = p->backgroundPosition();
      QSizeF sz = p->backgroundSize();
      QRectF rc = QRectF(ps.x() * resolution, ps.y() * resolution, sz.width() * resolution, sz.height() * resolution);
      renderBackground(image, p->backgroundImage(), rc.toRect(),
        p->backgroundScale(), p->backgroundScaleMode(),
        p->backgroundAlign(), p->backgroundOpacity());
    }

    // Render Watermark
    if((!p->watermarkText().isEmpty()) && (p->watermarkOpacity() != 0))
    {
      doBgWm = true;
      renderWatermark(image, p->watermarkText(), p->watermarkFont(), p->watermarkOpacity(),
        ((pDocument->pageOptions().getMarginLeft() + pDocument->pageOptions().getMarginRight()) * resolution),
        ((pDocument->pageOptions().getMarginTop() + pDocument->pageOptions().getMarginBottom()) * resolution),
        pDocument->pageOptions().getMarginLeft() * resolution, pDocument->pageOptions().getMarginTop() * resolution);
    }

    if(doBgWm)
    {
      QRectF target(-printMarginWidth, -printMarginHeight, (painter->viewport().width() + printMarginWidth + printMarginWidth), (painter->viewport().height() + printMarginHeight + printMarginHeight));
      QRectF source(0, 0, image.width(), image.height());
      painter->drawImage(target, image, source);
    }
  }

  // Render Page Objects
  for(int i = 0; i < p->primitives(); i++)
  {
    OROPrimitive * prim = p->primitive(i);

    QPen pen(prim->pen());
    painter->save();
    painter->setPen(pen);
    painter->setBrush(prim->brush());

	QPointF ps = prim->position();
	if(prim->rotationAxis().isNull()) {
		painter->translate(ps.x() * xDpi, ps.y() * yDpi); 
		painter->rotate(prim->rotation()); // rotation around the origin of the primitive (not the center)
	}
	else { // rotation around the defined axis
		qreal xRot = prim->rotationAxis().x();
		qreal yRot = prim->rotationAxis().y();
		painter->translate(xRot * xDpi, yRot * yDpi); 
		painter->rotate(prim->rotation());
		painter->translate((ps.x() - xRot) * xDpi, (ps.y() - yRot) * yDpi); 
	}

    if(prim->type() == OROTextBox::TextBox)
    {
      OROTextBox * tb = (OROTextBox*)prim;

      QSizeF sz = tb->size();
      QRectF rc = QRectF(0, 0, sz.width() * xDpi, sz.height() * yDpi);

      prim->drawRect(rc, painter, printResolution);

	  painter->setFont(tb->font());
      painter->drawText(rc, tb->flags(), tb->text());
    }
    else if(prim->type() == OROLine::Line)
    {
        OROLine * ln = (OROLine*)prim;
		QPointF s = ln->startPoint();
		QPointF e = ln->endPoint();
        pen.setWidthF((pen.widthF() / 100) * printResolution);
		painter->setPen(pen);
		painter->drawLine(QLineF(0, 0, (e.x()-s.x()) * xDpi, (e.y()-s.y()) * yDpi));
    }
    else if(prim->type() == OROImage::Image)
    {
      OROImage * im = (OROImage*)prim;
      QSizeF sz = im->size();
      QRectF rc = QRectF(0, 0, sz.width() * xDpi, sz.height() * yDpi);

      prim->drawRect(rc, painter, printResolution);

      QImage img = im->image();
      if(im->scaled())
        img = img.scaled(rc.size().toSize(), (Qt::AspectRatioMode)im->aspectRatioMode(), (Qt::TransformationMode)im->transformationMode());

      QRectF sr = QRectF(QPointF(0.0, 0.0), rc.size().boundedTo(img.size()));
      painter->drawImage(rc.topLeft(), img, sr);
    }
    else if(prim->type() == ORORect::Rect)
    {
      QSizeF sz = ((OROTextBox*)prim)->size();
      QRectF rc = QRectF(0, 0, sz.width() * xDpi, sz.height() * yDpi);
      prim->drawRect(rc, painter, printResolution);
    }
    else
    {
      qDebug("unrecognized primitive type");
    }

    painter->restore();

  }
}

bool ORPrintRender::exportToPDF(ORODocument * pDocument, QString pdfFileName)
{
  if(!pDocument)
    return false;

  QPrinter printer(QPrinter::ScreenResolution);
  printer.setResolution(300);

#ifdef Q_WS_MAC
  printer.setOutputFormat( QPrinter::NativeFormat );
#else
  printer.setOutputFormat( QPrinter::PdfFormat );
#endif

  printer.setOutputFileName( pdfFileName );

  ORPrintRender render;
  render.setupPrinter(pDocument, &printer);
  render.setPrinter(&printer);
  return render.render(pDocument);
}

