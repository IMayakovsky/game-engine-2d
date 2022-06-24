#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "saves_manager.h"

#include <QGraphicsView>
#include <QApplication>
#include <QScreen>

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(savesManager::SavesManager *, QWidget *parent = nullptr);
    void ShowWindow();
    QList<QString> GetAllResolutions();
    QString GetCurrentResolution();
    int GetMaxWidth();
    bool IsFullScreen();
    void SetResolution(QString window_size);
    void ChangeFullScreenMode(bool status);

private:
    QList<QString> _resolutions;
    QString _current_resolusion;
    savesManager::SavesManager *_saves_manager;
    int _max_width;
    int _max_height;
    bool _isFullScreen;
    void AddResolutions();
    void resizeEvent(QResizeEvent *) override;
    void showEvent(QShowEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

};
#endif // MAINWINDOW_H
