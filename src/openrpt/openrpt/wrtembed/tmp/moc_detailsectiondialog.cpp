/****************************************************************************
** Meta object code from reading C++ file 'detailsectiondialog.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../detailsectiondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detailsectiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DetailSectionDialog[] = {

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
      21,   20,   20,   20, 0x0a,
      38,   20,   20,   20, 0x0a,
      56,   20,   20,   20, 0x0a,
      76,   20,   20,   20, 0x0a,
      96,   20,   20,   20, 0x0a,
     118,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DetailSectionDialog[] = {
    "DetailSectionDialog\0\0btnAdd_clicked()\0"
    "btnEdit_clicked()\0btnRemove_clicked()\0"
    "btnMoveUp_clicked()\0brnMoveDown_clicked()\0"
    "languageChange()\0"
};

const QMetaObject DetailSectionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DetailSectionDialog,
      qt_meta_data_DetailSectionDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetailSectionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetailSectionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetailSectionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetailSectionDialog))
        return static_cast<void*>(const_cast< DetailSectionDialog*>(this));
    if (!strcmp(_clname, "Ui::DetailSectionDialog"))
        return static_cast< Ui::DetailSectionDialog*>(const_cast< DetailSectionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DetailSectionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: btnAdd_clicked(); break;
        case 1: btnEdit_clicked(); break;
        case 2: btnRemove_clicked(); break;
        case 3: btnMoveUp_clicked(); break;
        case 4: brnMoveDown_clicked(); break;
        case 5: languageChange(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
