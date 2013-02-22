/****************************************************************************
** Meta object code from reading C++ file 'dbfiledialog.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wrtembed/dbfiledialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbfiledialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DBFileDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   14,   13, 0x0a,
      34,   13,   26,   13, 0x0a,
      44,   13,   14,   13, 0x0a,
      55,   13,   26,   13, 0x0a,
      67,   13,   26,   13, 0x0a,
      81,   13,   14,   13, 0x0a,
      96,   13,   13,   13, 0x0a,
     115,   13,   13,   13, 0x09,
     132,   13,   13,   13, 0x09,
     155,  150,   13,   13, 0x09,
     177,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DBFileDialog[] = {
    "DBFileDialog\0\0int\0getId()\0QString\0"
    "getName()\0getGrade()\0getSource()\0"
    "getNameById()\0getGradeById()\0"
    "sGradeChanged(int)\0languageChange()\0"
    "sSelectedReport()\0text\0sNameChanged(QString)\0"
    "sNameGradeChanged()\0"
};

const QMetaObject DBFileDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DBFileDialog,
      qt_meta_data_DBFileDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DBFileDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DBFileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DBFileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DBFileDialog))
        return static_cast<void*>(const_cast< DBFileDialog*>(this));
    if (!strcmp(_clname, "Ui::DBFileDialog"))
        return static_cast< Ui::DBFileDialog*>(const_cast< DBFileDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DBFileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = getId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { QString _r = getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { int _r = getGrade();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { QString _r = getSource();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = getNameById();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { int _r = getGradeById();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: sGradeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: languageChange(); break;
        case 8: sSelectedReport(); break;
        case 9: sNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: sNameGradeChanged(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
