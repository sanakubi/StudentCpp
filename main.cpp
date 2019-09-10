#include "clalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    clalc sexy;
    sexy.show();

    return a.exec();
}
