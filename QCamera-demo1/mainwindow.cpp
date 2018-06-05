#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->graphicsView = new QGraphicsView();
    ui->setupUi(this);
    m_scene = new QGraphicsScene;
    ui->graphicsView->setScene(m_scene);
    setCentralWidget(ui->graphicsView);
    m_camera = new QCamera(QCameraInfo::defaultCamera());
    m_videoItem = new QGraphicsVideoItem;
    m_camera->setViewfinder(m_videoItem);
    m_scene->addItem(m_videoItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_camera->start();
}
