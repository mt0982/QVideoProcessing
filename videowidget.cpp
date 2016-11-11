#include "videowidget.h"

VideoWidget::VideoWidget()
{
    player = new QMediaPlayer;
    video = new QVideoWidget;

    grid = new QGridLayout;
    grid->addWidget(video);
}

/* Setters */
void VideoWidget::setVideo(QString path)
{
    player->setVideoOutput(video);
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

/* Getters */
QGridLayout *VideoWidget::getGrid() const
{
    return grid;
}
