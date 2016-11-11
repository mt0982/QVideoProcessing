#include "videosurface.h"

VideoSurface::VideoSurface()
{

}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB565;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    Q_UNUSED(frame);
    // Handle the frame and do your processing

    return true;
}
