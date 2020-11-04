#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <iostream>
#include <vector>
#include <QString>
#include "peer.h"

#define REQUEST     0
#define RESPONSE    1

#define MAX_USER    20


struct TimeSlots
{
    int Becon_Slot_Number;
    int Cap_Slot_Number;
    int Cfp_Slot_Number;
    int Slot_Lenght;
};



struct PeerInfo
{
    double Desired_DataRate;
    double Transmission_Delay;
    int Peer_Buffer;
    int Rety_Count;
};





struct OutputInfo
{
    PeerOutput *Peer_Output[MAX_USER];
    double Total_Collution;
    int Super_Frame_Duration;

};



struct InputInfo
{

    std::vector<PeerInfo> Peer_List;
    int beacon_slot_num;
    int cap_slot_num;
    int Cfp_Slot_Per;
    double Beacon_Slot_Lenght;
    double Cap_Slot_Lenght;
    double Cfp_Slot_Lenght;
    double Slot_Duration;
    int Simulation_Duration;
    QString Simulation_Name;
    bool Enable_Buffer_Overflow;
    bool Enable_Simulation_Graph;


};


class Coordinator
{

public:
    Coordinator();
    ~Coordinator();

    std::vector<std::unique_ptr<Peer>> Peer_List;

    TimeSlots Time_Slots;
    OutputInfo Output_Info;
    InputInfo Input_Info;

    int Cfp_Slot_Per;
    int Total_Collution;
    int Total_Cap_Request;
    int Super_Frame_Duration;

    OutputInfo *ping();
    void beacon();
    void cap(int SLotNum);
    void cfp(int SLotNum);
    void setInputInformation(const InputInfo &Input);
    void reset();
private:

    int Ping_Counter;
};

#endif // COORDINATOR_H
