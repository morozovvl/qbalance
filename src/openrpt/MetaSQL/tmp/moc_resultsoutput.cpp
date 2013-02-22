/****************************************************************************
** Meta object code from reading C++ file 'resultsoutput.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../resultsoutput.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resultsoutput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResultsOutput[] = {

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
      15,   14,   14,   14, 0x0a,
      24,   22,   14,   14, 0x0a,
      50,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ResultsOutput[] = {
    "ResultsOutput\0\0copy()\0p\0"
    "createContextMenu(QPoint)\0languageChange()\0"
};

const QMetaObject ResultsOutput::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResultsOutput,
      qt_meta_data_ResultsOutput, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResultsOutput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResultsOutput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResultsOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResultsOutput))
        return static_cast<void*>(const_cast< ResultsOutput*>(this));
    if (!strcmp(_clname, "Ui::ResultsOutput"))
        return static_cast< Ui::ResultsOutput*>(const_cast< ResultsOutput*>(this));
    return QDialog::qt_metacast(_clname);
}

int ResultsOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: copy(); break;
        case 1: createContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: languageChange(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
