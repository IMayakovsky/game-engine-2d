#include "key_controller.h"
#include "task_manager.h"

#include <ui/panel.h>

/*!
 * \brief KeyController::KeyController
 * Constructor
 * \param gamelevel appropriate GameLevel
 * \param object_manager appropriate GameObjectManager
 */
KeyController::KeyController(GameLevel *gamelevel, GameObjectManager *object_manager)
{
    _gamelevel = gamelevel;
    _obj_manager = object_manager;
    SetKeysStatus();
}

void KeyController::KeyPressEvent(QKeyEvent *event)
{
    if (keys_status.contains((Qt::Key)event->key()))
        keys_status.insert((Qt::Key)event->key(), true);

}

void KeyController::KeyReleaseEvent(QKeyEvent *event)
{
    if (keys_status.contains((Qt::Key)event->key()))
        keys_status.insert((Qt::Key)event->key(), false);

    if (event->key() == Qt::Key_Escape)
    {
        TaskManager::GetInstance().GetLevelManager()->AddPanel(new Panel("pauseGamePanel/"));
    }

}

/*!
 * \brief KeyController::SetKeysStatus
 * Sets all possible keys with false value
 */
void KeyController::SetKeysStatus()
{
    keys_status.insert(Qt::Key_D, false);
    keys_status.insert(Qt::Key_A, false);
    keys_status.insert(Qt::Key_Space, false);
    keys_status.insert(Qt::Key_F, false);
    keys_status.insert(Qt::Key_E, false);
    keys_status.insert(Qt::Key_1, false);
    keys_status.insert(Qt::Key_2, false);
}

/*!
 * \brief KeyController::GetKeysStatus
 * \return status of all available keys
 */
QMap<Qt::Key, bool> KeyController::GetKeysStatus()
{
    return keys_status;
}
