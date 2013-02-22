/****************************************************************************
** Meta object code from reading C++ file 'labeldefinitioneditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../labeldefinitioneditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'labeldefinitioneditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LabelDefinitionEditor[] = {

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
      23,   22,   22,   22, 0x0a,
      57,   22,   43,   22, 0x0a,
      78,   22,   22,   22, 0x09,
      95,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LabelDefinitionEditor[] = {
    "LabelDefinitionEditor\0\0init(LabelSizeInfo)\0"
    "LabelSizeInfo\0getLabelDefinition()\0"
    "languageChange()\0saveLabelDef()\0"
};

const QMetaObject LabelDefinitionEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LabelDefinitionEditor,
      qt_meta_data_LabelDefinitionEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LabelDefinitionEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LabelDefinitionEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LabelDefinitionEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LabelDefinitionEditor))
        return static_cast<void*>(const_cast< LabelDefinitionEditor*>(this));
    if (!strcmp(_clname, "Ui::LabelDefinitionEditor"))
        return static_cast< Ui::LabelDefinitionEditor*>(const_cast< LabelDefinitionEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int LabelDefinitionEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: init((*reinterpret_cast< LabelSizeInfo(*)>(_a[1]))); break;
        case 1: { LabelSizeInfo _r = getLabelDefinition();
            if (_a[0]) *reinterpret_cast< LabelSizeInfo*>(_a[0]) = _r; }  break;
        case 2: languageChange(); break;
        case 3: saveLabelDef(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
