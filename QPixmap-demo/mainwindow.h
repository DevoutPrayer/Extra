#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void drawPixMap();
private:
    QLabel *m_label;
    QGridLayout *mainLayout;
};

#endif // MAINWINDOW_H
