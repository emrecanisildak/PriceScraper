#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyzviewmodel.h"
#include <QThread>


class ProgressWidget;
class DataBuilder;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AnalyzeLauncherWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onAnalyzeFinished(const std::vector<RefinedData>& refinedData);
private:
    Ui::MainWindow *ui;

    std::vector<RefinedData> mLastData;

    ProgressWidget* mProgressBarWidget;

    AnalyzeLauncherWidget* mAnalyzLauncherWidget;
    DataBuilder* mDataBuilder;
    AnalyzViewModel mModel;
    QThread workerThread;


    void setDarkTheme();

};
#endif // MAINWINDOW_H
