/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[45];
    char stringdata0[913];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_sendButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 28), // "on_runMacTableButton_clicked"
QT_MOC_LITERAL(4, 63, 9), // "sendFrame"
QT_MOC_LITERAL(5, 73, 19), // "macAddressTableTest"
QT_MOC_LITERAL(6, 93, 18), // "updateIPv4Checksum"
QT_MOC_LITERAL(7, 112, 13), // "updateHistory"
QT_MOC_LITERAL(8, 126, 1), // "s"
QT_MOC_LITERAL(9, 128, 9), // "L3Helper*"
QT_MOC_LITERAL(10, 138, 2), // "l3"
QT_MOC_LITERAL(11, 141, 9), // "L2Helper*"
QT_MOC_LITERAL(12, 151, 2), // "l2"
QT_MOC_LITERAL(13, 154, 6), // "l3Flag"
QT_MOC_LITERAL(14, 161, 6), // "l2Flag"
QT_MOC_LITERAL(15, 168, 17), // "saveHistoryToFile"
QT_MOC_LITERAL(16, 186, 8), // "fileName"
QT_MOC_LITERAL(17, 195, 19), // "loadHistoryFromFile"
QT_MOC_LITERAL(18, 215, 20), // "loadFrameFromHistory"
QT_MOC_LITERAL(19, 236, 5), // "index"
QT_MOC_LITERAL(20, 242, 14), // "updateFrameGUI"
QT_MOC_LITERAL(21, 257, 16), // "getNetInterfaces"
QT_MOC_LITERAL(22, 274, 13), // "testTableView"
QT_MOC_LITERAL(23, 288, 28), // "on_l2PayloadCheckBox_clicked"
QT_MOC_LITERAL(24, 317, 7), // "checked"
QT_MOC_LITERAL(25, 325, 30), // "on_autoComputeCheckBox_clicked"
QT_MOC_LITERAL(26, 356, 26), // "on_verEdit_editingFinished"
QT_MOC_LITERAL(27, 383, 26), // "on_ihlEdit_editingFinished"
QT_MOC_LITERAL(28, 410, 27), // "on_dscpEdit_editingFinished"
QT_MOC_LITERAL(29, 438, 26), // "on_ecnEdit_editingFinished"
QT_MOC_LITERAL(30, 465, 32), // "on_totLengthEdit_editingFinished"
QT_MOC_LITERAL(31, 498, 37), // "on_identificationEdit_editing..."
QT_MOC_LITERAL(32, 536, 28), // "on_flagsEdit_editingFinished"
QT_MOC_LITERAL(33, 565, 33), // "on_fragOffsetEdit_editingFini..."
QT_MOC_LITERAL(34, 599, 26), // "on_ttlEdit_editingFinished"
QT_MOC_LITERAL(35, 626, 31), // "on_protocolEdit_editingFinished"
QT_MOC_LITERAL(36, 658, 31), // "on_checksumEdit_editingFinished"
QT_MOC_LITERAL(37, 690, 28), // "on_srcIPEdit_editingFinished"
QT_MOC_LITERAL(38, 719, 28), // "on_dstIPEdit_editingFinished"
QT_MOC_LITERAL(39, 748, 24), // "on_dot1qCheckBox_clicked"
QT_MOC_LITERAL(40, 773, 28), // "on_l3PayloadCheckBox_clicked"
QT_MOC_LITERAL(41, 802, 21), // "on_loadButton_clicked"
QT_MOC_LITERAL(42, 824, 31), // "on_actionSave_History_triggered"
QT_MOC_LITERAL(43, 856, 25), // "on_repeatCheckBox_clicked"
QT_MOC_LITERAL(44, 882, 30) // "on_repeatIndefCheckBox_clicked"

    },
    "MainWindow\0on_sendButton_clicked\0\0"
    "on_runMacTableButton_clicked\0sendFrame\0"
    "macAddressTableTest\0updateIPv4Checksum\0"
    "updateHistory\0s\0L3Helper*\0l3\0L2Helper*\0"
    "l2\0l3Flag\0l2Flag\0saveHistoryToFile\0"
    "fileName\0loadHistoryFromFile\0"
    "loadFrameFromHistory\0index\0updateFrameGUI\0"
    "getNetInterfaces\0testTableView\0"
    "on_l2PayloadCheckBox_clicked\0checked\0"
    "on_autoComputeCheckBox_clicked\0"
    "on_verEdit_editingFinished\0"
    "on_ihlEdit_editingFinished\0"
    "on_dscpEdit_editingFinished\0"
    "on_ecnEdit_editingFinished\0"
    "on_totLengthEdit_editingFinished\0"
    "on_identificationEdit_editingFinished\0"
    "on_flagsEdit_editingFinished\0"
    "on_fragOffsetEdit_editingFinished\0"
    "on_ttlEdit_editingFinished\0"
    "on_protocolEdit_editingFinished\0"
    "on_checksumEdit_editingFinished\0"
    "on_srcIPEdit_editingFinished\0"
    "on_dstIPEdit_editingFinished\0"
    "on_dot1qCheckBox_clicked\0"
    "on_l3PayloadCheckBox_clicked\0"
    "on_loadButton_clicked\0"
    "on_actionSave_History_triggered\0"
    "on_repeatCheckBox_clicked\0"
    "on_repeatIndefCheckBox_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  179,    2, 0x08 /* Private */,
       3,    0,  180,    2, 0x08 /* Private */,
       4,    0,  181,    2, 0x08 /* Private */,
       5,    0,  182,    2, 0x08 /* Private */,
       6,    0,  183,    2, 0x08 /* Private */,
       7,    5,  184,    2, 0x08 /* Private */,
      15,    1,  195,    2, 0x08 /* Private */,
      17,    1,  198,    2, 0x08 /* Private */,
      18,    1,  201,    2, 0x08 /* Private */,
      20,    4,  204,    2, 0x08 /* Private */,
      21,    0,  213,    2, 0x08 /* Private */,
      22,    0,  214,    2, 0x08 /* Private */,
      23,    1,  215,    2, 0x08 /* Private */,
      25,    1,  218,    2, 0x08 /* Private */,
      26,    0,  221,    2, 0x08 /* Private */,
      27,    0,  222,    2, 0x08 /* Private */,
      28,    0,  223,    2, 0x08 /* Private */,
      29,    0,  224,    2, 0x08 /* Private */,
      30,    0,  225,    2, 0x08 /* Private */,
      31,    0,  226,    2, 0x08 /* Private */,
      32,    0,  227,    2, 0x08 /* Private */,
      33,    0,  228,    2, 0x08 /* Private */,
      34,    0,  229,    2, 0x08 /* Private */,
      35,    0,  230,    2, 0x08 /* Private */,
      36,    0,  231,    2, 0x08 /* Private */,
      37,    0,  232,    2, 0x08 /* Private */,
      38,    0,  233,    2, 0x08 /* Private */,
      39,    1,  234,    2, 0x08 /* Private */,
      40,    1,  237,    2, 0x08 /* Private */,
      41,    0,  240,    2, 0x08 /* Private */,
      42,    0,  241,    2, 0x08 /* Private */,
      43,    1,  242,    2, 0x08 /* Private */,
      44,    1,  245,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9, 0x80000000 | 11, QMetaType::Bool, QMetaType::Bool,    8,   10,   12,   13,   14,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::Bool, QMetaType::Int,   19,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, QMetaType::Bool, QMetaType::Bool,   10,   12,   13,   14,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_sendButton_clicked(); break;
        case 1: _t->on_runMacTableButton_clicked(); break;
        case 2: _t->sendFrame(); break;
        case 3: _t->macAddressTableTest(); break;
        case 4: _t->updateIPv4Checksum(); break;
        case 5: _t->updateHistory((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< L3Helper*(*)>(_a[2])),(*reinterpret_cast< L2Helper*(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 6: { bool _r = _t->saveHistoryToFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->loadHistoryFromFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->loadFrameFromHistory((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->updateFrameGUI((*reinterpret_cast< L3Helper*(*)>(_a[1])),(*reinterpret_cast< L2Helper*(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 10: { bool _r = _t->getNetInterfaces();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->testTableView(); break;
        case 12: _t->on_l2PayloadCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_autoComputeCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_verEdit_editingFinished(); break;
        case 15: _t->on_ihlEdit_editingFinished(); break;
        case 16: _t->on_dscpEdit_editingFinished(); break;
        case 17: _t->on_ecnEdit_editingFinished(); break;
        case 18: _t->on_totLengthEdit_editingFinished(); break;
        case 19: _t->on_identificationEdit_editingFinished(); break;
        case 20: _t->on_flagsEdit_editingFinished(); break;
        case 21: _t->on_fragOffsetEdit_editingFinished(); break;
        case 22: _t->on_ttlEdit_editingFinished(); break;
        case 23: _t->on_protocolEdit_editingFinished(); break;
        case 24: _t->on_checksumEdit_editingFinished(); break;
        case 25: _t->on_srcIPEdit_editingFinished(); break;
        case 26: _t->on_dstIPEdit_editingFinished(); break;
        case 27: _t->on_dot1qCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_l3PayloadCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->on_loadButton_clicked(); break;
        case 30: _t->on_actionSave_History_triggered(); break;
        case 31: _t->on_repeatCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->on_repeatIndefCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
