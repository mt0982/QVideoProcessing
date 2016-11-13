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
    QString fname = QFileDialog::getOpenFileName(this, tr("Open"), "/home/asus/Wideo", tr("Format (*.avi *.mp4 *.mpg)"));
    if(!fname.isEmpty()) {
        QFileInfo info(fname);
        setWindowTitle(info.baseName());
        video->setVideo(fname);
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{

}

/* Output */
void MainWindow::processFrame(QImage image)
{
    //QTime t; t.start();
    image = image.scaled(ui->label->width(), ui->label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));
    //qDebug() << t.elapsed() / 1000.0 << image.size();
}

/* Deinterlacing Flag */
void MainWindow::on_actionDeinterlacing_triggered(bool checked)
{
    qDebug() << "MainWindow::Deinterlacing():" << checked;
    video->setIsDeinterlacing(checked);
}

/* Aspect Ratio */
void MainWindow::on_action4_3_triggered()
{
    int h = ui->label->height();
    int w = (h * 4.0) / 3;
    ui->label->resize(w,h);
}

void MainWindow::on_action16_9_triggered()
{
    int h = ui->label->height();
    int w = (h * 16.0) / 9;
    ui->label->resize(w,h);
}

void MainWindow::on_action24_10_triggered()
{
    int h = ui->label->height();
    int w = h * 2.4;
    ui->label->resize(w,h);
}














