#include <QApplication>
#include "MainWindow.h"
#include "systemimagedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SystemImageDialog eh;
    eh.exec();
    return a.exec();

}
