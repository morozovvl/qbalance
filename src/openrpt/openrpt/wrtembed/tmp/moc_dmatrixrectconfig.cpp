/****************************************************************************
** Meta object code from reading C++ file 'dmatrixrectconfig.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dmatrixrectconfig.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmatrixrectconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DMatrixRectConfig[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   41,   18,   18, 0x0a,
      67,   18,   18,   18, 0x2a,
      81,   19,   18,   18, 0x0a,
     100,   18,   18,   18, 0x08,
     130,  128,   18,   18, 0x08,
     151,   19,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DMatrixRectConfig[] = {
    "DMatrixRectConfig\0\0index\0signalType(int)\0"
    "visible\0setVisible2(bool)\0setVisible2()\0"
    "setIndexValue(int)\0on__previewButton_clicked()\0"
    "i\0capacityRefresh(int)\0indexType(int)\0"
};

const QMetaObject DMatrixRectConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DMatrixRectConfig,
      qt_meta_data_DMatrixRectConfig, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DMatrixRectConfig::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DMatrixRectConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DMatrixRectConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DMatrixRectConfig))
        return static_cast<void*>(const_cast< DMatrixRectConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int DMatrixRectConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setVisible2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setVisible2(); break;
        case 3: setIndexValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on__previewButton_clicked(); break;
        case 5: capacityRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: indexType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DMatrixRectConfig::signalType(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
