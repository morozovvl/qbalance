/****************************************************************************
** Meta object code from reading C++ file 'selectmql.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../selectmql.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectmql.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectMQL[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   11,   10,   10, 0x0a,
      44,   10,   10,   10, 0x09,
      61,   10,   10,   10, 0x09,
      73,   10,   10,   10, 0x09,
      85,   10,   10,   10, 0x09,

 // methods: signature, parameters, type, tag, flags
     101,   10,   97,   10, 0x02,
     117,   10,  109,   10, 0x02,
     125,   10,   97,   10, 0x02,
     130,   10,  109,   10, 0x02,
     137,   10,  109,   10, 0x02,
     145,   10,  109,   10, 0x02,
     153,   10,  109,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_SelectMQL[] = {
    "SelectMQL\0\0id\0selectedQuery(int)\0"
    "setId(int)\0languageChange()\0sAccepted()\0"
    "sPopulate()\0sRejected()\0int\0grade()\0"
    "QString\0group()\0id()\0name()\0notes()\0"
    "query()\0schema()\0"
};

const QMetaObject SelectMQL::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SelectMQL,
      qt_meta_data_SelectMQL, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectMQL::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectMQL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectMQL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectMQL))
        return static_cast<void*>(const_cast< SelectMQL*>(this));
    if (!strcmp(_clname, "Ui::SelectMQL"))
        return static_cast< Ui::SelectMQL*>(const_cast< SelectMQL*>(this));
    return QWidget::qt_metacast(_clname);
}

int SelectMQL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectedQuery((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: languageChange(); break;
        case 3: sAccepted(); break;
        case 4: sPopulate(); break;
        case 5: sRejected(); break;
        case 6: { int _r = grade();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { QString _r = group();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { int _r = id();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = notes();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = query();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = schema();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SelectMQL::selectedQuery(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
