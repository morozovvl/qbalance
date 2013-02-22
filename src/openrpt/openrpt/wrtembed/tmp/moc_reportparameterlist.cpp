/****************************************************************************
** Meta object code from reading C++ file 'reportparameterlist.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../reportparameterlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportparameterlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportParameterList[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,
      38,   20,   20,   20, 0x09,
      45,   20,   20,   20, 0x09,
      53,   20,   20,   20, 0x09,
      63,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ReportParameterList[] = {
    "ReportParameterList\0\0languageChange()\0"
    "sAdd()\0sEdit()\0sDelete()\0"
    "sEdit(QListWidgetItem*)\0"
};

const QMetaObject ReportParameterList::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReportParameterList,
      qt_meta_data_ReportParameterList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportParameterList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportParameterList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportParameterList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportParameterList))
        return static_cast<void*>(const_cast< ReportParameterList*>(this));
    if (!strcmp(_clname, "Ui::ReportParameterList"))
        return static_cast< Ui::ReportParameterList*>(const_cast< ReportParameterList*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReportParameterList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: languageChange(); break;
        case 1: sAdd(); break;
        case 2: sEdit(); break;
        case 3: sDelete(); break;
        case 4: sEdit((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
