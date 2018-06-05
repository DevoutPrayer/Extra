#include "ch305.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CH305 w;
    w.show();

    return a.exec();
}
