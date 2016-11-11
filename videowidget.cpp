#include "videowidget.h"

VideoWidget::VideoWidget()
{
    /* Surface Handle | Display */
    surface = new VideoSurface(this);
    connect(surface, SIGNAL(frameAvailable(QImage)), this, SLOT(processFrame(QImage)));

    /* Content */
    player = new QMediaPlayer;
    player->setVideoOutput(surface);

    /* Output */
    label = new QLabel;
    label->setScaledContents(true);
    grid = new QGridLayout;
    grid->addWidget(label);
}

VideoWidget::~VideoWidget()
{
    delete surface;
    delete label;
    delete surface;
}

void VideoWidget::setWindowSize(int w, int h)
{
    this->width = w;
    this->height = h;
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
//    label->setPixmap(QPixmap::fromImage(image).scaled(image.width()/2,
//                                                      image.height()/2,
//                                                      Qt::KeepAspectRatio,
//                                                      Qt::SmoothTransformation));
}

















