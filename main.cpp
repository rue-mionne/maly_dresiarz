#include "malydresiarz.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MalyDresiarz w;
    w.show();
    return a.exec();
}
