#include "bma.h"

BMA::BMA()
{

}

QImage BMA::getNewFrame(QImage &currentFrame, QImage &previousFrame)
{

    /* Time */
    QTime t;
    t.start();

    /* Parameters */
    int blockSize = 8;
    int currentFrameSum;
    int previousFrameSum;
    int blockNr = 0;
    QVector<QVector3D> block;

    /* Height */
    for (int y = 0; y < currentFrame.height(); y += blockSize) {

        /* Width */
        for (int x = 0; x < currentFrame.width(); x += blockSize) {

            currentFrameSum = 0;
            previousFrameSum = 0;

            /* Block | Sum Each Pixel In Block */
            for(int k = 0; k < blockSize; k++) {

                QRgb *currentRGB = (QRgb*)currentFrame.scanLine(y + k);
                QRgb *previousRGB = (QRgb*)previousFrame.scanLine(y + k);
                for(int l = 0; l < blockSize; l++) {

                    previousFrameSum += qGray(previousRGB[x + l]);
                    currentFrameSum += qGray(currentRGB[x + l]);
                }
            }

            block.push_back(QVector3D(previousFrameSum, currentFrameSum, blockNr));
            blockNr++;
        }
    }

    /* Calculate New Blocks */
    QImage newFrame = calculate(blockSize, previousFrame, block);

    /* Elapse Time */
    //qDebug() << t.elapsed() / 1000.0f;

    /* Output */
    return newFrame;
}

QImage BMA::calculate(int blockSize, QImage &previousFrame, QVector<QVector3D> &block)
{
    /* Calculate New Blocks */
    QImage newFrame(previousFrame.width(), previousFrame.height(), QImage::Format_RGB32);
    int y = 0, x = 0;

    /* For Each Macroblock */
    for (int i = 0; i < block.size(); i++) {

        int currentFrame = block[i].y();
        int minimum = 999999;
        int newBlockIdx;
        int diff = 0;

        /* Calculate Neighbors Only [3x3] */
        for(int mul = -1; mul <= 1; mul++) {

            for(int step = -1; step <= 1; step++) {

                /* Check First Mid (0,0) Block | Barrier */
                if(abs(block[i].x() - currentFrame) == 0) {
                    minimum = abs(block[i].x() - currentFrame) / pow(blockSize, 2);
                    newBlockIdx = block[i].z();
                    break;
                }

                int offstet = i + (mul * (previousFrame.width() / blockSize)) + step;
                if(offstet >= 0 && offstet < block.size()) {

                    int previousFrame = block[offstet].x();
                    diff = abs(previousFrame - currentFrame);

                    if(diff < minimum) {
                        minimum = diff;
                        newBlockIdx = block[offstet].z();
                    }
                }
            }
        }

        /* Draw New Image */
        //if(minimum != 0) qDebug() << i << minimum << newBlockIdx;
        //newBlockIdx = block[i].z(); //should create normal img
        int newx = (newBlockIdx % (previousFrame.width() / blockSize)) * blockSize;
        int newy = (newBlockIdx / ( previousFrame.width() / blockSize)) * blockSize;

        //qDebug() << newy << newx;

        /* New Block */
        for(int k = 0; k < blockSize; k++) {

            QRgb *newRGB = (QRgb*)newFrame.scanLine(y + k);
            QRgb *previousRGB = (QRgb*)previousFrame.scanLine(newy + k);
            for(int l = 0; l < blockSize; l++) {
                newRGB[x + l] = previousRGB[newx + l];
            }
        }

        if(x + blockSize >= previousFrame.width()) { x = 0; y += blockSize; }
        else x += blockSize;
    }

    return newFrame;
}



























