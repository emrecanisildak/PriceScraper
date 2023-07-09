#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>

namespace Ui {
class ProgressWidget;
}

class ProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressWidget(QWidget *parent = nullptr);
    ~ProgressWidget();

signals:
    void finishAnalyzRequest();

public slots:
    void onLogOccured(const QString& log);
    void onLogStatitics(int total, int current);
    void onFinished();
    void onFinishedButtonClicked(bool flag);

private:
    Ui::ProgressWidget *ui;
};

#endif // PROGRESSWIDGET_H
