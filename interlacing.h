#ifndef INTERLACING_H
#define INTERLACING_H

#include <QImage>

class Interlacing {
private:
    int frameNumber;

public:
    Interlacing();
    QImage odd(QImage &frame);
    QImage even(QImage &frame);
    QImage process(QImage &frame);
};

#endif // INTERLACING_H
