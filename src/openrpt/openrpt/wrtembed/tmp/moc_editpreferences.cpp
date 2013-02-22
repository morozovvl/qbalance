/****************************************************************************
** Meta object code from reading C++ file 'editpreferences.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editpreferences.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editpreferences.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditPreferences[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x0a,
      55,   16,   48,   16, 0x0a,
      67,   16,   48,   16, 0x0a,
      84,   16,   79,   16, 0x0a,
      95,   16,   79,   16, 0x0a,
     111,  106,   16,   16, 0x0a,
     134,  129,   16,   16, 0x0a,
     156,  152,   16,   16, 0x0a,
     184,   16,  178,   16, 0x0a,
     198,   16,   16,   16, 0x09,
     215,   16,   16,   16, 0x09,
     239,  235,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_EditPreferences[] = {
    "EditPreferences\0\0x,y\0setGridSize(double,double)\0"
    "double\0gridSizeX()\0gridSizeY()\0bool\0"
    "showGrid()\0snapGrid()\0show\0setShowGrid(bool)\0"
    "snap\0setSnapGrid(bool)\0fnt\0"
    "setDefaultFont(QFont)\0QFont\0defaultFont()\0"
    "languageChange()\0changeDefaultFont()\0"
    "sel\0selLanguage(QString)\0"
};

const QMetaObject EditPreferences::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditPreferences,
      qt_meta_data_EditPreferences, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditPreferences::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditPreferences::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditPreferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditPreferences))
        return static_cast<void*>(const_cast< EditPreferences*>(this));
    if (!strcmp(_clname, "Ui::EditPreferences"))
        return static_cast< Ui::EditPreferences*>(const_cast< EditPreferences*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditPreferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setGridSize((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: { double _r = gridSizeX();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 2: { double _r = gridSizeY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 3: { bool _r = showGrid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = snapGrid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: setShowGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: setSnapGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: setDefaultFont((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 8: { QFont _r = defaultFont();
            if (_a[0]) *reinterpret_cast< QFont*>(_a[0]) = _r; }  break;
        case 9: languageChange(); break;
        case 10: changeDefaultFont(); break;
        case 11: selLanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
