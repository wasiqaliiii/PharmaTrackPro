/****************************************************************************
** Meta object code from reading C++ file 'VerificationService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Services/VerificationService.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VerificationService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto PharmaTrack::VerificationService::qt_create_metaobjectdata<qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PharmaTrack::VerificationService",
        "productionLoaded",
        "",
        "batchId",
        "totalCodes",
        "productionCleared",
        "codeVerified",
        "ScanLog",
        "log",
        "statisticsChanged",
        "total",
        "accepted",
        "rejected",
        "duplicate",
        "remaining"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'productionLoaded'
        QtMocHelpers::SignalData<void(const QString &, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'productionCleared'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'codeVerified'
        QtMocHelpers::SignalData<void(const ScanLog &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Signal 'statisticsChanged'
        QtMocHelpers::SignalData<void(int, int, int, int, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 }, { QMetaType::Int, 13 },
            { QMetaType::Int, 14 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VerificationService, qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PharmaTrack::VerificationService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>.metaTypes,
    nullptr
} };

void PharmaTrack::VerificationService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VerificationService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->productionLoaded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->productionCleared(); break;
        case 2: _t->codeVerified((*reinterpret_cast<std::add_pointer_t<ScanLog>>(_a[1]))); break;
        case 3: _t->statisticsChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (VerificationService::*)(const QString & , int )>(_a, &VerificationService::productionLoaded, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (VerificationService::*)()>(_a, &VerificationService::productionCleared, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (VerificationService::*)(const ScanLog & )>(_a, &VerificationService::codeVerified, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (VerificationService::*)(int , int , int , int , int )>(_a, &VerificationService::statisticsChanged, 3))
            return;
    }
}

const QMetaObject *PharmaTrack::VerificationService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PharmaTrack::VerificationService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack19VerificationServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PharmaTrack::VerificationService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PharmaTrack::VerificationService::productionLoaded(const QString & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void PharmaTrack::VerificationService::productionCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PharmaTrack::VerificationService::codeVerified(const ScanLog & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PharmaTrack::VerificationService::statisticsChanged(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4, _t5);
}
QT_WARNING_POP
