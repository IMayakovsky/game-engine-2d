#ifndef PANEL_H
#define PANEL_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLabel>

class LevelManager;

class Panel : public QGraphicsScene
{

    Q_OBJECT

public:
    Panel(QString path, QWidget *parent = nullptr);
    ~Panel();

protected:
    virtual void OnClick(QPushButton*, QString toPanel = "");
    void SetPanel();
    void InitPanel();
    bool isDeveloperMode = false;
    QString _main_path = "../src/panels/";
    QList<QPushButton *> _buttons;
    LevelManager *_levelManager;

private:

    QStringList _buttons_list;
    QStringList _text_list;
    QStringList _images_list;

    QGraphicsPixmapItem *_background_image;
    QMovie *_background_movie;
    bool isBackgroundMovie = false;
    bool isUpdateNecessary = false;
    QLabel *_background_label;
    QTimer *_update_timer;

    void AddMainInfo();
    void AddButtons();
    void AddText();
    void AddImages();
    void SetTimer();

    bool IsUpdateNecessary();

    void keyReleaseEvent(QKeyEvent *event) override;

protected slots:
    virtual void Update();
    void CheckDeveloperModeStatus();

};

#endif // PANEL_H
