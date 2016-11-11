#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoProbe>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>
#include <QVideoProbe>
#include <QDebug>
#include <QLabel>
#include "videosurface.h"

class VideoWidget: public QWidget {

    Q_OBJECT
    QMediaPlayer *player;
    VideoSurface *surface;
    QLabel *label;

    bool isDeinterlacing;

public:
    explicit VideoWidget();
    ~VideoWidget();

    void setWindowSize(int w, int h);

    /* Setters */
    void setVideo(QString path);
    void setIsDeinterlacing(bool value);

public slots:
    void processFrame(QImage image);

signals:
    void getFrame(QImage frame);
};

#endif // VIDEOWIDGET_H






























