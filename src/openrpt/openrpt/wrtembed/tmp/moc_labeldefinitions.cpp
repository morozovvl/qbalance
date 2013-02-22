/****************************************************************************
** Meta object code from reading C++ file 'labeldefinitions.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../labeldefinitions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'labeldefinitions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LabelDefinitions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      49,   17,   17,   17, 0x0a,
      67,   17,   17,   17, 0x0a,
      87,   17,   17,   17, 0x0a,
     104,   17,   17,   17, 0x0a,
     111,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LabelDefinitions[] = {
    "LabelDefinitions\0\0editLabelDef(QListWidgetItem*)\0"
    "btnEdit_clicked()\0btnDelete_clicked()\0"
    "btnAdd_clicked()\0init()\0languageChange()\0"
};

const QMetaObject LabelDefinitions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LabelDefinitions,
      qt_meta_data_LabelDefinitions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LabelDefinitions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LabelDefinitions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LabelDefinitions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LabelDefinitions))
        return static_cast<void*>(const_cast< LabelDefinitions*>(this));
    if (!strcmp(_clname, "Ui::LabelDefinitions"))
        return static_cast< Ui::LabelDefinitions*>(const_cast< LabelDefinitions*>(this));
    return QDialog::qt_metacast(_clname);
}

int LabelDefinitions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editLabelDef((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: btnEdit_clicked(); break;
        case 2: btnDelete_clicked(); break;
        case 3: btnAdd_clicked(); break;
        case 4: init(); break;
        case 5: languageChange(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
