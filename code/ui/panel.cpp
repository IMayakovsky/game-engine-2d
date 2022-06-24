#include "panel.h"

#include "utils/file_manager.h"
#include "enums/buttons_names_enum.h"
#include "enums/file_keys_enum.h"
#include "task_manager.h"

#include <QFileInfo>
#include <QLineEdit>
#include <QMovie>
#include <QTimer>

/*!
 * \brief Panel::Panel
 * Constructor
 * \param path resource path
 * \param parent
 */
Panel::Panel(QString path, QWidget *parent) : QGraphicsScene(parent)
{
    _main_path += path;
    SetPanel();
}

Panel::~Panel()
{
    delete _update_timer;
    clear();
    if (isBackgroundMovie)
        delete _background_movie;
}

void Panel::SetPanel()
{
    _levelManager = TaskManager::GetInstance().GetLevelManager();
    CheckDeveloperModeStatus();
    InitPanel();
    SetTimer();
}

void Panel::InitPanel()
{
    AddMainInfo();
    AddButtons();
    AddImages();
    AddText();
}

void Panel::AddMainInfo()
{
    file::FileManager file(_main_path + "main.txt");

    QString background_src = file.GetStringValue("backgroundImage");
    if (background_src == "none")
    {
        setBackgroundBrush(QBrush(QColor(file.GetRealValue("backgroundColor"))));
        return;
    }

    QFileInfo background_info(background_src);

    if (!isDeveloperMode &&
            background_info.suffix().compare("gif") == 0)
    {

        if (!isBackgroundMovie)
        {
            _background_movie = new QMovie();
            isBackgroundMovie = true;
        }
        _background_movie->setFileName(background_info.filePath());
        _background_movie->setScaledSize(QSize(TaskManager::GetInstance().GetMainWindow()->width(),
                                   TaskManager::GetInstance().GetMainWindow()->height()));
        _background_label = new QLabel();
        _background_label->setMovie(_background_movie);
        addWidget(_background_label);
        _background_label->show();
        _background_movie->setSpeed(200);
        _background_movie->start();
    }
    else
    {
        QPixmap map(background_info.filePath());
        map = map.scaled(TaskManager::GetInstance().GetMainWindow()->width(), TaskManager::GetInstance().GetMainWindow()->height());
        _background_image = new QGraphicsPixmapItem();
         _background_image->setPixmap(map);
        addItem(_background_image);
    }
}

void Panel::AddButtons()
{
    file::FileManager file(_main_path + "buttons.txt");

    _buttons_list = file.GetDataList();
    _buttons.clear();

    while (file.SwitchOnNextData())
    {
        using namespace file;
        QPushButton *but = new QPushButton();
        but->setText(file.GetStringValue(FileKeys::Text));
        but->setObjectName(file.GetStringValue(FileKeys::Name));
        but->setFixedSize(file.GetByWidthRatio(FileKeys::Width),
                          file.GetByHeightRatio(FileKeys::Height));
        but->move(file.GetByWidthRatio(FileKeys::X),
                  file.GetByHeightRatio(FileKeys::Y));
        but->setStyleSheet("background-color: #2B2B2B; color: white");
        QFont font = file.GetFont();
        but->setFont(QFont(font.family(), font.pointSize() + 1));
        QString switchTo = "";
        if (buttons::GetName(but->objectName()) == buttons::ButtonsNames::SwitchPanel)
        {
            switchTo = file.GetStringValue(FileKeys::SwitchTo);
        }
        connect(but, &QPushButton::clicked, this, [=](){ OnClick(but, switchTo); });
        addWidget(but);
        _buttons.push_back(but);
    }
}

void Panel::AddText()
{
    file::FileManager file(_main_path + "text.txt");

    _text_list = file.GetDataList();

    while (file.SwitchOnNextData())
    {
        using namespace file;

        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(file.GetStringValue(FileKeys::Name));
        QString font_style = file.GetStringValue("fontStyle");
        QString font_color = "color: " + file.GetStringValue("color") + ";";
        text->setFont(file.GetFont());
        if (font_style == "Italic")
            text->font().setItalic(true);
        else if (font_style == "Bold")
            text->font().setBold(true);
        text->setBrush(QBrush(QColor(file.GetStringValue("color"))));
        text->setPos(file.GetByWidthRatio(FileKeys::X),
                     file.GetByHeightRatio(FileKeys::Y));
        addItem(text);
    }
}

void Panel::AddImages()
{
    file::FileManager file(_main_path + "images.txt");

    _images_list = file.GetDataList();

    while (file.SwitchOnNextData())
    {
        using namespace file;

        QGraphicsPixmapItem *image = new QGraphicsPixmapItem("../" + file.GetStringValue(FileKeys::Image));
        image->setPixmap(image->pixmap().scaled(file.GetByWidthRatio(FileKeys::Width),
                                       file.GetByHeightRatio(FileKeys::Height)));
        image->setPos(file.GetByWidthRatio(FileKeys::X), file.GetByHeightRatio(FileKeys::Y));
        addItem(image);
    }
}

void Panel::SetTimer()
{
    _update_timer = new QTimer(this);
    _update_timer->setInterval(500);
    connect(_update_timer, SIGNAL(timeout()), this, SLOT(CheckDeveloperModeStatus()));
    _update_timer->start();
}

/*!
 * \brief Panel::IsUpdateNecessary
 * \return true if some resources has been changed
 * and scene must update, false otherwise
 */
bool Panel::IsUpdateNecessary()
{
    if ((_buttons_list != file::FileManager(_main_path + "buttons.txt").GetDataList())
            || (_text_list != file::FileManager(_main_path + "text.txt").GetDataList())
            || (_images_list != file::FileManager(_main_path + "images.txt").GetDataList()))
    {
        return true;
    }

    return false;
}

/*!
 * \brief Panel::OnClick
 * Onclick event for all buttons
 * \param but button
 * \param switchTo resource string on switching scene
 * if the button changes the scene
 */
void Panel::OnClick(QPushButton *but, QString switchTo)
{
    using namespace buttons;

    ButtonsNames name = GetName(but->objectName());

    switch (name)
    {
        case ButtonsNames::SwitchPanel:
            _levelManager->AddPanel(new Panel(switchTo));
            break;
        case ButtonsNames::ToBack:
            _levelManager->RemovePanel();
            break;
        case ButtonsNames::ToMainMenu:
            _levelManager->LoadMainMenu();
            break;
        default:
            break;
    }
}

void Panel::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            _levelManager->RemovePanel();
            break;
    }
}

void Panel::Update()
{
    clear();
    if (isBackgroundMovie)
    {
        isBackgroundMovie = false;
        delete _background_movie;
    }
    InitPanel();
}

void Panel::CheckDeveloperModeStatus()
{
    if (TaskManager::GetInstance().GetDeveloperModeStatus())
    {
        isDeveloperMode = true;
        if (IsUpdateNecessary())
            Update();
    }
    else if (isDeveloperMode)
    {
       isDeveloperMode = false;
       Update();
    }

}


