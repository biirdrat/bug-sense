#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Logger.h"
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void initializeChart();
    Logger* logger;

private:
    Ui::MainWindow *ui;

private:
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;

private slots:
    void onLogMessage(LogLevel log_level, const QString& formatted_message);
};
#endif // MAINWINDOW_H