/****************************************************************************
** Meta object code from reading C++ file 'parameteredit.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../parameteredit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parameteredit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParameterEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      23,   14,   14,   14, 0x09,
      40,   14,   14,   14, 0x09,
      50,   14,   14,   14, 0x09,
      61,   57,   14,   14, 0x09,
      75,   14,   14,   14, 0x09,
      98,   90,   14,   14, 0x09,
     119,   14,   14,   14, 0x09,
     137,   14,   14,   14, 0x09,

 // methods: signature, parameters, type, tag, flags
     170,  159,  150,   14, 0x02,
     240,  231,  150,   14, 0x22,
     287,  285,  150,   14, 0x22,
     337,   14,  323,   14, 0x02,
     365,  361,  356,   14, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ParameterEdit[] = {
    "ParameterEdit\0\0clear()\0languageChange()\0"
    "newItem()\0edit()\0row\0editItem(int)\0"
    "editItemList()\0row,col\0doubleClick(int,int)\0"
    "selectionChange()\0deleteItem()\0QDialog*\0"
    "p,parent,f\0"
    "ParameterEditDialog(ParameterEdit*,QWidget*,Qt::WindowFlags)\0"
    "p,parent\0ParameterEditDialog(ParameterEdit*,QWidget*)\0"
    "p\0ParameterEditDialog(ParameterEdit*)\0"
    "ParameterList\0getParameterList()\0bool\0"
    "doc\0setDocument(QDomDocument)\0"
};

const QMetaObject ParameterEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ParameterEdit,
      qt_meta_data_ParameterEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParameterEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParameterEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParameterEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParameterEdit))
        return static_cast<void*>(const_cast< ParameterEdit*>(this));
    if (!strcmp(_clname, "Ui::ParameterEdit"))
        return static_cast< Ui::ParameterEdit*>(const_cast< ParameterEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int ParameterEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clear(); break;
        case 1: languageChange(); break;
        case 2: newItem(); break;
        case 3: edit(); break;
        case 4: editItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: editItemList(); break;
        case 6: doubleClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: selectionChange(); break;
        case 8: deleteItem(); break;
        case 9: { QDialog* _r = ParameterEditDialog((*reinterpret_cast< ParameterEdit*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])),(*reinterpret_cast< Qt::WindowFlags(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = _r; }  break;
        case 10: { QDialog* _r = ParameterEditDialog((*reinterpret_cast< ParameterEdit*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = _r; }  break;
        case 11: { QDialog* _r = ParameterEditDialog((*reinterpret_cast< ParameterEdit*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = _r; }  break;
        case 12: { ParameterList _r = getParameterList();
            if (_a[0]) *reinterpret_cast< ParameterList*>(_a[0]) = _r; }  break;
        case 13: { bool _r = setDocument((*reinterpret_cast< const QDomDocument(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
