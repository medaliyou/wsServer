/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Server_t {
    QByteArrayData data[20];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Server_t qt_meta_stringdata_Server = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Server"
QT_MOC_LITERAL(1, 7, 10), // "logMessage"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "QWebSocket*"
QT_MOC_LITERAL(4, 31, 7), // "pSender"
QT_MOC_LITERAL(5, 39, 7), // "message"
QT_MOC_LITERAL(6, 47, 14), // "logTransaction"
QT_MOC_LITERAL(7, 62, 4), // "JSON"
QT_MOC_LITERAL(8, 67, 7), // "strJSON"
QT_MOC_LITERAL(9, 75, 20), // "initiateSecureServer"
QT_MOC_LITERAL(10, 96, 17), // "QWebSocketServer*"
QT_MOC_LITERAL(11, 114, 23), // "initiateNonSecureServer"
QT_MOC_LITERAL(12, 138, 21), // "prepareJSONfromString"
QT_MOC_LITERAL(13, 160, 15), // "onNewConnection"
QT_MOC_LITERAL(14, 176, 14), // "processMessage"
QT_MOC_LITERAL(15, 191, 11), // "onSslErrors"
QT_MOC_LITERAL(16, 203, 16), // "QList<QSslError>"
QT_MOC_LITERAL(17, 220, 6), // "errors"
QT_MOC_LITERAL(18, 227, 18), // "socketDisconnected"
QT_MOC_LITERAL(19, 246, 19) // "currentClientsCount"

    },
    "Server\0logMessage\0\0QWebSocket*\0pSender\0"
    "message\0logTransaction\0JSON\0strJSON\0"
    "initiateSecureServer\0QWebSocketServer*\0"
    "initiateNonSecureServer\0prepareJSONfromString\0"
    "onNewConnection\0processMessage\0"
    "onSslErrors\0QList<QSslError>\0errors\0"
    "socketDisconnected\0currentClientsCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x08 /* Private */,
       6,    2,   74,    2, 0x08 /* Private */,
       6,    2,   79,    2, 0x08 /* Private */,
       9,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    1,   86,    2, 0x08 /* Private */,
      13,    0,   89,    2, 0x08 /* Private */,
      14,    1,   90,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,
      18,    0,   96,    2, 0x08 /* Private */,
      19,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QJsonObject,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    8,
    0x80000000 | 10,
    0x80000000 | 10,
    QMetaType::QJsonObject, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Server *_t = static_cast<Server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logMessage((*reinterpret_cast< QWebSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->logTransaction((*reinterpret_cast< QWebSocket*(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 2: _t->logTransaction((*reinterpret_cast< QWebSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: { QWebSocketServer* _r = _t->initiateSecureServer();
            if (_a[0]) *reinterpret_cast< QWebSocketServer**>(_a[0]) = std::move(_r); }  break;
        case 4: { QWebSocketServer* _r = _t->initiateNonSecureServer();
            if (_a[0]) *reinterpret_cast< QWebSocketServer**>(_a[0]) = std::move(_r); }  break;
        case 5: { QJsonObject _r = _t->prepareJSONfromString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QJsonObject*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->onNewConnection(); break;
        case 7: _t->processMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->onSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 9: _t->socketDisconnected(); break;
        case 10: { int _r = _t->currentClientsCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    }
}

const QMetaObject Server::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Server.data,
      qt_meta_data_Server,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Server.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
