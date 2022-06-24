#include "task_manager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskManager task = TaskManager::GetInstance();

    task.StartGame();

    return a.exec();
}
