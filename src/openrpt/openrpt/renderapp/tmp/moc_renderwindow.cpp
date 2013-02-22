/****************************************************************************
** Meta object code from reading C++ file 'renderwindow.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../renderwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x0a,
      46,   37,   13,   13, 0x0a,
      64,   13,   13,   13, 0x0a,
      86,   75,   13,   13, 0x0a,
     114,  104,   13,   13, 0x0a,
     131,   13,   13,   13, 0x2a,
     145,  104,   13,   13, 0x0a,
     160,   13,   13,   13, 0x2a,
     172,   13,   13,   13, 0x0a,
     201,  189,   13,   13, 0x0a,
     226,   13,   13,   13, 0x0a,
     255,  237,   13,   13, 0x0a,
     294,  290,   13,   13, 0x0a,
     320,   13,   13,   13, 0x09,
     337,   13,   13,   13, 0x09,
     344,   13,   13,   13, 0x09,
     352,   13,   13,   13, 0x09,
     362,   13,   13,   13, 0x09,
     382,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RenderWindow[] = {
    "RenderWindow\0\0helpAbout()\0fileOpen()\0"
    "filename\0fileOpen(QString)\0fileLoad()\0"
    "reportname\0fileLoad(QString)\0numCopies\0"
    "filePreview(int)\0filePreview()\0"
    "filePrint(int)\0filePrint()\0filePrintToPDF()\0"
    "pdfFileName\0filePrintToPDF(QString&)\0"
    "fileExit()\0name,value,active\0"
    "updateParam(QString,QVariant,bool)\0"
    "doc\0setDocument(QDomDocument)\0"
    "languageChange()\0sAdd()\0sEdit()\0"
    "sDelete()\0sSelectionChanged()\0sList()\0"
};

const QMetaObject RenderWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RenderWindow,
      qt_meta_data_RenderWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderWindow))
        return static_cast<void*>(const_cast< RenderWindow*>(this));
    if (!strcmp(_clname, "Ui::RenderWindow"))
        return static_cast< Ui::RenderWindow*>(const_cast< RenderWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RenderWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: helpAbout(); break;
        case 1: fileOpen(); break;
        case 2: fileOpen((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: fileLoad(); break;
        case 4: fileLoad((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: filePreview((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: filePreview(); break;
        case 7: filePrint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: filePrint(); break;
        case 9: filePrintToPDF(); break;
        case 10: filePrintToPDF((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: fileExit(); break;
        case 12: updateParam((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 13: setDocument((*reinterpret_cast< const QDomDocument(*)>(_a[1]))); break;
        case 14: languageChange(); break;
        case 15: sAdd(); break;
        case 16: sEdit(); break;
        case 17: sDelete(); break;
        case 18: sSelectionChanged(); break;
        case 19: sList(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
