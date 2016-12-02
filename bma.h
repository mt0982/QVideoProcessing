#ifndef BMA_H
#define BMA_H

#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QTime>
#include <QImage>
#include <QRadialGradient>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <omp.h>

class BMA {
private:
    const int blockSize = 20;
    const int radius = 8;

public:
    BMA();
    void showMoveVectors(QImage &newFrame, int a1, int a2, int a3, int a4, int a5);
    int absdiff(QImage &a, QImage &b);
    QImage area(QImage &image, QPoint a, QPoint b);
    QPoint bestResult(QImage &searchArea, QImage &currentArea);
    void reconstruct(QImage &newFrame, QImage &optimalBlock, int yy, int xx);
    QImage getNewFrame(QImage &currentFrame, QImage &previousFrame);
};

#endif // BMA_H
