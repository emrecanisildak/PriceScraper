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

    MainWindow w;
    w.show();
    return a.exec();
}

