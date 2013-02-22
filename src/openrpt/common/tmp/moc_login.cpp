/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../login.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_login[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   11,    7,    6, 0x0a,
      38,    6,    6,    6, 0x09,
      55,    6,    6,    6, 0x09,
      64,    6,    6,    6, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_login[] = {
    "login\0\0int\0pParams\0set(ParameterList)\0"
    "languageChange()\0sLogin()\0sOptions()\0"
};

const QMetaObject login::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_login,
      qt_meta_data_login, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &login::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *login::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_login))
        return static_cast<void*>(const_cast< login*>(this));
    if (!strcmp(_clname, "Ui::login"))
        return static_cast< Ui::login*>(const_cast< login*>(this));
    return QDialog::qt_metacast(_clname);
}

int login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = set((*reinterpret_cast< const ParameterList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: languageChange(); break;
        case 2: sLogin(); break;
        case 3: sOptions(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
