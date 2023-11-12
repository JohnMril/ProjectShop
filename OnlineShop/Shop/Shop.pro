QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    DataClass/DataClass.cpp \
    DataClass/SqlDataBase.cpp \
    LogDialog.cpp \
    ModelHandler.cpp \
    Parser/ChoseSettingsDialog.cpp \
    Parser/FileSelector.cpp \
    Parser/Parser.cpp \
    Parser/ParserHolderWidget.cpp \
    Parser/ParsingDialog.cpp \
    Parser/RawDataParser/AsbisParser.cpp \
    Parser/RawDataParser/ElkoParser.cpp \
    Parser/RawDataParser/InlineParser.cpp \
    Parser/RawDataParser/LanitParser.cpp \
    Parser/RawDataParser/LogicParser.cpp \
    Parser/RawDataParser/MarvelParser.cpp \
    Parser/RawDataParser/MicsParser.cpp \
    Parser/RawDataParser/NetLabParser.cpp \
    Parser/RawDataParser/OcsParser.cpp \
    Parser/RawDataParser/ParserRawDataInteface.cpp \
    Parser/RawDataParser/ProNetParser.cpp \
    Parser/RawDataParser/RRCParser.cpp \
    Parser/RawDataParser/ResourceMediaParser.cpp \
    Parser/RawDataParser/SuperWaveParser.cpp \
    Parser/RawDataParser/TradeOnline.cpp \
    Parser/SelectedParserElementWidget.cpp \
    Parser/SelecterParsingFilesDialog.cpp \
    RequsterClass/RequestClass.cpp \
    RequsterClass/RequestClassHandler.cpp \
    SettingHandler.cpp \
    SortingsDialog/SortingDialog.cpp \
    SqlDataBase/AskToUseSettingsDialog.cpp \
    SqlDataBase/AuthorizationDialog.cpp \
    SqlDataBase/PushButtonSender.cpp \
    SqlDataBase/SenderDataDialog.cpp \
    SqlDataBase/SqlDataClassThread.cpp \
    SqlDataBase/SqlDatabseHandler.cpp \
    SqlDataBase/SqlElement.cpp \
    ViewEditorDialog/ModelViewDialog.cpp \
    ViewEditorDialog/ViewEditorDialog.cpp \
    ViewEditorDialog/ViewSelectorWidgetForm.cpp \
    WaitingDialog.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Common/EnumerationClass.hpp \
    Common/ModelStruct.hpp \
    DataClass/DataClass.hpp \
    DataClass/SqlDataBase.hpp \
    LogDialog.hpp \
    MainWindow.hpp \
    ModelHandler.hpp \
    Parser/ChoseSettingsDialog.hpp \
    Parser/FileSelector.hpp \
    Parser/Parser.hpp \
    Parser/ParserHolderWidget.hpp \
    Parser/ParsingDialog.hpp \ \
    Parser/RawDataParser/AsbisParser.hpp \
    Parser/RawDataParser/ElkoParser.hpp \
    Parser/RawDataParser/InlineParser.hpp \
    Parser/RawDataParser/LanitParser.hpp \
    Parser/RawDataParser/LogicParser.hpp \
    Parser/RawDataParser/MarvelParser.hpp \
    Parser/RawDataParser/MicsParser.hpp \
    Parser/RawDataParser/NetLabParser.hpp \
    Parser/RawDataParser/OcsParser.hpp \
    Parser/RawDataParser/ParserRawDataInteface.hpp \
    Parser/RawDataParser/ProNetParser.hpp \
    Parser/RawDataParser/RRCParser.hpp \
    Parser/RawDataParser/ResourceMediaParser.hpp \
    Parser/RawDataParser/SuperWaveParser.hpp \
    Parser/RawDataParser/TradeOnline.hpp \
    Parser/SelectedParserElementWidget.hpp \
    Parser/SelecterParsingFilesDialog.hpp \
    RequsterClass/RequestClass.hpp \
    RequsterClass/RequestClassHandler.hpp \
    SettingHandler.hpp \
    SortingsDialog/SortingDialog.hpp \ \
    SqlDataBase/AskToUseSettingsDialog.hpp \
    SqlDataBase/AuthorizationDialog.hpp \
    SqlDataBase/PushButtonSender.hpp \
    SqlDataBase/SenderDataDialog.hpp \
    SqlDataBase/SqlDataClassThread.hpp \
    SqlDataBase/SqlDatabseHandler.hpp \
    SqlDataBase/SqlElement.hpp \
    ViewEditorDialog/ModelViewDialog.hpp \
    ViewEditorDialog/ViewEditorDialog.hpp \
    ViewEditorDialog/ViewSelectorWidgetForm.hpp \
    WaitingDialog.hpp

FORMS += \
    LogDialog.ui \
    MainWindow.ui \
    Parser/ChoseSettingsDialog.ui \
    Parser/FileSelector.ui \
    Parser/ParsingDialog.ui \
    Parser/SelecterParsingFilesDialog.ui \
    RequsterClass/RequestClass.ui \
    RequsterClass/RequestClassHandler.ui \
    SortingsDialog/SortingDialog.ui \
    SqlDataBase/AskToUseSettingsDialog.ui \
    SqlDataBase/AuthorizationDialog.ui \
    SqlDataBase/SenderDataDialog.ui \
    SqlDataBase/SqlElement.ui \
    ViewEditorDialog/ModelViewDialog.ui \
    ViewEditorDialog/ViewEditorDialog.ui \
    ViewEditorDialog/ViewSelectorWidgetForm.ui \
    WaitingDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
