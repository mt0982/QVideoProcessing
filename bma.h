#ifndef BMA_H
#define BMA_H

#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QTime>
#include <QImage>

class BMA {

public:
    BMA();
    QImage getNewFrame(QImage &currentFrame, QImage &previousFrame);
    QImage calculate(int blockSize, QImage &previousFrame, QVector<QVector3D> &block);
};

#endif // BMA_H
