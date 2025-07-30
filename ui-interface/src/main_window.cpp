#include "main_window.h"
#include "ui_main_window.h"
#include <iostream>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , logger(&Logger::getInstance())
{
    ui->setupUi(this);

    connect(logger, &Logger::logMessageSignal, this, &MainWindow::onLogMessage);

    initializeChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeChart()
{
    // Create the series and populate it
    series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    // Create the chart and configure it
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Create chart view
    chartView = new QChartView(chart);
    chartView->setMinimumSize(550, 400);
    chartView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add chart view to layout
    ui->graph_layout->addWidget(chartView);
}

void MainWindow::onLogMessage(const QString& message)
{
    std::cout << message.toStdString() << std::endl;
}