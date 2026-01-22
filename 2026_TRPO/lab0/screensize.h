#ifndef SCREENSIZE_H
#define SCREENSIZE_H



#include <QObject>
#include <QRect>

class Screensize
{
public:
    explicit Screensize(QObject *parent = nullptr);

    static QRect geometry();
    static int width();
    static int height();

private:
    static QRect s_screenGeometry;

};

#endif // SCREENSIZE_H
