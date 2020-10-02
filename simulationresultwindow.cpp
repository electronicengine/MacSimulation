#include <QDir>
#include "peersimulation.h"
#include "simulationresultwindow.h"
#include "ui_simulationresultwindow.h"



SimulationResultWindow::SimulationResultWindow(const QString &Title, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationResultWindow)
{
    ui->setupUi(this);

    Sample_Count = 0;

    Max_Delay_Value = 0;
    Max_Total_Collusion_Value = 0;
    Max_Buffer_Value = 0;
    Max_DataRate_Value = 0;
    Max_Dropped_Backage = 0;
    Max_Unsuc_Reservation_Value = 0;

    setupBufferGraph();
    setupCollusionGraph();
    setupDataRateGraph();
    setupDelayGraph();
    setupDroppedPackGraph();
    setupReservationGraph();

    Avarage_Delay_Series = std::make_unique<QLineSeries>();

    this->setFormTitle(Title);


}



SimulationResultWindow::~SimulationResultWindow()
{
    delete ui;
}



PeerSimulationOutput SimulationResultWindow::getOutput()
{

    PeerSimulationOutput output;

    output.Max_Buffer_Value = ui->buffer_max->text().toInt();
    output.Max_DataRate_Value = ui->datarate_max->text().toDouble();
    output.Max_Total_Collusion_Value = ui->collusion_total_max->text().toDouble();
    output.Max_Delay = ui->delay_max->text().toDouble();
    output.Max_Dropped_Package_Value = ui->dropped_package_max->text().toDouble();
    output.Max_Unsuccesfull_Reservation = ui->reservation_max->text().toInt();

    output.Avarage_Delay_Value = Max_Avarage_Delay_Value;

    return output;
}



void SimulationResultWindow::setFormTitle(const QString &Title)
{
    this->setWindowTitle(Title);
}



void SimulationResultWindow::setupCollusionGraph()
{

    Collusion_Series = std::make_unique<QLineSeries>();

    Collusion_Chart = std::make_unique<QChart>();

    Collusion_Chart_View = std::make_unique<QChartView>(Collusion_Chart.get());

    Collusion_Chart->legend()->hide();
    Collusion_Chart->addSeries(Collusion_Series.get());
    Collusion_Chart->setTitle("Collusion Rate (Per Cap Request)");
    Collusion_Chart->createDefaultAxes();
    Collusion_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Collusion_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));
    Collusion_Chart->axes(Qt::Horizontal).back()->setRange(0, 30);

    Collusion_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Collusion_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);
    Collusion_Chart->axes(Qt::Vertical).back()->setRange(0, 10);

    Collusion_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Collusion_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Collusion_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Collusion_Chart_View->setRenderHint(QPainter::Antialiasing);
    Collusion_Chart_View->setParent(ui->collusion_graph_peer);
    Collusion_Chart_View->resize(ui->collusion_graph_peer->size());

    Collusion_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

}



void SimulationResultWindow::setupDataRateGraph()
{

    DataRate_Series = std::make_unique<QLineSeries>();

    DataRate_Chart = std::make_unique<QChart>();

    DataRate_Chart_View = std::make_unique<QChartView>(DataRate_Chart.get());

    DataRate_Chart->legend()->hide();
    DataRate_Chart->addSeries(DataRate_Series.get());
    DataRate_Chart->setTitle("DataRate (KBPS)");
    DataRate_Chart->createDefaultAxes();
    DataRate_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    DataRate_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    DataRate_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    DataRate_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    DataRate_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    DataRate_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    DataRate_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    DataRate_Chart_View->setRenderHint(QPainter::Antialiasing);
    DataRate_Chart_View->setParent(ui->datarate_graph);
    DataRate_Chart_View->resize(ui->datarate_graph->size());

    DataRate_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

}



void SimulationResultWindow::setupDelayGraph()
{

    Delay_Series = std::make_unique<QLineSeries>();

    Delay_Chart = std::make_unique<QChart>();

    Delay_Chart_View = std::make_unique<QChartView>(Delay_Chart.get());

    Delay_Chart->legend()->hide();
    Delay_Chart->addSeries(Delay_Series.get());
    Delay_Chart->setTitle("Latency (Slot Number)");
    Delay_Chart->createDefaultAxes();
    Delay_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Delay_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    Delay_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Delay_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    Delay_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Delay_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Delay_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Delay_Chart_View->setRenderHint(QPainter::Antialiasing);
    Delay_Chart_View->setParent(ui->delay_graph);
    Delay_Chart_View->resize(ui->delay_graph->size());

    Delay_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

}



void SimulationResultWindow::setupBufferGraph()
{

    Buffer_Series = std::make_unique<QLineSeries>();

    Buffer_Chart = std::make_unique<QChart>();

    Buffer_Chart_View = std::make_unique<QChartView>(Buffer_Chart.get());

    Buffer_Chart->legend()->hide();
    Buffer_Chart->addSeries(Buffer_Series.get());
    Buffer_Chart->setTitle("Buffer (Package)");
    Buffer_Chart->createDefaultAxes();
    Buffer_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Buffer_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    Buffer_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Buffer_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    Buffer_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Buffer_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Buffer_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Buffer_Chart_View->setRenderHint(QPainter::Antialiasing);
    Buffer_Chart_View->setParent(ui->buffer_graph_peer);
    Buffer_Chart_View->resize(ui->buffer_graph_peer->size());

    Buffer_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

}



void SimulationResultWindow::setupDroppedPackGraph()
{
    Dropped_Pack_Series = std::make_unique<QLineSeries>();

    Dropped_Pack_Chart = std::make_unique<QChart>();

    Dropped_Pack_Chart_View = std::make_unique<QChartView>(Dropped_Pack_Chart.get());


    Dropped_Pack_Chart->legend()->hide();
    Dropped_Pack_Chart->addSeries(Dropped_Pack_Series.get());
    Dropped_Pack_Chart->setTitle("Drop (Package)");
    Dropped_Pack_Chart->createDefaultAxes();
    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    Dropped_Pack_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Dropped_Pack_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    Dropped_Pack_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Dropped_Pack_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Dropped_Pack_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Dropped_Pack_Chart_View->setRenderHint(QPainter::Antialiasing);
    Dropped_Pack_Chart_View->setParent(ui->dropped_package_graph);
    Dropped_Pack_Chart_View->resize(ui->dropped_package_graph->size());

    Dropped_Pack_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);
}

void SimulationResultWindow::setupReservationGraph()
{
    Reservation_Series = std::make_unique<QLineSeries>();

    Reservation_Chart = std::make_unique<QChart>();

    Reservation_Chart_View = std::make_unique<QChartView>(Reservation_Chart.get());


    Reservation_Chart->legend()->hide();
    Reservation_Chart->addSeries(Reservation_Series.get());
    Reservation_Chart->setTitle("Failed Reservation");
    Reservation_Chart->createDefaultAxes();
    Reservation_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Reservation_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    Reservation_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Reservation_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    Reservation_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Reservation_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Reservation_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Reservation_Chart_View->setRenderHint(QPainter::Antialiasing);
    Reservation_Chart_View->setParent(ui->reservation_graph);
    Reservation_Chart_View->resize(ui->reservation_graph->size());

    Reservation_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);
}



void SimulationResultWindow::addCollusionValue(double Value)
{

    if(Value > Max_Total_Collusion_Value)
    {
        Max_Total_Collusion_Value = Value;
        Collusion_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Total_Collusion_Value);
        ui->collusion_total_max->setText(QString::number(Max_Total_Collusion_Value));
    }

    Collusion_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);

    Collusion_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addDataRateValue(double Value)
{

    if(Value > Max_DataRate_Value)
    {

        Max_DataRate_Value = Value;
        DataRate_Chart->axes(Qt::Vertical).back()->setRange(0, Max_DataRate_Value);
        ui->datarate_max->setText(QString::number(Max_DataRate_Value));

    }

    DataRate_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);

    DataRate_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addDelayValue(int Value)
{


    if(Value > Max_Delay_Value)
    {
        Max_Delay_Value = Value;
        Delay_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Delay_Value);
        ui->delay_max->setText(QString::number(Value));
    }

    Delay_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);

    Delay_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addAvarageDelayValue(int Value)
{
    if(Value > Max_Avarage_Delay_Value)
    {
        Max_Avarage_Delay_Value = Value;
    }

    Avarage_Delay_Series->append(Sample_Count, Value);
}



void SimulationResultWindow::addBufferValue(int Value)
{

    if(Value > Max_Buffer_Value)
    {
        Max_Buffer_Value = Value;
        Buffer_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Buffer_Value);
        ui->buffer_max->setText(QString::number(Value));
    }

    Buffer_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
    Buffer_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addDroppedPackValue(int Value)
{
    if(Value > Max_Dropped_Backage)
    {
        Max_Dropped_Backage = Value;
        Dropped_Pack_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Dropped_Backage);
        ui->dropped_package_max->setText(QString::number(Value));

    }

    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
    Dropped_Pack_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addReservationValue(int Value)
{
    if(Value > Max_Unsuc_Reservation_Value)
    {
        Max_Unsuc_Reservation_Value = Value;
        Reservation_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Unsuc_Reservation_Value);
        ui->reservation_max->setText(QString::number(Value));

    }

    Reservation_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
    Reservation_Series->append(Sample_Count, Value);
}



void SimulationResultWindow::saveGraphtoFile(const QString &UpperDir, const QString &Title)
{

    QString dir;

    dir = "graphs";

    if(!QDir(dir).exists())
        QDir().mkdir(dir);


    if(UpperDir == "graphs")
    {


        dir += + "/" + Title;

        if(!QDir(dir).exists())
            QDir().mkdir(dir);
    }
    else
    {

        dir += "/" + UpperDir;

        if(!QDir(dir).exists())
            QDir().mkdir(dir);

        dir += + "/" + Title;

        if(!QDir(dir).exists())
            QDir().mkdir(dir);

    }


    QPixmap pic = this->grab();
    this->render(&pic);
    pic.save(dir + "/" + Title + ".png");

    QFile file(dir + "/" + windowTitle() + ".log");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);


    out << "\t\t Collusion: "
        << "\t\t Buffer: "
        << "\t\t DataRate: "
        << "\t\t Delay: "
        << "\t\t Avarage Delay: "
        << "\t\t Drop: "
        << "\t\t Unsuccess Reservation: "
        <<" \n\n";


    for(int i = 0; i<Sample_Count; i++)
    {
        out << Sample_Names[i]
            << "\t\t " << QString::number(Collusion_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Buffer_Series->at(i).y()).rightJustified(8,'0')
            << "\t\t " << QString::number(DataRate_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Delay_Series->at(i).y()).rightJustified(8,'0')
            << "\t\t " << QString::number(Avarage_Delay_Series->at(i).y()).rightJustified(8,'0')
            << "\t\t " << QString::number(Dropped_Pack_Series->at(i).y()).rightJustified(8,'0')
            << "\t\t " << QString::number(Reservation_Series->at(i).y()).rightJustified(8,'0')
            <<" \n";
    }

    Sample_Count = 0;

    Max_Delay_Value = 0;
    Max_Total_Collusion_Value = 0;
    Max_Buffer_Value = 0;
    Max_DataRate_Value = 0;
    Max_Dropped_Backage = 0;
    Max_Unsuc_Reservation_Value = 0;


}



void SimulationResultWindow::refreshValues(const PeerSimulationOutput &Output, const QString &Name)
{

    Sample_Names.push_back(Name);
    Sample_Count++;

    addCollusionValue(Output.Max_Total_Collusion_Value);
    addBufferValue(Output.Max_Buffer_Value);
    addDataRateValue(Output.Max_DataRate_Value);
    addDelayValue(Output.Max_Delay);
    addAvarageDelayValue(Output.Avarage_Delay_Value);
    addDroppedPackValue(Output.Max_Dropped_Package_Value);
    addReservationValue(Output.Max_Unsuccesfull_Reservation);



}
