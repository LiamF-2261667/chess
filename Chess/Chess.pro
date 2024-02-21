QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board/Board.cpp \
    Board/Square.cpp \
    Functionality/Movement.cpp \
    Functionality/Position.cpp \
    Game/Game.cpp \
    Game/GameLoader.cpp \
    Game/History.cpp \
    Game/Legalization.cpp \
    Pieces/Bishop.cpp \
    Pieces/King.cpp \
    Pieces/Knight.cpp \
    Pieces/Pawn.cpp \
    Pieces/Piece.cpp \
    Pieces/Queen.cpp \
    Pieces/Rook.cpp \
    Player/AI.cpp \
    Player/Player.cpp \
    UI/GraphicsBoardScene.cpp \
    UI/GraphicsPieceItem.cpp \
    UI/UIManager.cpp \
    UI/GraphicsSquareItem.cpp \
    UI/endscreenwidget.cpp \
    UI/mainwindow.cpp \
    UI/mainmenuwindow.cpp \
    UI/promotionselectionwidget.cpp \
    gamemodeselectionwidget.cpp \
    main.cpp

HEADERS += \
    Board/Board.h \
    Board/Square.h \
    Functionality/Color.h \
    Functionality/Gamemode.h \
    Functionality/Movement.h \
    Functionality/Position.h \
    Functionality/Type.h \
    Game/Game.h \
    Game/GameLoader.h \
    Game/History.h \
    Game/Legalization.h \
    Pieces/Bishop.h \
    Pieces/King.h \
    Pieces/Knight.h \
    Pieces/Pawn.h \
    Pieces/Piece.h \
    Pieces/Queen.h \
    Pieces/Rook.h \
    Player/AI.h \
    Player/Player.h \
    UI/GraphicsBoardScene.h \
    UI/GraphicsPieceItem.h \
    UI/UIManager.h \
    UI/GraphicsSquareItem.h \
    UI/endscreenwidget.h \
    UI/mainwindow.h \
    UI/mainmenuwindow.h \
    UI/promotionselectionwidget.h \
    gamemodeselectionwidget.h

FORMS += \
    UI/endscreenwidget.ui \
    UI/promotionselectionwidget.ui \
    mainwindow.ui \
    gamemodeselectionwidget.ui \
    mainmenuwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += Resources/resources.qrc
