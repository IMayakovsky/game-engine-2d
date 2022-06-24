#ifndef KEY_CONTROLER_H
#define KEY_CONTROLER_H

class GameLevel;

#include <QKeyEvent>

#include "game_objects_manager.h"

class KeyController
{

public:
    KeyController(GameLevel *, GameObjectManager *);
    void KeyPressEvent(QKeyEvent *event);
    void KeyReleaseEvent(QKeyEvent *event);
    QMap<Qt::Key, bool> GetKeysStatus();
    void SetKeysStatus();

private:
    GameLevel *_gamelevel;
    GameObjectManager *_obj_manager;
    QMap<Qt::Key, bool> keys_status;






};

#endif // KEY_CONTROLER_H
