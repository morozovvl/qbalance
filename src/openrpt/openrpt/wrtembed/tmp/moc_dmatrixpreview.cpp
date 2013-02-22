/****************************************************************************
** Meta object code from reading C++ file 'dmatrixpreview.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dmatrixpreview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dmatrixpreview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DMatrixPreview[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   15,   16,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   40,   15,   15, 0x0a,
      66,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DMatrixPreview[] = {
    "DMatrixPreview\0\0bool\0escapeSignal(bool)\0"
    "format\0generePreview(int)\0escapeEvent()\0"
};

const QMetaObject DMatrixPreview::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DMatrixPreview,
      qt_meta_data_DMatrixPreview, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DMatrixPreview::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DMatrixPreview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DMatrixPreview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DMatrixPreview))
        return static_cast<void*>(const_cast< DMatrixPreview*>(this));
    return QDialog::qt_metacast(_clname);
}

int DMatrixPreview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = escapeSignal((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: generePreview((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: escapeEvent(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
bool DMatrixPreview::escapeSignal(bool _t1)
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
