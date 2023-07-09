#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>
#include "analyzeparameters.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/amazon_icon.png"));

    qRegisterMetaType<AnalyzeParameter>("AnalyzeParameter");
    qRegisterMetaType<std::vector<RefinedData>>("std::vector<RefinedData>");

    QString num = "1,183";
    int n = num.replace(",","").toInt();
    qDebug()<<n;


    MainWindow w;
    w.show();
    return a.exec();
}

