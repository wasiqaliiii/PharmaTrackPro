/****************************************************************************
** Meta object code from reading C++ file 'ScannerDiscoveryService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Services/ScannerDiscoveryService.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScannerDiscoveryService.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto PharmaTrack::ScannerDiscoveryService::qt_create_metaobjectdata<qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PharmaTrack::ScannerDiscoveryService",
        "discoveryStarted",
        "",
        "discoveryFinished",
        "scannerDiscovered",
        "ScannerInfo",
        "scanner",
        "progressChanged",
        "current",
        "total",
        "errorOccurred",
        "error",
        "discoverNext"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'discoveryStarted'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'discoveryFinished'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scannerDiscovered'
        QtMocHelpers::SignalData<void(const ScannerInfo &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'progressChanged'
        QtMocHelpers::SignalData<void(int, int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 },
        }}),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Slot 'discoverNext'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ScannerDiscoveryService, qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PharmaTrack::ScannerDiscoveryService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>.metaTypes,
    nullptr
} };

void PharmaTrack::ScannerDiscoveryService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ScannerDiscoveryService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->discoveryStarted(); break;
        case 1: _t->discoveryFinished(); break;
        case 2: _t->scannerDiscovered((*reinterpret_cast<std::add_pointer_t<ScannerInfo>>(_a[1]))); break;
        case 3: _t->progressChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->discoverNext(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ScannerDiscoveryService::*)()>(_a, &ScannerDiscoveryService::discoveryStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerDiscoveryService::*)()>(_a, &ScannerDiscoveryService::discoveryFinished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerDiscoveryService::*)(const ScannerInfo & )>(_a, &ScannerDiscoveryService::scannerDiscovered, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerDiscoveryService::*)(int , int )>(_a, &ScannerDiscoveryService::progressChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerDiscoveryService::*)(const QString & )>(_a, &ScannerDiscoveryService::errorOccurred, 4))
            return;
    }
}

const QMetaObject *PharmaTrack::ScannerDiscoveryService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PharmaTrack::ScannerDiscoveryService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack23ScannerDiscoveryServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PharmaTrack::ScannerDiscoveryService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PharmaTrack::ScannerDiscoveryService::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PharmaTrack::ScannerDiscoveryService::discoveryFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PharmaTrack::ScannerDiscoveryService::scannerDiscovered(const ScannerInfo & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PharmaTrack::ScannerDiscoveryService::progressChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void PharmaTrack::ScannerDiscoveryService::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
