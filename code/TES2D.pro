QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11
CONFIG += C++1z

RC_ICONS = ../src/main.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audio_manager.cpp \
    enums/audio_names_enum.cpp \
    enums/buttons_names_enum.cpp \
    enums/colliders_types_enum.cpp \
    enums/enemy_enum.cpp \
    enums/file_keys_enum.cpp \
    enums/saves_manager_enum.cpp \
    enums/settings_enum.cpp \
    enums/spacial_item_enum.cpp \
    enums/sprites_names_enum.cpp \
    gameLevel/arrow.cpp \
    gameLevel/checkpoint.cpp \
    gameLevel/enemy.cpp \
    gameLevel/game_level.cpp \
    gameLevel/game_objects_manager.cpp \
    gameLevel/game_objects_setter.cpp \
    gameLevel/key_controller.cpp \
    gameLevel/line_collider.cpp \
    gameLevel/physics_game_object.cpp \
    gameLevel/player.cpp \
    gameLevel/player_info.cpp \
    gameLevel/simple_game_object.cpp \
    gameLevel/spacial_item.cpp \
    game_levels_manager.cpp \
    main_window.cpp \
    saves_manager.cpp \
    ui/levels_menu.cpp \
    ui/main_menu.cpp \
    ui/settings_menu.cpp \
    utils/file_manager.cpp \
    level_manager.cpp \
    main.cpp \
    task_manager.cpp \
    ui/panel.cpp \
    utils/level_name_converter.cpp

HEADERS += \
    audio_manager.h \
    enums/audio_names_enum.h \
    enums/buttons_names_enum.h \
    enums/colliders_types_enum.h \
    enums/enemy_enum.h \
    enums/file_keys_enum.h \
    enums/saves_manager_enum.h \
    enums/settings_enum.h \
    enums/spacial_item_enum.h \
    enums/sprites_names_enum.h \
    gameLevel/arrow.h \
    gameLevel/checkpoint.h \
    gameLevel/enemy.h \
    gameLevel/game_level.h \
    gameLevel/game_objects_manager.h \
    gameLevel/game_objects_setter.h \
    gameLevel/key_controller.h \
    gameLevel/line_collider.h \
    gameLevel/physics_game_object.h \
    gameLevel/player.h \
    gameLevel/player_info.h \
    gameLevel/simple_game_object.h \
    gameLevel/spacial_item.h \
    game_levels_manager.h \
    level_manager.h \
    main_window.h \
    saves_manager.h \
    task_manager.h \
    ui/levels_menu.h \
    ui/main_menu.h \
    ui/panel.h \
    ui/settings_menu.h \
    utils/file_manager.h \
    utils/level_name_converter.h

FORMS += \
    main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=

DISTFILES += \
    ../src/assets/images/main_ico.png \
    files/style.gss \
    resources/audio/The Elder Scrolls IV Oblivion OST- King And Country 128k - BlueConvert.com.mp3 \
    resources/main_ico.png

RESOURCES += \
