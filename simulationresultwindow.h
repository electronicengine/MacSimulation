#ifndef SIMULATIONRESULTWINDOW_H
#define SIMULATIONRESULTWINDOW_H


#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>

#include "coordinator.h"

struct PeerSimulationOutput;

using namespace QtCharts;

namespace Ui {
class SimulationResultWindow;
}

class SimulationResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationResultWindow(const QString &Title, QWidget *parent = nullptr);
    ~SimulationResultWindow();

    PeerSimulationOutput getOutput();
    void refreshValues(const PeerSimulationOutput &Output, const QString &Name);
    void setFormTitle(const QString &Title);
    void saveGraphtoFile(const QString &HomeDir, const QString &UpperDir, const QString &Title);


public slots:

    void closeButton1Clicked();
    void nextButton1Clicked();
    void previousButton1Clicked();

    void closeButton2Clicked();
    void nextButton2Clicked();
    void previousButton2Clicked();

    void closeButton3Clicked();
    void nextButton3Clicked();
    void previousButton3Clicked();

    void closeButton4Clicked();
    void nextButton4Clicked();
    void previousButton4Clicked();

    void closeButton5Clicked();
    void nextButton5Clicked();
    void previousButton5Clicked();

    void closeButton6Clicked();
    void nextButton6Clicked();
    void previousButton6Clicked();

private:
    Ui::SimulationResultWindow *ui;


    double Max_Unsuc_Reservation_Value;
    double Max_Buffer_Value;
    double Max_Dropped_Package;
    double Total_Package_Sent_Value;
    double Max_DataRate_Value;
    double Max_Total_Collusion_Value;
    double Avarage_Collution_Value;
    double Max_Peer_Collusion_Value;
    double Max_Delay_Value;
    double Max_Avarage_Delay_Value;

    int Sample_Count;


    std::unique_ptr<QLineSeries> Collusion_Series;
    std::unique_ptr<QLineSeries> DataRate_Series;
    std::unique_ptr<QLineSeries> Delay_Series;
    std::unique_ptr<QLineSeries> Avarage_Delay_Series;
    std::unique_ptr<QLineSeries> Buffer_Series;
    std::unique_ptr<QLineSeries> Dropped_Pack_Series;
    std::unique_ptr<QLineSeries> Reservation_Series;
    std::unique_ptr<QLineSeries> Total_Package_Sent_Series;


    std::unique_ptr<QChartView> Collusion_Chart_View;
    std::unique_ptr<QChartView> DataRate_Chart_View;
    std::unique_ptr<QChartView> Delay_Chart_View;
    std::unique_ptr<QChartView> Buffer_Chart_View;
    std::unique_ptr<QChartView> Dropped_Pack_Chart_View;
    std::unique_ptr<QChartView> Reservation_Chart_View;

    std::unique_ptr<QChart> Collusion_Chart;
    std::unique_ptr<QChart> DataRate_Chart;
    std::unique_ptr<QChart> Delay_Chart;
    std::unique_ptr<QChart> Buffer_Chart;
    std::unique_ptr<QChart> Dropped_Pack_Chart;
    std::unique_ptr<QChart> Reservation_Chart;

    std::vector<QString> Sample_Names;

    void setupCollusionGraph();
    void setupDataRateGraph();
    void setupDelayGraph();
    void setupBufferGraph();
    void setupDroppedPackGraph();
    void setupReservationGraph();

    void addCollusionValue(double Value);
    void addDataRateValue(double Value);
    void addDelayValue(double Value);
    void addAvarageDelayValue(double Value);
    void addBufferValue(double Value);
    void addDroppedPackValue(double Value);
    void addTotalPackageSentValue(double Value);
    void addReservationValue(double Value);


};

#endif // SIMULATIONRESULTWINDOW_H
