#include "videowidget.h"

VideoWidget::VideoWidget()
{
    /* Surface Handle | Display */
    surface = new VideoSurface();
    connect(surface, SIGNAL(frameAvailable(QImage)), this, SLOT(processFrame(QImage)));

    /* Content */
    player = new QMediaPlayer;
    player->setVideoOutput(surface);

    /* Output */
    label = new QLabel;
    grid = new QGridLayout;
    grid->addWidget(label);
}

VideoWidget::~VideoWidget()
{
    delete surface;
    delete label;
    delete surface;
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

/* Slots */
void VideoWidget::processFrame(QImage image)
{
    label->setPixmap(QPixmap::fromImage(image));
}

















