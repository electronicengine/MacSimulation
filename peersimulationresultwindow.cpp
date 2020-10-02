//#include <QDir>
//#include <QFile>
//#include <QTextStream>
//#include <iostream>
//#include <cmath>
//#include "peersimulationresultwindow.h"
//#include "ui_peersimulationresultwindow.h"

//PeerSimulationResultWindow::PeerSimulationResultWindow(int Id, const InputInfo &Input, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::PeerSimulationResultWindow),
//    Peer_Simulation_Output{0,0,0,0,0,0}
//{

//    ui->setupUi(this);

//    Sample_Count = 0;

//    Avarage_Delay_Value = 0;
//    Max_Peer_Collusion_Value = 0;
//    Max_Total_Collusion_Value = 0;
//    Max_Buffer_Value = 0;
//    Max_DataRate_Value = 0;
//    Max_Dropped_Backage = 0;
//    Total_Slot = 0;
//    Max_Delay_Value = 0;
//    Max_Unsuc_Reservation_Value = 0;
////    Title_ = Input.Simulation_Name;

////    setupBufferGraph();
////    setupCollusionGraph();
////    setupDataRateGraph();
////    setupDelayGraph();
////    setupDroppedPackGraph();
////    setupReservationGraph();

////    setInputInfo(Id, Input);

//    //std::cout << "PeerSimulationResultWindow::"<< std::to_string(id)  << std::endl;


//}



//PeerSimulationResultWindow::~PeerSimulationResultWindow()
//{
//    //std::cout << "PeerSimulationResultWindow::~" << std::to_string(id) << std::endl;

//    delete ui;
//}



//void PeerSimulationResultWindow::setFormTitle(const QString &Title)
//{
//    this->setWindowTitle(Title);
//}



//void PeerSimulationResultWindow::setTitle(const QString &Title)
//{
//    Title_ = Title;
//}



//void PeerSimulationResultWindow::setInputInfo(int Id, const InputInfo &Input)
//{

//    ui->user_number->setText(QString::number(Input.Peer_List.size()));
//    ui->cfp_slotper->setText(QString::number(Input.Cfp_Slot_Per));
//    ui->cap_slot->setText(QString::number(Input.cap_slot_num));
//    ui->slot_lenght->setText(QString::number(Input.Slot_Lenght));
//    ui->supported_datarate->setText(QString::number(Input.Peer_List[Id].Data_Rate));
//    ui->available_buffer->setText(QString::number(Input.Peer_List[Id].Peer_Buffer));


//}



//void PeerSimulationResultWindow::saveGraphInfo(const QString &Dir)
//{


////    Collusion_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Total_Collusion_Value);
////    Collusion_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
//    ui->collusion_total_st->setText(QString::number(Collution_Values[Sample_Count - 1].y()));

////    Collusion_Series->replace(Collution_Values);


////    DataRate_Chart->axes(Qt::Vertical).back()->setRange(0, Max_DataRate_Value);
////    DataRate_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
//    ui->datarate_max->setText(QString::number(Max_DataRate_Value));
//    ui->datarate_st->setText(QString::number(DataRate_Values[Sample_Count - 1].y()));

////    DataRate_Series->replace(DataRate_Values);


////    Buffer_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Buffer_Value);
////    Buffer_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
//    ui->buffer_max->setText(QString::number(Max_Buffer_Value));
//    ui->buffer_st->setText(QString::number(Buffer_Values[Sample_Count - 1].y()));

////    Buffer_Series->replace(Buffer_Values);


////    Dropped_Pack_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Dropped_Backage);
////    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);
//    ui->dropped_package_max->setText(QString::number(Max_Dropped_Backage));
//    ui->dropped_package_st->setText(QString::number(Dropped_Pack_Values[Sample_Count - 1].y()));

////    Dropped_Pack_Series->replace(Dropped_Pack_Values);

////    Delay_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Delay_Value);
////    Delay_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);

//    Avarage_Delay_Value /= Sample_Count;

//    ui->delay_avarage->setText(QString::number(Avarage_Delay_Value));
//    ui->delay_st->setText(QString::number(Delay_Values[Sample_Count - 1].y()));

////    Delay_Series->replace(Delay_Values);


////    Reservation_Chart->axes(Qt::Vertical).back()->setRange(0, Max_Unsuc_Reservation_Value);
////    Reservation_Chart->axes(Qt::Horizontal).back()->setRange(0, Sample_Count);

//    ui->reservation_max->setText(QString::number(Max_Unsuc_Reservation_Value));
//    ui->reservation_st->setText(QString::number(Delay_Values[Sample_Count - 1].y()));

////    Reservation_Series->replace(Delay_Values);

////    QPixmap pic = this->grab();
////    this->render(&pic);
////    pic.save(Dir + "/" + windowTitle() + ".png");

//    QFile file(Dir + "/" + windowTitle() + ".log");
//    file.open(QIODevice::WriteOnly | QIODevice::Text);

//    QTextStream out(&file);


//    out << "\t\t Collusion: "
//        << "\t\t Buffer: "
//        << "\t\t DataRate: "
//        << "\t\t Delay: "
//        << "\t\t Drop: "
//        << "\t\t Unsuccess Reservation: "
//        <<" \n\n";

//    for(int i = 0; i<Sample_Count; i++)
//    {
//        out << i
//            << "\t\t " << QString::number(Collution_Values[i].y()).leftJustified(8,'0')
//            << "\t\t " << QString::number(Buffer_Values[i].y()).rightJustified(8,'0')
//            << "\t\t " << QString::number(DataRate_Values[i].y()).leftJustified(8,'0')
//            << "\t\t " << QString::number(Delay_Values[i].y()).rightJustified(8,'0')
//            << "\t\t " << QString::number(Dropped_Pack_Values[i].y()).rightJustified(8,'0')
//            << "\t\t " << QString::number(Reservation_Values[i].y()).rightJustified(8,'0')
//            <<" \n";
//    }

//    Collution_Values.clear();

//    Buffer_Values.clear();

//    DataRate_Values.clear();

//    Delay_Values.clear();

//    Dropped_Pack_Values.clear();

//    Reservation_Values.clear();

//}



//const PeerSimulationOutput &PeerSimulationResultWindow::getPeerSimulationOutput()
//{
//    Peer_Simulation_Output.Max_Buffer_Value = ui->buffer_st->text().toInt();
//    Peer_Simulation_Output.Max_DataRate_Value = ui->datarate_st->text().toDouble();
//    Peer_Simulation_Output.Max_Total_Collusion_Value = ui->collusion_total_st->text().toDouble();
//    Peer_Simulation_Output.Avarage_Delay_Value = std::ceil(ui->delay_avarage->text().toDouble());
//    Peer_Simulation_Output.Max_Dropped_Package_Value = ui->dropped_package_max->text().toDouble();
//    Peer_Simulation_Output.Max_Unsuccesfull_Reservation = ui->reservation_max->text().toInt();

//    return Peer_Simulation_Output;
//}



//void PeerSimulationResultWindow::setupCollusionGraph()
//{

////    Collusion_Series = std::make_unique<QLineSeries>();

////    Collusion_Chart = std::make_unique<QChart>();

////    Collusion_Chart_View = std::make_unique<QChartView>(Collusion_Chart.get());

////    Collusion_Chart->legend()->hide();
////    Collusion_Chart->addSeries(Collusion_Series.get());
////    Collusion_Chart->setTitle("Collusion Rate (Per Cap Request) & Time");
////    Collusion_Chart->createDefaultAxes();
////    Collusion_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    Collusion_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));
////    Collusion_Chart->axes(Qt::Horizontal).back()->setRange(0, 30);

////    Collusion_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    Collusion_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);
////    Collusion_Chart->axes(Qt::Vertical).back()->setRange(0, 10);

////    Collusion_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    Collusion_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    Collusion_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    Collusion_Chart_View->setRenderHint(QPainter::Antialiasing);
////    Collusion_Chart_View->setParent(ui->collusion_graph_peer);
////    Collusion_Chart_View->resize(ui->collusion_graph_peer->size());

////    Collusion_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

//}



//void PeerSimulationResultWindow::setupDataRateGraph()
//{

////    DataRate_Series = std::make_unique<QLineSeries>();

////    DataRate_Chart = std::make_unique<QChart>();

////    DataRate_Chart_View = std::make_unique<QChartView>(DataRate_Chart.get());


////    DataRate_Chart->legend()->hide();
////    DataRate_Chart->addSeries(DataRate_Series.get());
////    DataRate_Chart->setTitle("DataRate (KBPS) & Time");
////    DataRate_Chart->createDefaultAxes();
////    DataRate_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    DataRate_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

////    DataRate_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    DataRate_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

////    DataRate_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    DataRate_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    DataRate_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    DataRate_Chart_View->setRenderHint(QPainter::Antialiasing);
////    DataRate_Chart_View->setParent(ui->datarate_graph);
////    DataRate_Chart_View->resize(ui->datarate_graph->size());

////    DataRate_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);


//}



//void PeerSimulationResultWindow::setupDelayGraph()
//{

////    Delay_Series = std::make_unique<QLineSeries>();

////    Delay_Chart = std::make_unique<QChart>();

////    Delay_Chart_View = std::make_unique<QChartView>(Delay_Chart.get());

////    Delay_Chart->legend()->hide();
////    Delay_Chart->addSeries(Delay_Series.get());
////    Delay_Chart->setTitle("Latency (Slot Number) & Time");
////    Delay_Chart->createDefaultAxes();
////    Delay_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    Delay_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

////    Delay_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    Delay_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

////    Delay_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    Delay_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    Delay_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    Delay_Chart_View->setRenderHint(QPainter::Antialiasing);
////    Delay_Chart_View->setParent(ui->delay_graph);
////    Delay_Chart_View->resize(ui->delay_graph->size());

////    Delay_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

//}



//void PeerSimulationResultWindow::setupBufferGraph()
//{


////    Buffer_Series = std::make_unique<QLineSeries>();

////    Buffer_Chart = std::make_unique<QChart>();

////    Buffer_Chart_View = std::make_unique<QChartView>(Buffer_Chart.get());


////    Buffer_Chart->legend()->hide();
////    Buffer_Chart->addSeries(Buffer_Series.get());
////    Buffer_Chart->setTitle("Buffer (Package) & Time");
////    Buffer_Chart->createDefaultAxes();
////    Buffer_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    Buffer_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

////    Buffer_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    Buffer_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

////    Buffer_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    Buffer_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    Buffer_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    Buffer_Chart_View->setRenderHint(QPainter::Antialiasing);
////    Buffer_Chart_View->setParent(ui->buffer_graph_peer);
////    Buffer_Chart_View->resize(ui->buffer_graph_peer->size());

////    Buffer_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);

//}

//void PeerSimulationResultWindow::setupDroppedPackGraph()
//{
////    Dropped_Pack_Series = std::make_unique<QLineSeries>();

////    Dropped_Pack_Chart = std::make_unique<QChart>();

////    Dropped_Pack_Chart_View = std::make_unique<QChartView>(Dropped_Pack_Chart.get());


////    Dropped_Pack_Chart->legend()->hide();
////    Dropped_Pack_Chart->addSeries(Dropped_Pack_Series.get());
////    Dropped_Pack_Chart->setTitle("Drop (Package) & Time");
////    Dropped_Pack_Chart->createDefaultAxes();
////    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    Dropped_Pack_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

////    Dropped_Pack_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    Dropped_Pack_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

////    Dropped_Pack_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    Dropped_Pack_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    Dropped_Pack_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    Dropped_Pack_Chart_View->setRenderHint(QPainter::Antialiasing);
////    Dropped_Pack_Chart_View->setParent(ui->dropped_package_graph);
////    Dropped_Pack_Chart_View->resize(ui->dropped_package_graph->size());

////    Dropped_Pack_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);
//}

//void PeerSimulationResultWindow::setupReservationGraph()
//{
////    Reservation_Series = std::make_unique<QLineSeries>();

////    Reservation_Chart = std::make_unique<QChart>();

////    Reservation_Chart_View = std::make_unique<QChartView>(Reservation_Chart.get());


////    Reservation_Chart->legend()->hide();
////    Reservation_Chart->addSeries(Reservation_Series.get());
////    Reservation_Chart->setTitle("Failed Reservation & Time");
////    Reservation_Chart->createDefaultAxes();
////    Reservation_Chart->axes(Qt::Horizontal).back()->setGridLineVisible(false);
////    Reservation_Chart->axes(Qt::Horizontal).back()->setLabelsColor(QColor(114, 159, 207));

////    Reservation_Chart->axes(Qt::Vertical).back()->setLabelsColor(QColor(114, 159, 207));
////    Reservation_Chart->axes(Qt::Vertical).back()->setGridLineVisible(false);

////    Reservation_Chart->setTitleBrush(QBrush(QColor(114, 159, 207)));
////    Reservation_Chart->setBackgroundBrush(QBrush(QColor(46, 52, 54)));
////    Reservation_Chart->setPlotAreaBackgroundBrush(QBrush(QColor(46, 52, 54)));

////    Reservation_Chart_View->setRenderHint(QPainter::Antialiasing);
////    Reservation_Chart_View->setParent(ui->reservation_graph);
////    Reservation_Chart_View->resize(ui->reservation_graph->size());

////    Reservation_Chart_View->setRubberBand(QChartView::HorizontalRubberBand);
//}



//void PeerSimulationResultWindow::addCollusionValue(double Value)
//{

//    if(Value > Max_Total_Collusion_Value)
//    {
//        Max_Total_Collusion_Value = Value;
//    }

//    Collution_Values.append(QPointF(Sample_Count, Value));



//}



//void PeerSimulationResultWindow::addDataRateValue(double Value)
//{

//    if(Value > Max_DataRate_Value)
//    {

//        Max_DataRate_Value = Value;


//    }

//    DataRate_Values.append(QPointF(Sample_Count, Value));


//}



//void PeerSimulationResultWindow::addDelayValue(int Value)
//{

//    if(Value > Max_Delay_Value)
//    {

//        Max_Delay_Value = Value;

//    }


//    Delay_Values.append(QPointF(Sample_Count, Value));

//    Avarage_Delay_Value += Value;

//}



//void PeerSimulationResultWindow::addBufferValue(int Value)
//{

//    if(Value > Max_Buffer_Value)
//    {
//        Max_Buffer_Value = Value;


//    }

//    Buffer_Values.append(QPointF(Sample_Count, Value));


//}



//void PeerSimulationResultWindow::addDroppedPackValue(int Value)
//{
//    if(Value > Max_Dropped_Backage)
//    {
//        Max_Dropped_Backage = Value;

//    }

//    Dropped_Pack_Values.append(QPointF(Sample_Count, Value));

//}



//void PeerSimulationResultWindow::addReservationValue(int Value)
//{
//    if(Value > Max_Unsuc_Reservation_Value)
//    {
//        Max_Unsuc_Reservation_Value = Value;

//    }

//    Reservation_Values.append(QPointF(Sample_Count, Value));
//}



//void PeerSimulationResultWindow::refreshValues(PeerOutput *Output, OutputInfo *Total_Output)
//{

//    Total_Slot += Total_Output->Super_Frame_Duration;

//    addCollusionValue(Total_Output->Total_Collution);
//    addBufferValue(Output->Buffer_);
//    addDataRateValue(Output->Data_Rate);
//    addDelayValue(Output->Delay_);
//    addDroppedPackValue(Output->Dropped_Packages);
//    addReservationValue(Output->Unsuccessful_Reservation);

//    ui->avarage_super_frame_duration->setText(QString::number(Total_Slot /
//                                                              ((Sample_Count == 0) ? 1 : Sample_Count)));

//    if(Output->Collusion_ > Max_Peer_Collusion_Value)
//    {
//        Max_Peer_Collusion_Value = Output->Collusion_;
//        ui->collustion_peer_st->setText(QString::number(Max_Peer_Collusion_Value));
//    }

//    Sample_Count++;
//}
