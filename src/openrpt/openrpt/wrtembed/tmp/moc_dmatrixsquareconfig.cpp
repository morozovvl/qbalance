/****************************************************************************
** Meta object code from reading C++ file 'dmatrixsquareconfig.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dmatrixsquareconfig.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmatrixsquareconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DMatrixSquareConfig[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   42,   20,   20, 0x0a,
      68,   20,   20,   20, 0x2a,
      82,   20,   20,   20, 0x09,
      99,   21,   20,   20, 0x0a,
     119,   20,   20,   20, 0x08,
     147,   21,   20,   20, 0x08,
     166,   21,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DMatrixSquareConfig[] = {
    "DMatrixSquareConfig\0\0i\0refreshWidget(int)\0"
    "visible\0setVisible2(bool)\0setVisible2()\0"
    "languageChange()\0setCursorValue(int)\0"
    "on__previewButton_clicked()\0"
    "formatRefresh(int)\0capacityRefresh(int)\0"
};

const QMetaObject DMatrixSquareConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DMatrixSquareConfig,
      qt_meta_data_DMatrixSquareConfig, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DMatrixSquareConfig::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DMatrixSquareConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DMatrixSquareConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DMatrixSquareConfig))
        return static_cast<void*>(const_cast< DMatrixSquareConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int DMatrixSquareConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setVisible2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setVisible2(); break;
        case 3: languageChange(); break;
        case 4: setCursorValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on__previewButton_clicked(); break;
        case 6: formatRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: capacityRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DMatrixSquareConfig::refreshWidget(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
