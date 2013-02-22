/****************************************************************************
** Meta object code from reading C++ file 'documentscene.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../documentscene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'documentscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DocumentScene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   14,   14,   14, 0x0a,
      44,   14,   14,   14, 0x2a,
      58,   14,   14,   14, 0x0a,
      75,   14,   14,   14, 0x0a,
      96,   14,   14,   14, 0x0a,
     111,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DocumentScene[] = {
    "DocumentScene\0\0modified()\0setModified(bool)\0"
    "setModified()\0deleteSelected()\0"
    "refreshFontToolBox()\0onSelChanged()\0"
    "pageOptionsChanged()\0"
};

const QMetaObject DocumentScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_DocumentScene,
      qt_meta_data_DocumentScene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DocumentScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DocumentScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DocumentScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DocumentScene))
        return static_cast<void*>(const_cast< DocumentScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int DocumentScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: modified(); break;
        case 1: setModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setModified(); break;
        case 3: deleteSelected(); break;
        case 4: refreshFontToolBox(); break;
        case 5: onSelChanged(); break;
        case 6: pageOptionsChanged(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DocumentScene::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
