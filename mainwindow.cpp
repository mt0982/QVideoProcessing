#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    video = new VideoWidget;
    connect(video, SIGNAL(getFrame(QImage)), this, SLOT(processFrame(QImage)));
}

MainWindow::~MainWindow()
{
    delete video;
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Open"), "/home/asus/Wideo", tr("Format (*.avi *.mp4 *.mvk)"));
    if(!fname.isEmpty()) {
        QFileInfo info(fname);
        setWindowTitle(info.baseName());
        video->setVideo(fname);
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->widget->resize(width() - 100, height() - 100);
}

void MainWindow::processFrame(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

/* Deinterlacing Flag */
void MainWindow::on_actionDeinterlacing_triggered(bool checked)
{
    qDebug() << "MainWindow::Deinterlacing():" << checked;
}













