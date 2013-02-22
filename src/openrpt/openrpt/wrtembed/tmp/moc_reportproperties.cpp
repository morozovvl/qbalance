/****************************************************************************
** Meta object code from reading C++ file 'reportproperties.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../reportproperties.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportProperties[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   17,   18,   17, 0x0a,
      49,   17,   18,   17, 0x0a,
      65,   17,   18,   17, 0x0a,
      86,   82,   17,   17, 0x0a,
     116,   82,   17,   17, 0x0a,
     139,   82,   17,   17, 0x0a,
     167,   17,  163,   17, 0x0a,
     191,  189,   17,   17, 0x0a,
     220,  216,   17,   17, 0x0a,
     243,   17,  237,   17, 0x0a,
     257,  255,   17,   17, 0x0a,
     285,   17,  280,   17, 0x0a,
     304,   17,  280,   17, 0x0a,
     321,  255,   17,   17, 0x0a,
     343,   17,   18,   17, 0x0a,
     355,   82,   17,   17, 0x0a,
     374,   82,   17,   17, 0x0a,
     395,   17,   18,   17, 0x0a,
     419,  409,   17,   17, 0x0a,
     456,   17,   18,   17, 0x0a,
     469,   17,   18,   17, 0x0a,
     483,   82,   17,   17, 0x0a,
     504,   17,   18,   17, 0x0a,
     517,  409,   17,   17, 0x0a,
     554,   17,  163,   17, 0x0a,
     569,  189,   17,   17, 0x0a,
     587,   17,  280,   17, 0x0a,
     601,  255,   17,   17, 0x0a,
     620,   17,  280,   17, 0x0a,
     633,  255,   17,   17, 0x0a,
     651,   17,   18,   17, 0x0a,
     671,  669,   17,   17, 0x0a,
     696,   17,   18,   17, 0x0a,
     717,  713,   17,   17, 0x0a,
     743,  741,   17,   17, 0x0a,
     759,   17,  163,   17, 0x0a,
     772,   17,  163,   17, 0x0a,
     787,   17,  163,   17, 0x0a,
     802,   17,  163,   17, 0x0a,
     821,   17,  163,   17, 0x0a,
     841,  189,   17,   17, 0x0a,
     859,  189,   17,   17, 0x0a,
     877,  189,   17,   17, 0x0a,
     899,  189,   17,   17, 0x0a,
     922,   17,   17,   17, 0x09,
     939,   17,   17,   17, 0x09,
     954,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ReportProperties[] = {
    "ReportProperties\0\0QString\0"
    "getReportDescription()\0getReportName()\0"
    "getReportTitle()\0str\0setReportDescription(QString)\0"
    "setReportName(QString)\0setReportTitle(QString)\0"
    "int\0getWatermarkOpacity()\0i\0"
    "setWatermarkOpacity(int)\0fnt\0"
    "setWmFont(QFont)\0QFont\0getWmFont()\0b\0"
    "SetUseBestWMFont(bool)\0bool\0"
    "getUseBestWmFont()\0isWmTextStatic()\0"
    "setWmTextStatic(bool)\0getWmText()\0"
    "setWmText(QString)\0setWmColumn(QString)\0"
    "getWmColumn()\0qsl,query\0"
    "setWmQuery(QuerySourceList*,QString)\0"
    "getWmQuery()\0getBgColumn()\0"
    "setBgColumn(QString)\0getBgQuery()\0"
    "setBgQuery(QuerySourceList*,QString)\0"
    "getBgOpacity()\0setBgOpacity(int)\0"
    "isBgEnabled()\0setBgEnabled(bool)\0"
    "isBgStatic()\0setBgStatic(bool)\0"
    "getBgResizeMode()\0m\0setBgResizeMode(QString)\0"
    "getBgImageData()\0dat\0setBgImageData(QString)\0"
    "f\0setBgAlign(int)\0getBgAlign()\0"
    "getBgBoundsX()\0getBgBoundsY()\0"
    "getBgBoundsWidth()\0getBgBoundsHeight()\0"
    "setBgBoundsX(int)\0setBgBoundsY(int)\0"
    "setBgBoundsWidth(int)\0setBgBoundsHeight(int)\0"
    "languageChange()\0changeWmFont()\0"
    "sLoadBgImage()\0"
};

const QMetaObject ReportProperties::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReportProperties,
      qt_meta_data_ReportProperties, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportProperties::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportProperties))
        return static_cast<void*>(const_cast< ReportProperties*>(this));
    if (!strcmp(_clname, "Ui::ReportProperties"))
        return static_cast< Ui::ReportProperties*>(const_cast< ReportProperties*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReportProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = getReportDescription();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = getReportName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = getReportTitle();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: setReportDescription((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: setReportName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: setReportTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { int _r = getWatermarkOpacity();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: setWatermarkOpacity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setWmFont((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 9: { QFont _r = getWmFont();
            if (_a[0]) *reinterpret_cast< QFont*>(_a[0]) = _r; }  break;
        case 10: SetUseBestWMFont((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { bool _r = getUseBestWmFont();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = isWmTextStatic();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: setWmTextStatic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: { QString _r = getWmText();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: setWmText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: setWmColumn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: { QString _r = getWmColumn();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: setWmQuery((*reinterpret_cast< QuerySourceList*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: { QString _r = getWmQuery();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: { QString _r = getBgColumn();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: setBgColumn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: { QString _r = getBgQuery();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 23: setBgQuery((*reinterpret_cast< QuerySourceList*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: { int _r = getBgOpacity();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: setBgOpacity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: { bool _r = isBgEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: setBgEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: { bool _r = isBgStatic();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 29: setBgStatic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: { QString _r = getBgResizeMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 31: setBgResizeMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: { QString _r = getBgImageData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 33: setBgImageData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: setBgAlign((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: { int _r = getBgAlign();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 36: { int _r = getBgBoundsX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 37: { int _r = getBgBoundsY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 38: { int _r = getBgBoundsWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 39: { int _r = getBgBoundsHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 40: setBgBoundsX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: setBgBoundsY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: setBgBoundsWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: setBgBoundsHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: languageChange(); break;
        case 45: changeWmFont(); break;
        case 46: sLoadBgImage(); break;
        default: ;
        }
        _id -= 47;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
