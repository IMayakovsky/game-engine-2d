#include "main_window.h"

#include <QRegularExpression>
#include <QDebug>
#include <QPainter>

const QRegularExpression COLLIDER_PATTERN("^(\\d*)x(\\d*)$");

MainWindow::MainWindow(savesManager::SavesManager * saves_manager, QWidget *parent) : QGraphicsView(parent)
{
    _saves_manager = saves_manager;
    setWindowTitle("The Elder Scrolls 2D: Stories");
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    _max_width = screenGeometry.width();
    _max_height = screenGeometry.height();
    AddResolutions();

    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void MainWindow::ShowWindow()
{
    _saves_manager->LoadOptionsSaveValue(savesManager::OptionsSaves::FullScreen, &_isFullScreen);
    SetResolution(_saves_manager->GetOptionsSaveValue(savesManager::OptionsSaves::Resolution));
    ChangeFullScreenMode(_isFullScreen);
    show();
}

QList<QString> MainWindow::GetAllResolutions()
{
    return _resolutions;
}

QString MainWindow::GetCurrentResolution()
{
    return _current_resolusion;
}

int MainWindow::GetMaxWidth()
{
    return _max_width;
}

bool MainWindow::IsFullScreen()
{
    return _isFullScreen;
}

void MainWindow::AddResolutions()
{
    QList<QString> all_res = {"1280x720", "1280x960", "1280x1024",
                     "1440x900", "1600x900", "1680x1050", "1920x1080"};
    QRegularExpressionMatch match;
    for (QString res : all_res)
    {
        match = COLLIDER_PATTERN.match(res);
        if (match.captured(1).toInt() <= _max_width && match.captured(2).toInt() <= _max_height)
        {
            _resolutions.push_back(res);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *){}

void MainWindow::showEvent(QShowEvent *){}

void MainWindow::scrollContentsBy(int, int){}

void MainWindow::dragMoveEvent(QDragMoveEvent*){}

/*!
 * \brief MainWindow::SetResolution
 * Sets current window resolution
 * \param window_size string resolution value for set
 */
void MainWindow::SetResolution(QString window_size)
{
    QRegularExpressionMatch match = COLLIDER_PATTERN.match(window_size);

    if (!match.hasMatch() || !_resolutions.contains(window_size))
    {
        _current_resolusion = _resolutions[_resolutions.size() - 1];
        match = COLLIDER_PATTERN.match(_current_resolusion);
        match.hasMatch();
        setFixedSize(match.captured(1).toInt(), match.captured(2).toInt());
    }
    else
    {
        setFixedSize(match.captured(1).toInt(), match.captured(2).toInt());
        _current_resolusion = window_size;
    }

    _saves_manager->UpdateOptionsSaves(savesManager::OptionsSaves::Resolution, _current_resolusion);

    if (_resolutions[_resolutions.size() - 1] != window_size && _isFullScreen)
    {
        showFullScreen();
        ChangeFullScreenMode(false);
    }
}

/*!
 * \brief MainWindow::ChangeFullScreenMode
 * Changes full screen mode
 * \param status full if full screen is
 * false otherwise
 */
void MainWindow::ChangeFullScreenMode(bool status)
{
    using savesManager::OptionsSaves;

    _isFullScreen = status;

    if (status)
    {
        QString resolution = _resolutions[_resolutions.size() - 1];
        SetResolution(resolution);
        showFullScreen();
        _saves_manager->UpdateOptionsSaves(OptionsSaves::Resolution, resolution);
        _saves_manager->UpdateOptionsSaves(OptionsSaves::FullScreen, true);

    }
    else
    {
        _saves_manager->UpdateOptionsSaves(OptionsSaves::FullScreen, false);
        showNormal();
    }
}

