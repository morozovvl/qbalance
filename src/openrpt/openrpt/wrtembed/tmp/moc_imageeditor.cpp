/****************************************************************************
** Meta object code from reading C++ file 'imageeditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imageeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageEditor[] = {

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
      17,   13,   12,   12, 0x0a,
      48,   12,   40,   12, 0x0a,
      67,   63,   12,   12, 0x0a,
      89,   12,   40,   12, 0x0a,
     104,   12,   99,   12, 0x0a,
     117,  115,   12,   12, 0x0a,
     134,   13,   12,   12, 0x0a,
     150,   12,   12,   12, 0x0a,
     168,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ImageEditor[] = {
    "ImageEditor\0\0yes\0cbStatic_toggled(bool)\0"
    "QString\0getImageData()\0dat\0"
    "setImageData(QString)\0getMode()\0bool\0"
    "isInline()\0m\0setMode(QString)\0"
    "setInline(bool)\0btnLoad_clicked()\0"
    "languageChange()\0"
};

const QMetaObject ImageEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImageEditor,
      qt_meta_data_ImageEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEditor))
        return static_cast<void*>(const_cast< ImageEditor*>(this));
    if (!strcmp(_clname, "Ui::ImageEditor"))
        return static_cast< Ui::ImageEditor*>(const_cast< ImageEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int ImageEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cbStatic_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: { QString _r = getImageData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: setImageData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { QString _r = getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { bool _r = isInline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setInline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: btnLoad_clicked(); break;
        case 8: languageChange(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
