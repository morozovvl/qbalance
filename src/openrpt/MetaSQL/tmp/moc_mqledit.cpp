/****************************************************************************
** Meta object code from reading C++ file 'mqledit.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mqledit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqledit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MQLEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      17,    8,    8,    8, 0x0a,
      28,    8,    8,    8, 0x0a,
      40,    8,    8,    8, 0x0a,
      62,    8,    8,    8, 0x0a,
      87,    8,    8,    8, 0x0a,
     109,  106,    8,    8, 0x0a,
     136,    8,  131,    8, 0x0a,
     157,    8,    8,    8, 0x0a,
     168,    8,    8,    8, 0x0a,
     178,    8,    8,    8, 0x0a,
     189,    8,    8,    8, 0x0a,
     201,    8,  131,    8, 0x0a,
     212,    8,    8,    8, 0x0a,
     227,  225,    8,    8, 0x0a,
     247,    8,    8,    8, 0x0a,
     259,    8,    8,    8, 0x0a,
     274,    8,    8,    8, 0x0a,
     286,    8,  131,    8, 0x0a,
     299,    8,    8,    8, 0x0a,
     312,    8,    8,    8, 0x0a,
     336,  106,    8,    8, 0x0a,
     357,  354,    8,    8, 0x0a,
     375,    8,    8,    8, 0x0a,
     393,    8,    8,    8, 0x0a,
     403,    8,    8,    8, 0x0a,
     417,    8,    8,    8, 0x09,
     434,    8,    8,    8, 0x09,

 // methods: signature, parameters, type, tag, flags
     458,    8,  450,    8, 0x02,
     490,    8,  475,    8, 0x02,
     521,    8,  509,    8, 0x02,
     548,  225,  509,    8, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_MQLEdit[] = {
    "MQLEdit\0\0clear()\0editFind()\0execQuery()\0"
    "fileDatabaseConnect()\0fileDatabaseDisconnect()\0"
    "fileDatabaseOpen()\0id\0fileDatabaseOpen(int)\0"
    "bool\0fileDatabaseSaveAs()\0fileExit()\0"
    "fileNew()\0fileOpen()\0filePrint()\0"
    "fileSave()\0fileSaveAs()\0p\0forceTestMode(bool)\0"
    "helpAbout()\0helpContents()\0helpIndex()\0"
    "isReadOnly()\0parseQuery()\0"
    "populateParameterEdit()\0sMQLSelected(int)\0"
    "ro\0setReadOnly(bool)\0showExecutedSQL()\0"
    "showLog()\0showResults()\0languageChange()\0"
    "showParamList()\0QString\0getMetaSQLText()\0"
    "ParameterEdit*\0getParameterEdit()\0"
    "QStringList\0getParamsFromMetaSQLText()\0"
    "getParamsFromMetaSQLText(QString)\0"
};

const QMetaObject MQLEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MQLEdit,
      qt_meta_data_MQLEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MQLEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MQLEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MQLEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MQLEdit))
        return static_cast<void*>(const_cast< MQLEdit*>(this));
    if (!strcmp(_clname, "Ui::MQLEdit"))
        return static_cast< Ui::MQLEdit*>(const_cast< MQLEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int MQLEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clear(); break;
        case 1: editFind(); break;
        case 2: execQuery(); break;
        case 3: fileDatabaseConnect(); break;
        case 4: fileDatabaseDisconnect(); break;
        case 5: fileDatabaseOpen(); break;
        case 6: fileDatabaseOpen((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: { bool _r = fileDatabaseSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: fileExit(); break;
        case 9: fileNew(); break;
        case 10: fileOpen(); break;
        case 11: filePrint(); break;
        case 12: { bool _r = fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: fileSaveAs(); break;
        case 14: forceTestMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: helpAbout(); break;
        case 16: helpContents(); break;
        case 17: helpIndex(); break;
        case 18: { bool _r = isReadOnly();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: parseQuery(); break;
        case 20: populateParameterEdit(); break;
        case 21: sMQLSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: setReadOnly((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: showExecutedSQL(); break;
        case 24: showLog(); break;
        case 25: showResults(); break;
        case 26: languageChange(); break;
        case 27: showParamList(); break;
        case 28: { QString _r = getMetaSQLText();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 29: { ParameterEdit* _r = getParameterEdit();
            if (_a[0]) *reinterpret_cast< ParameterEdit**>(_a[0]) = _r; }  break;
        case 30: { QStringList _r = getParamsFromMetaSQLText();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 31: { QStringList _r = getParamsFromMetaSQLText((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
