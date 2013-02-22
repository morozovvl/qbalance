/****************************************************************************
** Meta object code from reading C++ file 'parameterproperties.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../parameterproperties.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parameterproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParameterProperties[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      38,   20,   20,   20, 0x0a,
      49,   20,   20,   20, 0x0a,
      62,   20,   20,   20, 0x0a,
      75,   20,   20,   20, 0x0a,
      90,   20,   20,   20, 0x0a,
     102,  100,   20,   20, 0x0a,
     120,  118,   20,   20, 0x0a,
     145,  100,   20,   20, 0x0a,
     162,  100,   20,   20, 0x0a,
     179,  100,   20,   20, 0x0a,
     203,  100,   20,   20, 0x0a,

 // methods: signature, parameters, type, tag, flags
     227,   20,  222,   20, 0x02,
     252,   20,  236,   20, 0x02,
     267,   20,  259,   20, 0x02,
     289,   20,  274,   20, 0x02,
     296,   20,  259,   20, 0x02,
     316,   20,  307,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ParameterProperties[] = {
    "ParameterProperties\0\0languageChange()\0"
    "editItem()\0deleteItem()\0moveItemUp()\0"
    "moveItemDown()\0newItem()\0p\0setActive(bool)\0"
    "l\0setList(QList<QVariant>)\0setName(QString)\0"
    "setType(QString)\0setType(QVariant::Type)\0"
    "setValue(QVariant)\0bool\0active()\0"
    "QList<QVariant>\0list()\0QString\0name()\0"
    "QVariant::Type\0type()\0typeName()\0"
    "QVariant\0value()\0"
};

const QMetaObject ParameterProperties::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParameterProperties,
      qt_meta_data_ParameterProperties, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParameterProperties::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParameterProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParameterProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParameterProperties))
        return static_cast<void*>(const_cast< ParameterProperties*>(this));
    if (!strcmp(_clname, "Ui::ParameterProperties"))
        return static_cast< Ui::ParameterProperties*>(const_cast< ParameterProperties*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParameterProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: languageChange(); break;
        case 1: editItem(); break;
        case 2: deleteItem(); break;
        case 3: moveItemUp(); break;
        case 4: moveItemDown(); break;
        case 5: newItem(); break;
        case 6: setActive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: setList((*reinterpret_cast< const QList<QVariant>(*)>(_a[1]))); break;
        case 8: setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: setType((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: setType((*reinterpret_cast< QVariant::Type(*)>(_a[1]))); break;
        case 11: setValue((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 12: { bool _r = active();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { QList<QVariant> _r = list();
            if (_a[0]) *reinterpret_cast< QList<QVariant>*>(_a[0]) = _r; }  break;
        case 14: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QVariant::Type _r = type();
            if (_a[0]) *reinterpret_cast< QVariant::Type*>(_a[0]) = _r; }  break;
        case 16: { QString _r = typeName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { QVariant _r = value();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
