/****************************************************************************
** Meta object code from reading C++ file 'scatterdatamodifier.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scatterdatamodifier.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scatterdatamodifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScatterDataModifier_t {
    QByteArrayData data[17];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScatterDataModifier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScatterDataModifier_t qt_meta_stringdata_ScatterDataModifier = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ScatterDataModifier"
QT_MOC_LITERAL(1, 20, 24), // "backgroundEnabledChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 7), // "enabled"
QT_MOC_LITERAL(4, 54, 18), // "gridEnabledChanged"
QT_MOC_LITERAL(5, 73, 20), // "shadowQualityChanged"
QT_MOC_LITERAL(6, 94, 7), // "quality"
QT_MOC_LITERAL(7, 102, 11), // "fontChanged"
QT_MOC_LITERAL(8, 114, 4), // "font"
QT_MOC_LITERAL(9, 119, 11), // "changeStyle"
QT_MOC_LITERAL(10, 131, 5), // "style"
QT_MOC_LITERAL(11, 137, 11), // "changeTheme"
QT_MOC_LITERAL(12, 149, 5), // "theme"
QT_MOC_LITERAL(13, 155, 19), // "changeShadowQuality"
QT_MOC_LITERAL(14, 175, 28), // "shadowQualityUpdatedByVisual"
QT_MOC_LITERAL(15, 204, 31), // "QAbstract3DGraph::ShadowQuality"
QT_MOC_LITERAL(16, 236, 13) // "shadowQuality"

    },
    "ScatterDataModifier\0backgroundEnabledChanged\0"
    "\0enabled\0gridEnabledChanged\0"
    "shadowQualityChanged\0quality\0fontChanged\0"
    "font\0changeStyle\0style\0changeTheme\0"
    "theme\0changeShadowQuality\0"
    "shadowQualityUpdatedByVisual\0"
    "QAbstract3DGraph::ShadowQuality\0"
    "shadowQuality"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScatterDataModifier[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   66,    2, 0x0a /* Public */,
      11,    1,   69,    2, 0x0a /* Public */,
      13,    1,   72,    2, 0x0a /* Public */,
      14,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QFont,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void ScatterDataModifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScatterDataModifier *_t = static_cast<ScatterDataModifier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backgroundEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->gridEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->shadowQualityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->fontChanged((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 4: _t->changeStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeTheme((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->changeShadowQuality((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->shadowQualityUpdatedByVisual((*reinterpret_cast< QAbstract3DGraph::ShadowQuality(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScatterDataModifier::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScatterDataModifier::backgroundEnabledChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScatterDataModifier::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScatterDataModifier::gridEnabledChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ScatterDataModifier::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScatterDataModifier::shadowQualityChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ScatterDataModifier::*)(QFont );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScatterDataModifier::fontChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScatterDataModifier::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ScatterDataModifier.data,
    qt_meta_data_ScatterDataModifier,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScatterDataModifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScatterDataModifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScatterDataModifier.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScatterDataModifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ScatterDataModifier::backgroundEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScatterDataModifier::gridEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScatterDataModifier::shadowQualityChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScatterDataModifier::fontChanged(QFont _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
