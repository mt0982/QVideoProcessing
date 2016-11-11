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
    QVideoProbe *probe;
    QMediaPlayer *player;
    QVideoWidget *video;
    QGridLayout *grid;
    VideoSurface *surface;
    QLabel *label;

public:
    explicit VideoWidget();
    ~VideoWidget();

    /* Setters */
    void setVideo(QString path);

    /* Getters */
    QGridLayout *getGrid() const;

public slots:
    void processFrame(QVideoFrame frame);
    void processImage(QImage image);
};

#endif // VIDEOWIDGET_H






























