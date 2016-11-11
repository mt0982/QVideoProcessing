#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoProbe>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>
#include <QDebug>
#include <QTimer>

class VideoWidget: public QWidget {

    Q_OBJECT
    QVideoProbe *probe;
    QMediaPlayer *player;
    QVideoWidget *video;
    QGridLayout *grid;
    QTimer timer;

public:
    explicit VideoWidget();

    /* Setters */
    void setVideo(QString path);

    /* Getters */
    QGridLayout *getGrid() const;

public slots:
    void refresh();
};

#endif // VIDEOWIDGET_H






























