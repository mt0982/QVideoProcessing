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
    /* For Each Odd Line */
    for(int y = 1; y < image.height(); y += 2) {
        QRgb *previous = (QRgb*)image.scanLine(y-1);
        QRgb *current = (QRgb*)image.scanLine(y);
        QRgb *next = (QRgb*)image.scanLine(y+1);

        for (int x = 0; x < image.width(); x++) {
            int p_gray = qGray(previous[x]);
            int c_gray = qGray(current[x]);
            int n_gray = qGray(next[x]);

            if(((p_gray + n_gray) / 2.0f) - c_gray > 5.0f) {
                current[x] = qRgb((qRed(previous[x]) + qRed(next[x])) / 2,
                                  (qGreen(previous[x]) + qGreen(next[x])) / 2,
                                  (qBlue(previous[x]) + qBlue(next[x])) / 2);
            }
        }
    }

    label->setPixmap(QPixmap::fromImage(image));

//    label->setPixmap(QPixmap::fromImage(image).scaled(image.width()/2,
//                                                      image.height()/2,
//                                                      Qt::KeepAspectRatio,
//                                                      Qt::SmoothTransformation));
}

















