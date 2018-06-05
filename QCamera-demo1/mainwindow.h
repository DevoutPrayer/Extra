#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCamera>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QCameraInfo>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QCamera *m_camera;
    QGraphicsVideoItem *m_videoItem;
};

#endif // MAINWINDOW_H
