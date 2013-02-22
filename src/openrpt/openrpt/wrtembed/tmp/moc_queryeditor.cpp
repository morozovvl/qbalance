/****************************************************************************
** Meta object code from reading C++ file 'queryeditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../queryeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'queryeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QueryEditor[] = {

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
      13,   12,   12,   12, 0x09,
      32,   30,   12,   12, 0x09,
      58,   12,   12,   12, 0x09,
      75,   12,   12,   12, 0x09,
     105,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QueryEditor[] = {
    "QueryEditor\0\0languageChange()\0e\0"
    "keyPressEvent(QKeyEvent*)\0mqlToggled(bool)\0"
    "groupEditTextChanged(QString)\0"
    "nameEditTextChanged(QString)\0"
};

const QMetaObject QueryEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QueryEditor,
      qt_meta_data_QueryEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QueryEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QueryEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QueryEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QueryEditor))
        return static_cast<void*>(const_cast< QueryEditor*>(this));
    if (!strcmp(_clname, "Ui::QueryEditor"))
        return static_cast< Ui::QueryEditor*>(const_cast< QueryEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int QueryEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: languageChange(); break;
        case 1: keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: mqlToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: groupEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: nameEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
