#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    float inputArray[10];
    void input_into_array();
private slots:
    void slot_clear_inputs();
    void slot_cal();
};

#endif // MAINWINDOW_H
