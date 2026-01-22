QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab0_safronov_52052
TEMPLATE = app

# Исходные файлы
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    screensize.cpp \
    center.cpp \
    matrixcalculate.cpp

# Заголовочные файлы
HEADERS += \
    mainwindow.h \
    screensize.h \
    center.h \
    matrixcalculate.h

# Формы (если используете Qt Designer)
FORMS += \
    mainwindow.ui  # если есть файл .ui

# Настройки компилятора
CONFIG += c++17
QMAKE_CXXFLAGS += -Wall -Wextra -Wno-sign-compare
