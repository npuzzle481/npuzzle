#include "mainwindow.h"
#include "globals.h"
#include <time.h>




int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
