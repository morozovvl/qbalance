/****************************************************************************
** Meta object code from reading C++ file 'reportparameter.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../reportparameter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportparameter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportParameter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   16,   17,   16, 0x0a,
      49,   16,   37,   16, 0x0a,
      66,   61,   16,   16, 0x0a,
      94,   88,   16,   16, 0x0a,
     120,   16,   16,   16, 0x0a,
     140,   16,   16,   16, 0x0a,
     147,   16,   16,   16, 0x0a,
     155,   16,   16,   16, 0x0a,
     165,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ReportParameter[] = {
    "ReportParameter\0\0QString\0paramName()\0"
    "ORParameter\0paramData()\0text\0"
    "setParamName(QString)\0param\0"
    "setParamData(ORParameter)\0sSelectionChanged()\0"
    "sAdd()\0sEdit()\0sRemove()\0languageChange()\0"
};

const QMetaObject ReportParameter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReportParameter,
      qt_meta_data_ReportParameter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportParameter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportParameter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportParameter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportParameter))
        return static_cast<void*>(const_cast< ReportParameter*>(this));
    if (!strcmp(_clname, "Ui::ReportParameter"))
        return static_cast< Ui::ReportParameter*>(const_cast< ReportParameter*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReportParameter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = paramName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { ORParameter _r = paramData();
            if (_a[0]) *reinterpret_cast< ORParameter*>(_a[0]) = _r; }  break;
        case 2: setParamName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: setParamData((*reinterpret_cast< const ORParameter(*)>(_a[1]))); break;
        case 4: sSelectionChanged(); break;
        case 5: sAdd(); break;
        case 6: sEdit(); break;
        case 7: sRemove(); break;
        case 8: languageChange(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
