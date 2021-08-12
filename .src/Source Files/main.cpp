#include "mainwindow.h"
#include "splashscreen.h"
#include "loading.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    splashscreen w;
    loading load;
    load.show();
    a.setWindowIcon(QIcon(":/Images/icon.ico"));
    return a.exec();
}
