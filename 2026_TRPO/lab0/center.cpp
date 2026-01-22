#include <QtGlobal>
#include "screensize.h"
#include "center.h"
#include <QPoint>

int min_x = 300;
int min_y = 300;
QPoint coord;

QPoint Centering(){
    int center_x = qMax(0, (Screensize::width() - min_x) / 2);
    int center_y = qMax(0, (Screensize::height() - min_y) / 2);

    return QPoint(center_x, center_y);
}
