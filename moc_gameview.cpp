/****************************************************************************
** Meta object code from reading C++ file 'gameview.h'
**
** Created: Sat Dec 3 16:21:05 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gameview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x05,
      33,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,    9,    9,    9, 0x0a,
      57,    9,    9,    9, 0x0a,
      67,    9,    9,    9, 0x0a,
      80,    9,   75,    9, 0x0a,
      85,    9,   75,    9, 0x0a,
      92,    9,   75,    9, 0x0a,
      99,    9,   75,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameView[] = {
    "GameView\0\0,\0scoreupdata(int,int)\0"
    "ai_done()\0restartGame()\0ai_play()\0"
    "train()\0bool\0up()\0down()\0left()\0right()\0"
};

void GameView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameView *_t = static_cast<GameView *>(_o);
        switch (_id) {
        case 0: _t->scoreupdata((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->ai_done(); break;
        case 2: _t->restartGame(); break;
        case 3: _t->ai_play(); break;
        case 4: _t->train(); break;
        case 5: { bool _r = _t->up();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->down();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->left();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->right();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GameView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GameView,
      qt_meta_data_GameView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameView))
        return static_cast<void*>(const_cast< GameView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GameView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GameView::scoreupdata(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameView::ai_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
