#include "peersimulation.h"
#include <QFile>
#include <QVector>
#include <QPointF>
#include <cmath>
#include <QTextStream>



PeerSimulation::PeerSimulation(int Id, const InputInfo &Input) : Peer_Simulation_Output{0,0,0,0,0,0,0,0}
{

    Sample_Count = 0;

    Avarage_Delay_Value = 0;
    Max_Peer_Collusion_Value = 0;
    Max_Total_Collusion_Value = 0;
    Max_Buffer_Value = 0;
    Max_DataRate_Value = 0;
    Max_Dropped_Backage = 0;
    Total_Slot = 0;
    Max_Delay_Value = 0;
    Max_Unsuc_Reservation_Value = 0;
    Max_Total_Sent_Package = 0;

    Save_Log = Input.Enable_Simulation_Graph;

    Title_ = Input.Simulation_Name;

    (void)(Id);
    (void)(Input);


}



PeerSimulation::~PeerSimulation()
{

}



void PeerSimulation::setFormTitle(const QString &Title)
{
    Title_ = Title;
//    this->setWindowTitle(Title);
}



void PeerSimulation::setTitle(const QString &Title)
{
    Title_ = Title;
}



void PeerSimulation::setInputInfo(int Id, const InputInfo &Input)
{
    (void)(Id);
    (void)(Input);

    if(Save_Log == true)
    {
//        ui->user_number->setText(QString::number(Input.Peer_List.size()));
//        ui->cfp_slotper->setText(QString::number(Input.Cfp_Slot_Per));
//        ui->cap_slot->setText(QString::number(Input.cap_slot_num));
//        ui->slot_lenght->setText(QString::number(Input.Slot_Lenght));
//        ui->supported_datarate->setText(QString::number(Input.Peer_List[Id].Data_Rate));
//        ui->available_buffer->setText(QString::number(Input.Peer_List[Id].Peer_Buffer));
    }


}



void PeerSimulation::saveGraphInfo(const QString &Dir)
{


    if(Save_Log == true)
    {
        QFile file(Dir + "/" + Title_ + ".log");
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream out(&file);


        out << "\t\t Collusion: "
            << "\t\t Buffer: "
            << "\t\t DataRate: "
            << "\t\t Delay: "
            << "\t\t Drop: "
            << "\t\t Unsuccess Reservation: "
            <<" \n\n";

        for(int i = 0; i<Sample_Count; i++)
        {
            out << i
                << "\t\t " << QString::number(Collution_Values[i].y()).rightJustified(8,'0')
                << "\t\t " << QString::number(Buffer_Values[i].y()).rightJustified(8,'0')
                << "\t\t " << QString::number(DataRate_Values[i].y()).rightJustified(8,'0')
                << "\t\t " << QString::number(Delay_Values[i].y()).rightJustified(8,'0')
                << "\t\t " << QString::number(Dropped_Pack_Values[i].y()).rightJustified(8,'0')
                << "\t\t " << QString::number(Reservation_Values[i].y()).rightJustified(8,'0')
                <<" \n";
        }

        Collution_Values.clear();
        Collution_Values.squeeze();

        Buffer_Values.clear();
        Buffer_Values.squeeze();

        DataRate_Values.clear();
        DataRate_Values.squeeze();

        Delay_Values.clear();
        Delay_Values.squeeze();

        Dropped_Pack_Values.clear();
        Dropped_Pack_Values.squeeze();

        Reservation_Values.clear();
        Reservation_Values.squeeze();

        Sample_Count = 0;
    }


    (void)Dir;

}



const PeerSimulationOutput &PeerSimulation::getPeerSimulationOutput()
{
    Peer_Simulation_Output.Max_Buffer_Value = Max_Buffer_Value;
    Peer_Simulation_Output.Max_DataRate_Value = Max_DataRate_Value;
    Peer_Simulation_Output.Max_Total_Collusion_Value = Max_Total_Collusion_Value;
//    Peer_Simulation_Output.Max_Delay = Max_Delay_Value;
    Peer_Simulation_Output.Max_Delay = std::ceil(Avarage_Delay_Value);
    Peer_Simulation_Output.Avarage_Delay_Value = std::ceil(Avarage_Delay_Value);
    Peer_Simulation_Output.Max_Dropped_Package_Value = Max_Dropped_Backage;
    Peer_Simulation_Output.Max_Unsuccesfull_Reservation = Max_Unsuc_Reservation_Value;
    Peer_Simulation_Output.Max_Total_Sent_Package = Max_Total_Sent_Package;

    return Peer_Simulation_Output;
}




void PeerSimulation::addCollusionValue(double Value)
{


    Max_Total_Collusion_Value = Max_Total_Collusion_Value * (Sample_Count);

    Max_Total_Collusion_Value += Value;

    Max_Total_Collusion_Value /= (Sample_Count + 1);
    if(Save_Log == true)
        Collution_Values.append(QPointF(Sample_Count, Value));


}



void PeerSimulation::addDataRateValue(double Value)
{


    if(Save_Log == true)
        DataRate_Values.append(QPointF(Sample_Count, Value));

    Max_DataRate_Value = Max_DataRate_Value * (Sample_Count);

    Max_DataRate_Value += Value;

    Max_DataRate_Value /= (Sample_Count + 1);

}



void PeerSimulation::addDelayValue(double Value)
{

    if(Save_Log == true)
        Delay_Values.append(QPointF(Sample_Count, Value));

    Avarage_Delay_Value = Avarage_Delay_Value * (Sample_Count);

    Avarage_Delay_Value += Value;

    Avarage_Delay_Value /= (Sample_Count + 1);



}



void PeerSimulation::addBufferValue(double Value)
{

    if(Save_Log == true)
        Buffer_Values.append(QPointF(Sample_Count, Value));


    Max_Buffer_Value = Max_Buffer_Value * (Sample_Count);

    Max_Buffer_Value += (double)Value;

    Max_Buffer_Value /= (Sample_Count + 1);
}



void PeerSimulation::addDroppedPackValue(double Value)
{

    Max_Dropped_Backage = Max_Dropped_Backage * (Sample_Count);

    Max_Dropped_Backage += (double)Value;

    Max_Dropped_Backage /= (Sample_Count + 1);

    if(Save_Log == true)
        Dropped_Pack_Values.append(QPointF(Sample_Count, Value));


}



void PeerSimulation::addReservationValue(double Value)
{

    Max_Unsuc_Reservation_Value = Max_Unsuc_Reservation_Value * (Sample_Count);

    Max_Unsuc_Reservation_Value += (double)Value;

    Max_Unsuc_Reservation_Value /= (Sample_Count + 1);

    if(Save_Log == true)
        Reservation_Values.append(QPointF(Sample_Count, Value));

}



void PeerSimulation::addTotalSentPackage(double Value)
{

    Max_Total_Sent_Package = Max_Total_Sent_Package * (Sample_Count);

    Max_Total_Sent_Package += (double)Value;

    Max_Total_Sent_Package /= (Sample_Count + 1);


}



void PeerSimulation::refreshValues(PeerOutput *Output, OutputInfo *Total_Output)
{

    Total_Slot += Total_Output->Super_Frame_Duration;

    addCollusionValue(Total_Output->Total_Collution);
    addBufferValue(Output->Buffer_);
    addDataRateValue(Output->Data_Rate);
    addDelayValue(Output->Delay_);
    addDroppedPackValue(Output->Dropped_Packages);
    addReservationValue(Output->Unsuccessful_Reservation);
    addTotalSentPackage(Output->Total_Package_Sent);

    if(Output->Collusion_ > Max_Peer_Collusion_Value)
    {
        Max_Peer_Collusion_Value = Output->Collusion_;
    }

    Sample_Count++;
}
