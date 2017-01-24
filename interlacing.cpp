#include "interlacing.h"

Interlacing::Interlacing(): frameNumber(0)
{

}

QImage Interlacing::odd(QImage &frame) {

    QImage temporary(frame.width(), frame.height(), QImage::Format_RGB32);

    for (int y = 1; y < frame.height(); y += 2) {

        QRgb *line = (QRgb*)frame.scanLine(y);
        QRgb *tLine = (QRgb*)temporary.scanLine(y);

        for (int x = 0; x < frame.width(); ++x) {
            tLine[x] = line[x];
        }
    }

    return temporary;
}

QImage Interlacing::even(QImage &frame) {

    QImage temporary(frame.width(), frame.height(), QImage::Format_RGB32);

    for (int y = 0; y < frame.height(); y += 2) {

        QRgb *line = (QRgb*)frame.scanLine(y);
        QRgb *tLine = (QRgb*)temporary.scanLine(y);

        for (int x = 0; x < frame.width(); ++x) {
            tLine[x] = line[x];
        }
    }

    return temporary;
}

QImage Interlacing::process(QImage &frame)
{
    QImage image = (frameNumber % 2 == 0) ? odd(frame) : even(frame);
    frameNumber++;

    return image;
}























