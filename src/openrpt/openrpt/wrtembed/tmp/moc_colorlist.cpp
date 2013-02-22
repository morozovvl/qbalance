/****************************************************************************
** Meta object code from reading C++ file 'colorlist.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../colorlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colorlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorList[] = {

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
      11,   10,   10,   10, 0x0a,
      34,   29,   10,   10, 0x0a,
      71,   10,   10,   10, 0x0a,
      90,   10,   10,   10, 0x0a,
     116,  111,   10,   10, 0x0a,
     144,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ColorList[] = {
    "ColorList\0\0_btnAdd_clicked()\0item\0"
    "_lbColors_dblClick(QListWidgetItem*)\0"
    "_btnEdit_clicked()\0_btnDelete_clicked()\0"
    "cmap\0init(QMap<QString,QColor>*)\0"
    "languageChange()\0"
};

const QMetaObject ColorList::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ColorList,
      qt_meta_data_ColorList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorList))
        return static_cast<void*>(const_cast< ColorList*>(this));
    if (!strcmp(_clname, "Ui::ColorList"))
        return static_cast< Ui::ColorList*>(const_cast< ColorList*>(this));
    return QDialog::qt_metacast(_clname);
}

int ColorList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _btnAdd_clicked(); break;
        case 1: _lbColors_dblClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _btnEdit_clicked(); break;
        case 3: _btnDelete_clicked(); break;
        case 4: init((*reinterpret_cast< QMap<QString,QColor>*(*)>(_a[1]))); break;
        case 5: languageChange(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
