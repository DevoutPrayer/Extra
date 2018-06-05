#ifndef SCREENLABEL_H
#define SCREENLABEL_H
#include <QLabel>

class ScreenLabel : public QLabel
{
public:
    explicit ScreenLabel(QWidget* parent = NULL);
    void paintEvent(QPaintEvent *paintEvent);
};

#endif // SCREENLABEL_H
