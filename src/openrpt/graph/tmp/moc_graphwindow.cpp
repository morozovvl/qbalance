/****************************************************************************
** Meta object code from reading C++ file 'graphwindow.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graphwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      30,   12,   12,   12, 0x0a,
      51,   47,   12,   12, 0x0a,
      84,   47,   12,   12, 0x0a,
     118,   12,   12,   12, 0x0a,
     145,  138,   12,   12, 0x0a,
     156,   12,   12,   12, 0x0a,
     174,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_GraphWindow[] = {
    "GraphWindow\0\0setColCount(int)\0"
    "setRowCount(int)\0r,s\0"
    "_dataTable_valueChanged(int,int)\0"
    "_labelTable_valueChanged(int,int)\0"
    "_btnClear_clicked()\0haveDB\0init(bool)\0"
    "_btnSql_clicked()\0languageChange()\0"
};

const QMetaObject GraphWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GraphWindow,
      qt_meta_data_GraphWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphWindow))
        return static_cast<void*>(const_cast< GraphWindow*>(this));
    if (!strcmp(_clname, "Ui::GraphWindow"))
        return static_cast< Ui::GraphWindow*>(const_cast< GraphWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GraphWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setColCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setRowCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _dataTable_valueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _labelTable_valueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _btnClear_clicked(); break;
        case 5: init((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _btnSql_clicked(); break;
        case 7: languageChange(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
