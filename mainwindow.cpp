#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    video = new VideoWidget;
    ui->widget->setLayout(video->getGrid());
    video->setVideo("/home/asus/Wideo/BickBuckBunny.mp4");
}

MainWindow::~MainWindow()
{
    delete ui;
}
