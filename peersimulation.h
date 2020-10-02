#ifndef PEERSIMULATION_H
#define PEERSIMULATION_H

#include <QVector>
#include <QPointF>

#include "coordinator.h"

struct PeerSimulationOutput
{

    int Max_Unsuccesfull_Reservation;
    int Max_Buffer_Value;
    int Max_Dropped_Package_Value;
    int Max_Delay;
    double Avarage_Delay_Value;
    double Max_DataRate_Value;
    double Max_Total_Collusion_Value;

    void reset()
    {
        Max_Unsuccesfull_Reservation = 0;
        Max_Buffer_Value = 0;
        Max_Dropped_Package_Value = 0;
        Max_Delay = 0;
        Avarage_Delay_Value = 0;
        Max_DataRate_Value = 0;
        Max_Total_Collusion_Value = 0;
    }

};



class PeerSimulation
{
public:
    PeerSimulation(int Id, const InputInfo &Input);
    ~PeerSimulation();

    void refreshValues(PeerOutput *Output, OutputInfo *Total_Output);
    void setFormTitle(const QString &Title);
    void setTitle(const QString &Title);
    void setInputInfo(int Id, const InputInfo &Input);
    void saveGraphInfo(const QString &Dir);
    const PeerSimulationOutput &getPeerSimulationOutput();

private:


    int id;
    int Max_Unsuc_Reservation_Value;
    int Max_Buffer_Value;
    double Max_Dropped_Backage;
    double Max_DataRate_Value;
    double Max_Total_Collusion_Value;
    double Max_Peer_Collusion_Value;
    double Max_Delay_Value;
    double Max_Avarage_Delay_Value;

    double Avarage_Delay_Value;

    int Sample_Count;
    int Total_Slot;

    QString Title_;

    PeerSimulationOutput Peer_Simulation_Output;

    QVector<QPointF> Collution_Values;
    QVector<QPointF> DataRate_Values;
    QVector<QPointF> Delay_Values;
    QVector<QPointF> Buffer_Values;
    QVector<QPointF> Dropped_Pack_Values;
    QVector<QPointF> Reservation_Values;

    void addCollusionValue(double Value);
    void addDataRateValue(double Value);
    void addAvarageDelayValue(int Value);
    void addDelayValue(int Value);

    void addBufferValue(int Value);
    void addDroppedPackValue(int Value);
    void addReservationValue(int Value);
};

#endif // PEERSIMULATION_H
