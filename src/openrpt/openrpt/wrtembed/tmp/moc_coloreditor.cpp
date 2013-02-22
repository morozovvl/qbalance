/****************************************************************************
** Meta object code from reading C++ file 'coloreditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coloreditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coloreditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorEditor[] = {

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
      13,   12,   12,   12, 0x0a,
      38,   33,   12,   12, 0x0a,
      64,   60,   12,   12, 0x0a,
      88,   12,   81,   12, 0x0a,
     107,   12,   99,   12, 0x0a,
     122,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ColorEditor[] = {
    "ColorEditor\0\0_btnColor_clicked()\0name\0"
    "setColorName(QString)\0col\0setColor(QColor)\0"
    "QColor\0getColor()\0QString\0getColorName()\0"
    "languageChange()\0"
};

const QMetaObject ColorEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ColorEditor,
      qt_meta_data_ColorEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorEditor))
        return static_cast<void*>(const_cast< ColorEditor*>(this));
    if (!strcmp(_clname, "Ui::ColorEditor"))
        return static_cast< Ui::ColorEditor*>(const_cast< ColorEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int ColorEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _btnColor_clicked(); break;
        case 1: setColorName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 3: { QColor _r = getColor();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 4: { QString _r = getColorName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: languageChange(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
