#include "container.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Container wgt(":/data.xml");
    wgt.show();
    return a.exec();
}
