/****************************************************************************
** Meta object code from reading C++ file 'reportgridoptions.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../reportgridoptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportgridoptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportGridOptions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   40,   18,   18, 0x0a,
      61,   18,   18,   18, 0x2a,
      74,   18,   18,   18, 0x0a,
      81,   18,   18,   18, 0x0a,
      90,   88,   18,   18, 0x0a,
     111,   88,   18,   18, 0x0a,
     132,   40,   18,   18, 0x0a,
     146,   18,   18,   18, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_ReportGridOptions[] = {
    "ReportGridOptions\0\0gridOptionsChanged()\0"
    "yes\0setVisible(bool)\0setVisible()\0"
    "show()\0hide()\0i\0setXInterval(double)\0"
    "setYInterval(double)\0setSnap(bool)\0"
    "setSnap()\0"
};

const QMetaObject ReportGridOptions::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReportGridOptions,
      qt_meta_data_ReportGridOptions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportGridOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportGridOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportGridOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportGridOptions))
        return static_cast<void*>(const_cast< ReportGridOptions*>(this));
    return QObject::qt_metacast(_clname);
}

int ReportGridOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: gridOptionsChanged(); break;
        case 1: setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setVisible(); break;
        case 3: show(); break;
        case 4: hide(); break;
        case 5: setXInterval((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: setYInterval((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: setSnap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: setSnap(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ReportGridOptions::gridOptionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
