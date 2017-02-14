#include <QApplication>

#include "smarttable.h"
#include "task.h"
#include "mainwindow.h"
#include "lockdisplay.h"

//QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const QString device = "ttyACM0";
    SmartTable *myTable = new SmartTable( device );
    MainWindow myApplication( myTable );
    myApplication.show();

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString strStyle = QLatin1String(file.readAll());
    qApp->setStyleSheet(strStyle);

    return app.exec();
}
