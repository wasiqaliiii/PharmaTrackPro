/****************************************************************************
** Meta object code from reading C++ file 'ScannerService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Services/ScannerService.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScannerService.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto PharmaTrack::ScannerService::qt_create_metaobjectdata<qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PharmaTrack::ScannerService",
        "scannerConnected",
        "",
        "scannerDisconnected",
        "scannerError",
        "error",
        "batchLoaded",
        "batchId",
        "batchUnloaded",
        "scanStarted",
        "scanStopped",
        "qrScanned",
        "serial",
        "ScanResult",
        "result",
        "codeVerified",
        "ScanLog",
        "log",
        "statisticsChanged",
        "total",
        "accepted",
        "rejected",
        "duplicate",
        "remaining",
        "processQr",
        "qr"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'scannerConnected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scannerDisconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scannerError'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'batchLoaded'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'batchUnloaded'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scanStarted'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scanStopped'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'qrScanned'
        QtMocHelpers::SignalData<void(const QString &, ScanResult)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 }, { 0x80000000 | 13, 14 },
        }}),
        // Signal 'codeVerified'
        QtMocHelpers::SignalData<void(const ScanLog &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Signal 'statisticsChanged'
        QtMocHelpers::SignalData<void(int, int, int, int, int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 }, { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { QMetaType::Int, 22 },
            { QMetaType::Int, 23 },
        }}),
        // Slot 'processQr'
        QtMocHelpers::SlotData<void(const QString &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ScannerService, qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PharmaTrack::ScannerService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>.metaTypes,
    nullptr
} };

void PharmaTrack::ScannerService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ScannerService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->scannerConnected(); break;
        case 1: _t->scannerDisconnected(); break;
        case 2: _t->scannerError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->batchLoaded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->batchUnloaded(); break;
        case 5: _t->scanStarted(); break;
        case 6: _t->scanStopped(); break;
        case 7: _t->qrScanned((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<ScanResult>>(_a[2]))); break;
        case 8: _t->codeVerified((*reinterpret_cast<std::add_pointer_t<ScanLog>>(_a[1]))); break;
        case 9: _t->statisticsChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5]))); break;
        case 10: _t->processQr((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)()>(_a, &ScannerService::scannerConnected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)()>(_a, &ScannerService::scannerDisconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)(const QString & )>(_a, &ScannerService::scannerError, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)(const QString & )>(_a, &ScannerService::batchLoaded, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)()>(_a, &ScannerService::batchUnloaded, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)()>(_a, &ScannerService::scanStarted, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)()>(_a, &ScannerService::scanStopped, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)(const QString & , ScanResult )>(_a, &ScannerService::qrScanned, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)(const ScanLog & )>(_a, &ScannerService::codeVerified, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerService::*)(int , int , int , int , int )>(_a, &ScannerService::statisticsChanged, 9))
            return;
    }
}

const QMetaObject *PharmaTrack::ScannerService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PharmaTrack::ScannerService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack14ScannerServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PharmaTrack::ScannerService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PharmaTrack::ScannerService::scannerConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PharmaTrack::ScannerService::scannerDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PharmaTrack::ScannerService::scannerError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PharmaTrack::ScannerService::batchLoaded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PharmaTrack::ScannerService::batchUnloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PharmaTrack::ScannerService::scanStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PharmaTrack::ScannerService::scanStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PharmaTrack::ScannerService::qrScanned(const QString & _t1, ScanResult _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void PharmaTrack::ScannerService::codeVerified(const ScanLog & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void PharmaTrack::ScannerService::statisticsChanged(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2, _t3, _t4, _t5);
}
QT_WARNING_POP
