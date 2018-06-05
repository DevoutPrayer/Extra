#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QGridLayout *mainLayout;
    QHBoxLayout *m_HLayout;
    QListWidget *list;
    QLabel *m_label;
    QLineEdit *portLineEdit;
    QPushButton *submitBtn;
    QSpacerItem *m_spacer;
    QFont m_font;
signals:
    void signal_semsg(QString,int);
private slots:
    void slot_submit();
};

#endif // WIDGET_H
