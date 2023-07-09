#include "analyzelauncherwidget.h"
#include "ui_analyzelauncherwidget.h"

// Qt's include
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>

AnalyzeLauncherWidget::AnalyzeLauncherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeLauncherWidget)
{
    ui->setupUi(this);
    initUi();

    connect(ui->toolButton,&QToolButton::clicked,this,&AnalyzeLauncherWidget::onFileDialogShowClicked);
    connect(ui->pushButtonStart,&QPushButton::clicked,this,&AnalyzeLauncherWidget::onStartButtonClicked);
}

AnalyzeLauncherWidget::~AnalyzeLauncherWidget()
{
    delete ui;
}

void AnalyzeLauncherWidget::showEvent(QShowEvent *event)
{
    mChosenFilePath = "";
    ui->label_filePath->setText("Excel dosyası seçiniz");
    ui->label_filePath->setToolTip("");

}

void AnalyzeLauncherWidget::onFileSelected(const QString &file_name)
{
    mChosenFilePath = file_name;
    ui->label_filePath->setText(file_name);
    ui->label_filePath->setToolTip(file_name);
}

void AnalyzeLauncherWidget::onFileDialogShowClicked(bool flag)
{
    Q_UNUSED(flag);

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::root());
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Images (*.xlsx)"));
    dialog.setViewMode(QFileDialog::Detail);
    connect(&dialog,&QFileDialog::fileSelected,this,&AnalyzeLauncherWidget::onFileSelected);
    dialog.exec();
}

void AnalyzeLauncherWidget::onStartButtonClicked(bool flag)
{
    Q_UNUSED(flag);

    if(mChosenFilePath.isEmpty())
    {
        QMessageBox::warning(this,"Uyarı","Dosya yolu seçili değil. Analiz yapılamaz.");
        return;
    }


    AnalyzeParameter params;
    params.additional_cost = ui->lineEdit_ekGider->text().toInt();
    params.transportation_cost = ui->lineEdit_kargoMaliyet->text().toInt();
    params.amazon_share = ui->lineEdit_amazonPayi->text().toDouble();
    params.discount = ui->lineEdit_iskonto->text().toDouble();

    emit startAnalyze(mChosenFilePath,params);

    hide();
}

void AnalyzeLauncherWidget::initUi()
{
    setStyleSheet("QGroupBox{color: cyan;}");

    ui->toolButton->setIcon(QIcon(":/icon/search_icon.png"));
    setWindowTitle("Amazon Productivity");
    setWindowFlags(Qt::WindowStaysOnTopHint);

    // Set Size
    ui->label->setFixedWidth(150);
    ui->label_2->setFixedWidth(150);
    ui->label_3->setFixedWidth(150);
    ui->label_4->setFixedWidth(150);

    ui->lineEdit_iskonto->setFixedWidth(140);
    ui->lineEdit_kargoMaliyet->setFixedWidth(140);
    ui->lineEdit_amazonPayi->setFixedWidth(140);
    ui->lineEdit_ekGider->setFixedWidth(140);

    ui->toolButton->setFixedSize(30,30);
    ui->toolButton->setIconSize(QSize(20, 20));

    // Set Size
    QRegExp digitRegexp("[0-9]{6}");
    QRegExp digitRegexp2("[0-9]{3}");
    QRegExp floatRegex("[+-]?\\d*\\.?\\d+");

    ui->lineEdit_iskonto->setMaxLength(6);
    ui->lineEdit_amazonPayi->setMaxLength(6);

    ui->lineEdit_kargoMaliyet->setValidator(new QRegExpValidator(digitRegexp, ui->lineEdit_kargoMaliyet));
    ui->lineEdit_ekGider->setValidator(new QRegExpValidator(digitRegexp, ui->lineEdit_ekGider));
    ui->lineEdit_iskonto->setValidator(new QRegExpValidator(floatRegex, ui->lineEdit_iskonto));
    ui->lineEdit_amazonPayi->setValidator(new QRegExpValidator(floatRegex, ui->lineEdit_amazonPayi));

    // Set Allignment
    ui->lineEdit_kargoMaliyet->setAlignment(Qt::AlignRight);
    ui->lineEdit_ekGider->setAlignment(Qt::AlignRight);
    ui->lineEdit_iskonto->setAlignment(Qt::AlignRight);
    ui->lineEdit_amazonPayi->setAlignment(Qt::AlignRight);

}
