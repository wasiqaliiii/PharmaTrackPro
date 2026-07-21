/****************************************************************************
** Meta object code from reading C++ file 'ScannerConfigurationService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Services/ScannerConfigurationService.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScannerConfigurationService.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto PharmaTrack::ScannerConfigurationService::qt_create_metaobjectdata<qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PharmaTrack::ScannerConfigurationService",
        "configurationStarted",
        "",
        "configurationCompleted",
        "configurationFailed",
        "error",
        "scannerConfigured",
        "ScannerInfo",
        "scanner",
        "scannerDisconnected"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'configurationStarted'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'configurationCompleted'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'configurationFailed'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'scannerConfigured'
        QtMocHelpers::SignalData<void(const ScannerInfo &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Signal 'scannerDisconnected'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ScannerConfigurationService, qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PharmaTrack::ScannerConfigurationService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>.metaTypes,
    nullptr
} };

void PharmaTrack::ScannerConfigurationService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ScannerConfigurationService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->configurationStarted(); break;
        case 1: _t->configurationCompleted(); break;
        case 2: _t->configurationFailed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->scannerConfigured((*reinterpret_cast<std::add_pointer_t<ScannerInfo>>(_a[1]))); break;
        case 4: _t->scannerDisconnected(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ScannerConfigurationService::*)()>(_a, &ScannerConfigurationService::configurationStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerConfigurationService::*)()>(_a, &ScannerConfigurationService::configurationCompleted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerConfigurationService::*)(const QString & )>(_a, &ScannerConfigurationService::configurationFailed, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerConfigurationService::*)(const ScannerInfo & )>(_a, &ScannerConfigurationService::scannerConfigured, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScannerConfigurationService::*)()>(_a, &ScannerConfigurationService::scannerDisconnected, 4))
            return;
    }
}

const QMetaObject *PharmaTrack::ScannerConfigurationService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PharmaTrack::ScannerConfigurationService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PharmaTrack27ScannerConfigurationServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PharmaTrack::ScannerConfigurationService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PharmaTrack::ScannerConfigurationService::configurationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PharmaTrack::ScannerConfigurationService::configurationCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PharmaTrack::ScannerConfigurationService::configurationFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PharmaTrack::ScannerConfigurationService::scannerConfigured(const ScannerInfo & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PharmaTrack::ScannerConfigurationService::scannerDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
