#include "window.h"
#include <QDebug>
Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    /*给Window添加GridLayout*/
    QWidget *m_widget = new QWidget;
    m_gridLayout = new QGridLayout;
    m_widget->setLayout(m_gridLayout);
    setCentralWidget(m_widget);

    QLabel *m_label = new QLabel("xx0000");
    m_label->setFixedSize(20,30);
    m_label->setAlignment(Qt::AlignLeft);
    m_label->setStyleSheet("border:1px solid #fff");



    m_gridLayout->addWidget(m_label,0,0,Qt::AlignLeft);
    QSpacerItem *m_spacerItem = new QSpacerItem(20,10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_gridLayout->addItem(m_spacerItem,1,1);

    screenLabel = new ScreenLabel;
    m_gridLayout->addWidget(screenLabel,0,1,Qt::AlignRight);
    m_menuBar = new QMenuBar;
    QMenu *m_menu = new QMenu;
    m_menu->setTitle("7788");
    m_menu->addAction("7788");
    connect(m_menu,SIGNAL(triggered(QAction*)),this,SLOT(slotClickMenuBarOne()));
    m_menuBar->addMenu(m_menu);
    setMenuBar(m_menuBar);
    setMinimumSize(1200,300);
    m_menuBar->addMenu("AboutQt");

}

Window::~Window()
{

}

void Window::slotClickMenuBarOne()
{
    qDebug()<<"YesTrig";

}
