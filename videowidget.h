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
    QGridLayout *grid;
    VideoSurface *surface;
    QLabel *label;

    int width, height;

public:
    explicit VideoWidget();
    ~VideoWidget();

    void setWindowSize(int w, int h);

    /* Setters */
    void setVideo(QString path);

    /* Getters */
    QGridLayout *getGrid() const;

public slots:
    void processFrame(QImage image);
};

#endif // VIDEOWIDGET_H






























