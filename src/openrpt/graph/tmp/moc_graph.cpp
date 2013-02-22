/****************************************************************************
** Meta object code from reading C++ file 'graph.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graph[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      24,    6,    6,    6, 0x0a,
      41,    6,    6,    6, 0x0a,
      63,    6,    6,    6, 0x0a,
      86,    6,    6,    6, 0x0a,
     104,    6,    6,    6, 0x0a,
     131,    6,    6,    6, 0x0a,
     151,    6,    6,    6, 0x0a,
     182,    6,    6,    6, 0x0a,
     206,    6,    6,    6, 0x0a,
     232,    6,    6,    6, 0x0a,
     251,    6,    6,    6, 0x0a,
     283,    6,    6,    6, 0x0a,
     308,    6,    6,    6, 0x0a,
     335,    6,    6,    6, 0x0a,
     355,    6,    6,    6, 0x0a,
     375,    6,    6,    6, 0x0a,
     392,    6,    6,    6, 0x0a,
     412,    6,    6,    6, 0x0a,
     431,  429,    6,    6, 0x0a,
     465,  462,    6,    6, 0x0a,
     493,  429,    6,    6, 0x0a,
     524,  429,    6,    6, 0x0a,
     548,    6,    6,    6, 0x0a,
     566,    6,    6,    6, 0x0a,
     585,    6,    6,    6, 0x0a,
     605,    6,    6,    6, 0x0a,
     625,    6,    6,    6, 0x0a,
     646,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graph[] = {
    "Graph\0\0setHPadding(int)\0setVPadding(int)\0"
    "setDataLabel(QString)\0setValueLabel(QString)\0"
    "setTitle(QString)\0setTitleFont(const QFont*)\0"
    "setTitleFont(QFont)\0setDataLabelFont(const QFont*)\0"
    "setDataLabelFont(QFont)\0"
    "setDataFont(const QFont*)\0setDataFont(QFont)\0"
    "setValueLabelFont(const QFont*)\0"
    "setValueLabelFont(QFont)\0"
    "setValueFont(const QFont*)\0"
    "setValueFont(QFont)\0setMinValue(double)\0"
    "setMinValue(int)\0setMaxValue(double)\0"
    "setMaxValue(int)\0,\0setReferenceLabel(int,QString)\0"
    ",,\0setSetValue(int,int,double)\0"
    "setSetColor(int,const QColor*)\0"
    "setSetColor(int,QColor)\0setDrawBars(bool)\0"
    "setDrawLines(bool)\0setDrawPoints(bool)\0"
    "setAutoMinMax(bool)\0setAutoRepaint(bool)\0"
    "clear()\0"
};

const QMetaObject Graph::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Graph,
      qt_meta_data_Graph, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graph::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graph))
        return static_cast<void*>(const_cast< Graph*>(this));
    return QWidget::qt_metacast(_clname);
}

int Graph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setHPadding((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setVPadding((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setDataLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: setValueLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: setTitleFont((*reinterpret_cast< const QFont*(*)>(_a[1]))); break;
        case 6: setTitleFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 7: setDataLabelFont((*reinterpret_cast< const QFont*(*)>(_a[1]))); break;
        case 8: setDataLabelFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 9: setDataFont((*reinterpret_cast< const QFont*(*)>(_a[1]))); break;
        case 10: setDataFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 11: setValueLabelFont((*reinterpret_cast< const QFont*(*)>(_a[1]))); break;
        case 12: setValueLabelFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 13: setValueFont((*reinterpret_cast< const QFont*(*)>(_a[1]))); break;
        case 14: setValueFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 15: setMinValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: setMinValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: setMaxValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: setMaxValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setReferenceLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 20: setSetValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 21: setSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QColor*(*)>(_a[2]))); break;
        case 22: setSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 23: setDrawBars((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: setDrawLines((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: setDrawPoints((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: setAutoMinMax((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: setAutoRepaint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: clear(); break;
        default: ;
        }
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
