#include <QDir>
#include <QScreen>
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
    Max_Dropped_Package = 0;
    Max_Unsuc_Reservation_Value = 0;
    Avarage_Collution_Value = 0;


    setupBufferGraph();
    setupCollusionGraph();
    setupDataRateGraph();
    setupDelayGraph();
    setupDroppedPackGraph();
    setupReservationGraph();

    QScreen *screen = QApplication::screens().at(0);

    ui->stackedWidget->resize(screen->availableGeometry().width(), screen->availableGeometry().height() - 80);

    Avarage_Delay_Series = std::make_unique<QLineSeries>();
    Total_Package_Sent_Series = std::make_unique<QLineSeries>();

    connect(ui->close_button_1, SIGNAL(clicked()), this, SLOT(closeButton1Clicked()));
    connect(ui->next_button_1, SIGNAL(clicked()), this, SLOT(nextButton1Clicked()));
    connect(ui->previous_button_1, SIGNAL(clicked()), this, SLOT(previousButton1Clicked()));

    connect(ui->close_button_2, SIGNAL(clicked()), this, SLOT(closeButton2Clicked()));
    connect(ui->next_button_2, SIGNAL(clicked()), this, SLOT(nextButton2Clicked()));
    connect(ui->previous_button_2, SIGNAL(clicked()), this, SLOT(previousButton2Clicked()));

    connect(ui->close_button_3, SIGNAL(clicked()), this, SLOT(closeButton3Clicked()));
    connect(ui->next_button_3, SIGNAL(clicked()), this, SLOT(nextButton3Clicked()));
    connect(ui->previous_button_3, SIGNAL(clicked()), this, SLOT(previousButton3Clicked()));

    connect(ui->close_button_4, SIGNAL(clicked()), this, SLOT(closeButton4Clicked()));
    connect(ui->next_button_4, SIGNAL(clicked()), this, SLOT(nextButton4Clicked()));
    connect(ui->previous_button_4, SIGNAL(clicked()), this, SLOT(previousButton4Clicked()));

    connect(ui->close_button_5, SIGNAL(clicked()), this, SLOT(closeButton5Clicked()));
    connect(ui->next_button_5, SIGNAL(clicked()), this, SLOT(nextButton5Clicked()));
    connect(ui->previous_button_5, SIGNAL(clicked()), this, SLOT(previousButton5Clicked()));

    connect(ui->close_button_6, SIGNAL(clicked()), this, SLOT(closeButton6Clicked()));
    connect(ui->next_button_6, SIGNAL(clicked()), this, SLOT(nextButton6Clicked()));
    connect(ui->previous_button_6, SIGNAL(clicked()), this, SLOT(previousButton6Clicked()));

    this->setFormTitle(Title);


}



SimulationResultWindow::~SimulationResultWindow()
{
    delete ui;
}



PeerSimulationOutput SimulationResultWindow::getOutput()
{

    PeerSimulationOutput output;

    output.Max_Buffer_Value = ui->buffer_max->text().toDouble();
    output.Max_DataRate_Value = ui->datarate_max->text().toDouble();
    output.Max_Total_Collusion_Value = ui->collusion_total_max->text().toDouble();
//    output.Max_Total_Collusion_Value = Avarage_Collution_Value;
    output.Max_Delay = ui->delay_max->text().toDouble();
    output.Max_Dropped_Package_Value = Max_Dropped_Package;
    output.Max_Total_Sent_Package = Total_Package_Sent_Value;
    output.Max_Unsuccesfull_Reservation = ui->reservation_max->text().toDouble();

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
    ui->collusion_graph_peer->resize(this->size().width(), this->size().height() - 140);
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
    ui->datarate_graph->resize(this->size().width(), this->size().height() - 140);

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
    Delay_Chart->setTitle("Latency (ms)");
    Delay_Chart->createDefaultAxes();
    Delay_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
    Delay_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

    Delay_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
    Delay_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

    Delay_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
    Delay_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
    Delay_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

    Delay_Chart_View->setRenderHint(QPainter::Antialiasing);
    ui->delay_graph->resize(this->size().width(), this->size().height() - 140);

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
    ui->buffer_graph_peer->resize(this->size().width(), this->size().height() - 140);

    Buffer_Chart_View->setParent(ui->buffer_graph_peer);
    Buffer_Chart_View->resize(ui->buffer_graph_peer->size());


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
    ui->dropped_package_graph->resize(this->size().width(), this->size().height() - 140);

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
    ui->reservation_graph->resize(this->size().width(), this->size().height() - 140);

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

//    Avarage_Collution_Value = Avarage_Collution_Value * (Sample_Count - 1);

//    Avarage_Collution_Value += Value;

//    Avarage_Collution_Value /= (Sample_Count);

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



void SimulationResultWindow::addDelayValue(double Value)
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



void SimulationResultWindow::addAvarageDelayValue(double Value)
{
    if(Value > Max_Avarage_Delay_Value)
    {
        Max_Avarage_Delay_Value = Value;
    }

    Avarage_Delay_Series->append(Sample_Count, Value);
}



void SimulationResultWindow::addBufferValue(double Value)
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



void SimulationResultWindow::addDroppedPackValue(double Value)
{
    if(Value > Max_Dropped_Package)
    {
        Max_Dropped_Package = Value;
        Dropped_Pack_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Dropped_Package);
        ui->dropped_package_max->setText(QString::number(Value));

    }

    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
    Dropped_Pack_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addTotalPackageSentValue(double Value)
{
    if(Value > Total_Package_Sent_Value)
    {
        Total_Package_Sent_Value = Value;
    }

    Total_Package_Sent_Series->append(Sample_Count, Value);

}



void SimulationResultWindow::addReservationValue(double Value)
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



void SimulationResultWindow::saveGraphtoFile(const QString &HomeDir, const QString &UpperDir, const QString &Title)
{

    QString dir;

    dir = HomeDir + "/graphs";

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
        << "\t\t Package Sent: "
        << "\t\t Unsuccess Reservation: "
        <<" \n\n";


    for(int i = 0; i<Sample_Count; i++)
    {
        out << Sample_Names[i]
            << "\t\t " << QString::number(Collusion_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Buffer_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(DataRate_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Delay_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Avarage_Delay_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Dropped_Pack_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Total_Package_Sent_Series->at(i).y()).leftJustified(8,'0')
            << "\t\t " << QString::number(Reservation_Series->at(i).y()).leftJustified(8,'0')
            <<" \n";
    }

    Sample_Count = 0;

}

void SimulationResultWindow::closeButton1Clicked()
{
    this->close();

}

void SimulationResultWindow::nextButton1Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);

}

void SimulationResultWindow::previousButton1Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void SimulationResultWindow::closeButton2Clicked()
{
    this->close();
}

void SimulationResultWindow::nextButton2Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void SimulationResultWindow::previousButton2Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void SimulationResultWindow::closeButton3Clicked()
{
    this->close();
}

void SimulationResultWindow::nextButton3Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void SimulationResultWindow::previousButton3Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void SimulationResultWindow::closeButton4Clicked()
{
    this->close();
}

void SimulationResultWindow::nextButton4Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void SimulationResultWindow::previousButton4Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void SimulationResultWindow::closeButton5Clicked()
{
    this->close();
}

void SimulationResultWindow::nextButton5Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void SimulationResultWindow::previousButton5Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void SimulationResultWindow::closeButton6Clicked()
{
    this->close();
}

void SimulationResultWindow::nextButton6Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void SimulationResultWindow::previousButton6Clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
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
    addTotalPackageSentValue(Output.Max_Total_Sent_Package);
    addReservationValue(Output.Max_Unsuccesfull_Reservation);



}
