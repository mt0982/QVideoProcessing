#include "bma.h"

BMA::BMA()
{

}

void BMA::showMoveVectors(QImage &newFrame, int a1, int a2, int a3, int a4, int a5) {

    QRadialGradient gradient(a4, a5, a3, a1, a2);
    gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 0));
    gradient.setColorAt(1, QColor::fromRgbF(1, 0, 0, 1));
    QBrush brush(gradient);

    QPainter painter(&newFrame);
    painter.setPen(QPen(brush, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(a1, a2, a4, a5);
}

int BMA::absdiff(QImage &a, QImage &b) {

    int sum = 0;

    QRgb *rgb = (QRgb*)a.bits();
    QRgb *rgb2 = (QRgb*)b.bits();

    for(int i = 0; i < a.width() * a.height(); i++) {
        sum += abs(qGreen(rgb[i]) - qGreen(rgb2[i]));
        sum += abs(qBlue(rgb[i]) - qBlue(rgb2[i]));
        sum += abs(qRed(rgb[i]) - qRed(rgb2[i]));
    }

    return sum;
}

QImage BMA::area(QImage &image, QPoint a, QPoint b) {

    int w = b.y() - b.x();
    int h = a.y() - a.x();
    int rx = 0, ry = 0;
    QImage searchArea(w, h, QImage::Format_RGB32);

    for(int y = a.x(); y < a.y(); y++) {
        QRgb *rgb = (QRgb*)image.scanLine(y);
        QRgb *rgb2 = (QRgb*)searchArea.scanLine(ry);
        rx = 0;
        for(int x = b.x(); x < b.y(); x++) {
            rgb2[rx] = rgb[x];
            rx++;
        }
        ry++;
    }

    return searchArea;
}

QPoint BMA::bestResult(QImage &searchArea, QImage &currentArea) {

    QPoint best;
    unsigned areaWidth = searchArea.width();
    unsigned areaHeight = searchArea.height();
    unsigned patternWidth = currentArea.width();
    unsigned patternHeight = currentArea.height();
    int miniumum = 987645;

    for (int y = 0; y + patternHeight < areaHeight; y++) {
        for (int x = 0; x + patternWidth < areaWidth; x++) {

            QImage areaRect = area(searchArea, QPoint(y, y + patternHeight), QPoint(x, x + patternWidth));
            int min_sum = absdiff(areaRect, currentArea);

            if(min_sum < miniumum) {
                miniumum = min_sum;
                best.rx() = x;
                best.ry() = y;
            }
        }
    }

    return best;
}

void BMA::reconstruct(QImage &newFrame, QImage &optimalBlock, int yy, int xx) {

    int rx = 0, ry = 0;

    for(int y = yy; y < yy + blockSize; y++) {
        QRgb *rgb = (QRgb*)newFrame.scanLine(y);
        QRgb *rgb2 = (QRgb*)optimalBlock.scanLine(ry++);
        rx = 0;
        for(int x = xx; x < xx + blockSize; x++) {
            rgb[x] = rgb2[rx++];
        }
    }
}

QImage BMA::getNewFrame(QImage &currentFrame, QImage &previousFrame)
{
    QImage newFrame(currentFrame.width(), currentFrame.height(), QImage::Format_RGB32);

    /* Parameters */
    const unsigned rows = currentFrame.height();
    const unsigned cols = currentFrame.width();

    /* Time */
    QTime time;
    time.start();

    /* Rows */
    #pragma omp parallel for
    for (int y = 0; y < currentFrame.height(); y += blockSize) {
        /* Colums */
        for (int x = 0; x < currentFrame.width(); x += blockSize) {
            unsigned startx = (x > radius) ? x - radius : 0;
            unsigned starty = (y > radius) ? y - radius : 0;
            unsigned xshift = (x - startx);
            unsigned yshift = (y - starty);
            unsigned stopx = ((x + blockSize + radius) < cols) ? x + blockSize + radius : cols;
            unsigned stopy = ((y + blockSize + radius) < rows) ? y + blockSize + radius : rows;

            QImage searchArea = area(previousFrame, QPoint(starty, stopy), QPoint(startx, stopx));
            QImage currentArea = area(currentFrame, QPoint(y, y + blockSize), QPoint(x, x + blockSize));
            QPoint best = bestResult(searchArea, currentArea);

            best.rx() -= xshift;
            best.ry() -= yshift;

            /* Draw */
            QImage optimalBlock = area(previousFrame, QPoint(y + best.y(), y + best.y() + blockSize),
                                       QPoint(x + best.x(), x + best.x() + blockSize));

            reconstruct(newFrame, optimalBlock, y, x);

            /* Show Move Vectors */
//            if(best.y() != 0 && best.x() != 0) {
//                #pragma omp critical
//                showMoveVectors(newFrame, x, y, radius * 2, x + best.rx(), y + best.ry());
//            }
        }
    }

    /* Time Elapse */
    qDebug() << time.elapsed() / 1000.0f;

    return newFrame;
}



























