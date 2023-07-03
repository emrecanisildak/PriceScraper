#ifndef ANALYZELAUNCHERWIDGET_H
#define ANALYZELAUNCHERWIDGET_H

#include <QWidget>

// User Defined class
#include "analyzeparameters.h"

namespace Ui {
class AnalyzeLauncherWidget;
}

class AnalyzeLauncherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeLauncherWidget(QWidget *parent = nullptr);
    ~AnalyzeLauncherWidget();

    virtual void showEvent(QShowEvent* event)override;

signals:
    void startAnalyze(const QString& filePath, const AnalyzeParameter& parameter);

private slots:
    void onFileSelected(const QString& file_name);
    void onFileDialogShowClicked(bool flag);
    void onStartButtonClicked(bool flag);

private:
    Ui::AnalyzeLauncherWidget *ui;
    QString mChosenFilePath;
    void initUi();
};

#endif // ANALYZELAUNCHERWIDGET_H
