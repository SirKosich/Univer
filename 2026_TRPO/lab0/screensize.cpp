#include "screensize.h"
#include <QGuiApplication>
#include <QScreen>

QRect Screensize::s_screenGeometry = QRect();

QRect Screensize::geometry(){
    if (s_screenGeometry.isNull()){
        QScreen *screen = QGuiApplication::primaryScreen();

        if (screen){
            s_screenGeometry = screen -> geometry();
        }
    }
    return s_screenGeometry;
}
int Screensize::width(){
    return geometry().width();
}

int Screensize::height(){
    return geometry().height();
}
