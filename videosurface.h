#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QWidget>
#include <QPainter>
#include <QDebug>

class VideoSurface: public QAbstractVideoSurface {

    Q_OBJECT

public:
    VideoSurface(QWidget *widget, QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const;

    bool start(const QVideoSurfaceFormat &format);
    void stop();

    bool present(const QVideoFrame &frame);

    QRect videoRect() const { return targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);

private:
    QWidget *widget;
    QImage::Format imageFormat;
    QRect targetRect;
    QSize imageSize;
    QRect sourceRect;
    QVideoFrame currentFrame;

signals:
    void frameAvailable(QImage image);
};

#endif // VIDEOSURFACE_H
