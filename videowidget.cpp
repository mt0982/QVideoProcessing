#include "videowidget.h"

VideoWidget::VideoWidget()
{
    player = new QMediaPlayer;
    video = new QVideoWidget;

    grid = new QGridLayout;
    grid->addWidget(video);

    player->setVideoOutput(video);

    connect(&timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer.start();
}

/* Setters */
void VideoWidget::setVideo(QString path)
{
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

/* Getters */
QGridLayout *VideoWidget::getGrid() const
{
    return grid;
}

void VideoWidget::refresh() {
    qDebug() << "A";
}

















