#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QDebug>
#include <QElapsedTimer>
#include <QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/timg.jpg");

    QSplashScreen screen(pixmap);
        screen.show();
        screen.showMessage("LOVE", Qt::AlignCenter, Qt::red);

        /*int delayTime = 3;
        QElapsedTimer timer;
        timer.start();
        while(timer.elapsed() < (delayTime * 1000))
        {
             a.processEvents();
        }*/


/*
        QDateTime n=QDateTime::currentDateTime();
        QDateTime now;
        do{
            now=QDateTime::currentDateTime();
            a.processEvents();
        } while (n.secsTo(now)<=5);//5为需要延时的秒数
        */


    MainWindow w;

    w.show();
    screen.finish(&w);



    return a.exec();
}
