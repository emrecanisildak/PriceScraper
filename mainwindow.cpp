#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyleFactory>
#include <QDebug>
#include <QCursor>
#include "analyzelauncherwidget.h"
#include <QMetaType>
#include <QFileDialog>
#include "exportcontroller.h"
#include <databuilder.h>
#include <QMessageBox>
#include "progresswidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<std::vector<RefinedData>>("RefinedDataContainer");
    setDarkTheme();
    setFixedWidth(1335);

    ui->setupUi(this);
    setWindowTitle("Amazon Productivity");
    setWindowIcon(QIcon(":/icon/amazon_icon.png"));

    connect(ui->actionHelp,&QAction::triggered,this,[this](bool flag)
     {
                QMessageBox::information(this,"Yardım","Telif Hakkı © 2023 EciesCompany. Tüm hakları saklıdır."
"Bu uygulama, Amazon'daki ürünlerin fiyat analizini yapmak için geliştirilmiştir.\nBu uygulama, EciesCompany tarafından oluşturulmuş olup, tüm telif hakkı, ticari marka hakları ve diğer fikri mülkiyet haklarına ilişkin yasal korumalarla korunmaktadır.\nBu uygulamanın içeriği, yazılı izin alınmadan çoğaltılamaz, dağıtılamaz, değiştirilemez, yayınlanamaz veya başka bir şekilde kullanılamaz.\n"
"Bu uygulama, kullanıcılara Amazon'daki ürünlerin fiyatlarını karşılaştırmak ve analiz etmek için kullanılabilir. Ancak, uygulamanın verdiği fiyat bilgileri yalnızca bilgilendirme amaçlıdır ve kesinlik, doğruluk veya güncellik garantisi verilmez.\nKullanıcılar, kendi takdirlerine bağlı olarak bu bilgilere dayanarak hareket etmeli ve satın alma kararlarını yapmadan önce kendi araştırmalarını yapmalıdır."
"Bu uygulama, üçüncü taraf web sitelerine veya hizmetlere bağlantılar içerebilir.\nBu bağlantılar, kullanıcıları farklı sitelere yönlendirebilir ve bu sitelerin içeriği veya güvenlik önlemleri hakkında EciesCompany tarafından herhangi bir kontrol veya sorumluluk sağlanmamaktadır.\n"
"Lütfen, bu uygulamayı kullanmadan önce Kullanım Koşulları ve Gizlilik Politikası'nı dikkatlice okuyun. Bu belgeler, uygulamanın kullanımına ilişkin önemli bilgiler içermektedir."
"Bu telif hakkı metni, EciesCompany tarafından sağlanan Amazon fiyat analizi uygulamasıyla ilgili tüm fikri mülkiyet haklarını korur.\n"
"Herhangi bir soru veya endişeniz varsa, lütfen bize emirgulal@gmail.com üzerinden ulaşın."
                                                "Teşekkür ederiz!");
            });

    mDataBuilder          = new DataBuilder;
    mAnalyzLauncherWidget = new AnalyzeLauncherWidget;
    mProgressBarWidget    = new ProgressWidget;


    connect(mProgressBarWidget, &ProgressWidget::finishAnalyzRequest,
            mDataBuilder, &DataBuilder::onFinishRequest);

    connect(mDataBuilder, &DataBuilder::logOccured,
            mProgressBarWidget, &ProgressWidget::onLogOccured);

    connect(mDataBuilder, &DataBuilder::goingStatics,
            mProgressBarWidget, &ProgressWidget::onLogStatitics);

    connect(mDataBuilder,&DataBuilder::analyzeFinished,
            this, &MainWindow::onAnalyzeFinished);

    connect(mAnalyzLauncherWidget,&AnalyzeLauncherWidget::startAnalyze,
            mDataBuilder,        &DataBuilder::onStartAnalyzeRequest);

    connect(ui->actionAnaliz_Ekran,&QAction::triggered,
            this,[this](){
                mProgressBarWidget->show();
            });



    connect(mAnalyzLauncherWidget,&AnalyzeLauncherWidget::startAnalyze,
            [this](const QString& filePath, const AnalyzeParameter& parameter){
                mProgressBarWidget->show();
            });

    connect(ui->actionYeni,&QAction::triggered,this,[this](bool isTriggered)
    {
          Q_UNUSED(isTriggered);
          mAnalyzLauncherWidget->show();
    });

    connect(ui->actionDisaAktar, &QAction::triggered,this,[this](bool isTriggered)
            {
                Q_UNUSED(isTriggered);
                QFileDialog dialog(this);
                dialog.setDirectory(QDir::root());
                dialog.setFileMode(QFileDialog::Directory);
                dialog.setViewMode(QFileDialog::Detail);
                connect(&dialog,&QFileDialog::fileSelected,this,[this](const QString& file)
                        {
                            QString time_format = "/yyyy_MM_dd_HH_mm_ss";
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            as += "_Analiz.xlsx";

                            QString fileFullName = file + as;
                            qDebug()<<fileFullName;
                            ExportController::onExportRequest(mLastData,fileFullName);
                        });

                dialog.exec();
            });

     ui->tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
     ui->tableView->setModel(&mModel);

     ui->tableView->setColumnWidth(0,150);
     ui->tableView->setColumnWidth(1,300);
     ui->tableView->setColumnWidth(2,100);
     ui->tableView->setColumnWidth(3,90);
     ui->tableView->setColumnWidth(4,110);
     ui->tableView->setColumnWidth(5,90);
     ui->tableView->setColumnWidth(6,90);
     ui->tableView->setColumnWidth(7,90);
     ui->tableView->setColumnWidth(8,110);
     ui->tableView->setColumnWidth(9,90);
     ui->tableView->setColumnWidth(10,90);

     mDataBuilder->moveToThread(&workerThread);
     connect(&workerThread, &QThread::started, mDataBuilder, &DataBuilder::init);

     connect(&workerThread, &QThread::finished, mDataBuilder, &QObject::deleteLater);
     workerThread.start();

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    workerThread.quit();
    workerThread.wait();
    delete mProgressBarWidget;
}

void MainWindow::onAnalyzeFinished(const std::vector<RefinedData> &refinedData)
{
    mLastData = refinedData;
    mModel.giveModelData(refinedData);
    mProgressBarWidget->onFinished();
    mProgressBarWidget->hide();
}

void MainWindow::setDarkTheme()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QFont defaultFont = QApplication::font();
    defaultFont.setPointSize(defaultFont.pointSize()+2);
    qApp->setFont(defaultFont);
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window,QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Base,QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
    darkPalette.setColor(QPalette::ToolTipText,Qt::white);
    darkPalette.setColor(QPalette::Text,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
    darkPalette.setColor(QPalette::Button,QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText,Qt::red);
    darkPalette.setColor(QPalette::Link,QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));
    qApp->setPalette(darkPalette);

}




