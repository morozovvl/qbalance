/****************************************************************************
** Meta object code from reading C++ file 'sectioneditor.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sectioneditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sectioneditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SectionEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      32,   14,   14,   14, 0x0a,
      50,   14,   14,   14, 0x0a,
      70,   14,   14,   14, 0x0a,
      90,   14,   14,   14, 0x0a,
     116,  112,   14,   14, 0x0a,
     145,  112,   14,   14, 0x0a,
     174,  112,   14,   14, 0x0a,
     200,  112,   14,   14, 0x0a,
     225,  112,   14,   14, 0x0a,
     250,  112,   14,   14, 0x0a,
     274,  112,   14,   14, 0x0a,
     300,  112,   14,   14, 0x0a,
     325,  112,   14,   14, 0x0a,
     350,  112,   14,   14, 0x0a,
     374,  112,   14,   14, 0x0a,
     398,  112,   14,   14, 0x0a,
     422,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SectionEditor[] = {
    "SectionEditor\0\0btnAdd_clicked()\0"
    "btnEdit_clicked()\0btnRemove_clicked()\0"
    "btnMoveUp_clicked()\0brnMoveDown_clicked()\0"
    "yes\0cbReportHeader_toggled(bool)\0"
    "cbReportFooter_toggled(bool)\0"
    "cbHeadFirst_toggled(bool)\0"
    "cbHeadLast_toggled(bool)\0"
    "cbHeadEven_toggled(bool)\0"
    "cbHeadOdd_toggled(bool)\0"
    "cbFootFirst_toggled(bool)\0"
    "cbFootLast_toggled(bool)\0"
    "cbFootEven_toggled(bool)\0"
    "cbFootOdd_toggled(bool)\0cbHeadAny_toggled(bool)\0"
    "cbFootAny_toggled(bool)\0languageChange()\0"
};

const QMetaObject SectionEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SectionEditor,
      qt_meta_data_SectionEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SectionEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SectionEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SectionEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SectionEditor))
        return static_cast<void*>(const_cast< SectionEditor*>(this));
    if (!strcmp(_clname, "Ui::SectionEditor"))
        return static_cast< Ui::SectionEditor*>(const_cast< SectionEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int SectionEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 5: cbReportHeader_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: cbReportFooter_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: cbHeadFirst_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: cbHeadLast_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: cbHeadEven_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: cbHeadOdd_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: cbFootFirst_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: cbFootLast_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: cbFootEven_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: cbFootOdd_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: cbHeadAny_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: cbFootAny_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: languageChange(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
