/****************************************************************************
** Meta object code from reading C++ file 'patheditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../patheditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patheditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PathEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x09,
      49,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PathEditor[] = {
    "PathEditor\0\0_btnColor_clicked()\0"
    "languageChange()\0accept()\0"
};

const QMetaObject PathEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PathEditor,
      qt_meta_data_PathEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PathEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PathEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PathEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PathEditor))
        return static_cast<void*>(const_cast< PathEditor*>(this));
    if (!strcmp(_clname, "Ui::PathEditor"))
        return static_cast< Ui::PathEditor*>(const_cast< PathEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int PathEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _btnColor_clicked(); break;
        case 1: languageChange(); break;
        case 2: accept(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
