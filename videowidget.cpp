#include "videowidget.h"

VideoWidget::VideoWidget()
{
    player = new QMediaPlayer;
    video = new QVideoWidget;

    grid = new QGridLayout;
    grid->addWidget(video);

    /* Surface Handle */
    surface = new VideoSurface();
    connect(surface, SIGNAL(frameAvailable(QImage)), this, SLOT(processImage(QImage)));

    player->setVideoOutput(/*video*/surface);


    /* Frame Process Handle */
    probe = new QVideoProbe;
    probe->setSource(player);
    connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));

    label = new QLabel;
    label->show();
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
void VideoWidget::processFrame(QVideoFrame frame)
{
//    qDebug() << frame;
//    surface->present(frame);

//    QImage img( frame.bits(),
//                 frame.width(),
//                 frame.height(),
//                 frame.bytesPerLine(), QImage::Format_RGB32);
//    qDebug() << img.size();

//    if(frame.isValid()) {

//        QVideoFrame copy(frame);
//        copy.map(QAbstractVideoBuffer::ReadOnly);
//        QImage image(copy.bits(), copy.width(), copy.height(),
//                     QVideoFrame::imageFormatFromPixelFormat(copy.pixelFormat()));
//    }
}

void VideoWidget::processImage(QImage image)
{
    label->setPixmap(QPixmap::fromImage(image));
}

















