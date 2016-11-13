#include "videosurface.h"

//http://doc.qt.io/qt-4.8/qt-multimedia-videowidget-example.html

VideoSurface::VideoSurface(QWidget *widget, QObject *parent)
    : QAbstractVideoSurface(parent)
    , widget(widget)
    , imageFormat(QImage::Format_Invalid)
{
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const
{
    Q_UNUSED(similar);

    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid && !size.isEmpty() && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool VideoSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {

        this->imageFormat = imageFormat;
        imageSize = size;
        sourceRect = format.viewport();

        QAbstractVideoSurface::start(format);

        widget->updateGeometry();
        updateVideoRect();
        return true;

    } else {
        return false;
    }
}

void VideoSurface::stop()
{
    currentFrame = QVideoFrame();
    targetRect = QRect();
    QAbstractVideoSurface::stop();
    widget->update();
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    if (frame.isValid()) {

        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        const QImage image(cloneFrame.bits(),
                           cloneFrame.width(),
                           cloneFrame.height(),
                           QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));

        emit frameAvailable(image);
        cloneFrame.unmap();
    }

    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();
        return false;

    } else {
        currentFrame = frame;
        widget->repaint(targetRect);
        return true;
    }
}

void VideoSurface::updateVideoRect()
{
    QSize size = surfaceFormat().sizeHint();
    size.scale(widget->size().boundedTo(size), Qt::KeepAspectRatio);

    targetRect = QRect(QPoint(0, 0), size);
    targetRect.moveCenter(widget->rect().center());
}

void VideoSurface::paint(QPainter *painter)
{
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        const QTransform oldTransform = painter->transform();

        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
            painter->scale(1, -1);
            painter->translate(0, -widget->height());
        }

        QImage image(
                    currentFrame.bits(),
                    currentFrame.width(),
                    currentFrame.height(),
                    currentFrame.bytesPerLine(),
                    imageFormat);

        painter->drawImage(targetRect, image, sourceRect);
        painter->setTransform(oldTransform);
        currentFrame.unmap();
    }
}
















