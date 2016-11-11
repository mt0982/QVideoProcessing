#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QDebug>

class VideoSurface: public QAbstractVideoSurface {

    Q_OBJECT

public:
    explicit VideoSurface();
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);

signals:
    void frameAvailable(QImage image);
};

#endif // VIDEOSURFACE_H
