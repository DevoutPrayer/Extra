#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSpacerItem>

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QGridLayout>
#include <QLabel>

#include "screenlabel.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();
private:
    QMenuBar *m_menuBar;
    QGridLayout *m_gridLayout;
    ScreenLabel *screenLabel;
private slots:
    void slotClickMenuBarOne();
};

#endif // WINDOW_H
