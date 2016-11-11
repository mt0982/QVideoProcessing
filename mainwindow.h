#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QResizeEvent>
#include "videowidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    VideoWidget *video;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void resizeEvent(QResizeEvent *);
    void processFrame(QImage image);
    void on_actionDeinterlacing_triggered(bool checked);
    void on_action4_3_triggered();
    void on_action16_9_triggered();
    void on_action24_10_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
























