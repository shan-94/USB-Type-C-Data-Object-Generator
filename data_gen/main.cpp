#include "dialog.h"
#include "pdo.h"
#include "rdo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString fileName;

    TabDialog tabdialog(fileName);
    tabdialog.show();

    return a.exec();
}
