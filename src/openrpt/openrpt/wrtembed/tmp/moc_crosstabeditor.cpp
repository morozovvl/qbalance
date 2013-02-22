/****************************************************************************
** Meta object code from reading C++ file 'crosstabeditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../crosstabeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crosstabeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CrossTabEditor[] = {

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
      16,   15,   15,   15, 0x0a,
      34,   15,   15,   15, 0x09,
      51,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CrossTabEditor[] = {
    "CrossTabEditor\0\0btnFont_clicked()\0"
    "languageChange()\0on_valueQueryGroupBox_toggled(bool)\0"
};

const QMetaObject CrossTabEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CrossTabEditor,
      qt_meta_data_CrossTabEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CrossTabEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CrossTabEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CrossTabEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CrossTabEditor))
        return static_cast<void*>(const_cast< CrossTabEditor*>(this));
    if (!strcmp(_clname, "Ui::CrossTabEditor"))
        return static_cast< Ui::CrossTabEditor*>(const_cast< CrossTabEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int CrossTabEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: btnFont_clicked(); break;
        case 1: languageChange(); break;
        case 2: on_valueQueryGroupBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
