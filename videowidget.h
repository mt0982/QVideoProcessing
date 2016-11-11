#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoProbe>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>

class VideoWidget {

    QVideoProbe *probe;
    QMediaPlayer *player;
    QVideoWidget *video;
    QGridLayout *grid;

public:
    VideoWidget();

    /* Setters */
    void setVideo(QString path);

    /* Getters */
    QGridLayout *getGrid() const;
};

#endif // VIDEOWIDGET_H






























