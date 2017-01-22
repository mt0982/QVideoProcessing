#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoProbe>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>
#include <QVideoProbe>
#include <QDebug>
#include <QLabel>
#include <QStack>
#include "videosurface.h"
#include "bma.h"

class VideoWidget: public QWidget {

    Q_OBJECT
    QMediaPlayer *player;
    VideoSurface *surface;
    QLabel *label;
    QStack<QImage> stack;
    BMA bma;

    bool isDeinterlacingChecked;
    bool isMotionEstimationChecked;

public:
    explicit VideoWidget();
    ~VideoWidget();

    void setWindowSize(int w, int h);

    /* Setters */
    void setVideo(QString path);
    void setIsDeinterlacing(bool value);
    void setIsMotionEstimation(bool value);

public slots:
    void processFrame(QImage image);

signals:
    void getFrame(QImage frame);
};

#endif // VIDEOWIDGET_H






























