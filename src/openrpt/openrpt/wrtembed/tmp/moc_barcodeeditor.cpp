/****************************************************************************
** Meta object code from reading C++ file 'barcodeeditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../barcodeeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'barcodeeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BarcodeEditor[] = {

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
      15,   14,   14,   14, 0x0a,
      39,   14,   14,   14, 0x0a,
      69,   14,   14,   14, 0x0a,
      94,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_BarcodeEditor[] = {
    "BarcodeEditor\0\0cbFormat_activated(int)\0"
    "sliderMaxVal_sliderMoved(int)\0"
    "cbFormat_ViewConfig(int)\0languageChange()\0"
};

const QMetaObject BarcodeEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BarcodeEditor,
      qt_meta_data_BarcodeEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BarcodeEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BarcodeEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BarcodeEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BarcodeEditor))
        return static_cast<void*>(const_cast< BarcodeEditor*>(this));
    if (!strcmp(_clname, "Ui::BarcodeEditor"))
        return static_cast< Ui::BarcodeEditor*>(const_cast< BarcodeEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int BarcodeEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cbFormat_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: sliderMaxVal_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: cbFormat_ViewConfig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: languageChange(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
