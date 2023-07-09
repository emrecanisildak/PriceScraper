#include "progresswidget.h"
#include "ui_progresswidget.h"

ProgressWidget::ProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressWidget)
{
    ui->setupUi(this);
    ui->plainTextEdit->setMaximumBlockCount(1000);

    setFixedSize(500,500);

    setWindowTitle("Analiz Bekleme Ekranı");
    setWindowFlags(Qt::WindowStaysOnTopHint);

    ui->progressBar->setValue(0);

    connect(ui->pushButton_durdur,&QPushButton::clicked,
            this,&ProgressWidget::onFinishedButtonClicked);


}

ProgressWidget::~ProgressWidget()
{
    delete ui;
}

void ProgressWidget::onLogOccured(const QString &log)
{
    ui->plainTextEdit->appendPlainText(log);
    ui->plainTextEdit->appendPlainText("\n");

}

void ProgressWidget::onLogStatitics(int total, int current)
{
    ui->label_totalBook->setText(QString::number(total));
    ui->label_currentBook->setText(QString::number(current));

    static int rate = 0;
    if(total != 0)
        rate = (double)current/(double)total*100.0;
    else
        rate = 0;

    ui->progressBar->setValue(rate);
}

void ProgressWidget::onFinished()
{

    ui->label_totalBook->setText("-");
    ui->label_currentBook->setText("-");
    ui->plainTextEdit->clear();
    ui->progressBar->setValue(0);
}

void ProgressWidget::onFinishedButtonClicked(bool flag)
{
    emit finishAnalyzRequest();
}
