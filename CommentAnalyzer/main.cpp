#include "mainwindow.h"
#include "commenttestdriver.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    CommentTestDriver driver;
    driver.testComment();

    return(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
