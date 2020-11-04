#ifndef PEER_H
#define PEER_H

#include <memory>
#include <QRandomGenerator>

#define PACKAGE_SIZE    2048    //bytes


struct TimeSlots;
struct PeerOutput;
struct InputInfo;


struct PeerOutput
{
    double Collusion_;
    double Data_Rate;
    double Total_Package_Sent;
    double Dropped_Packages;
    double Delay_;
    double Buffer_;
    double Unsuccessful_Reservation;

    void reset()
    {
        Collusion_ = 0;
        Data_Rate = 0;
        Total_Package_Sent = 0;
        Delay_ = 0;
        Buffer_ = 0;
        Dropped_Packages = 0;
        Unsuccessful_Reservation = 0;

    }
};

class Peer
{

public:

    double Desired_DataRate;
    double Transmission_Delay;
    double PackageTransfer_PerSlot;
    int Current_DataRate;
    int Available_Buffer;
    int Current_Buffer;
    double Total_Package_Generated;
    double Dropped_Packages;
    double Queued_Packets;
    double Total_Package_Sent;
    double Failed_Reservation;
    double Reservation_Count;
    int Total_Beacon_Slot_Number;
    double Beacon_Slot_Lenght;
    int Total_Cap_Slot_Number;
    double Cap_Slot_Lenght;
    int Total_Cfp_Slot_Number;
    double Cfp_Slot_Lenght;
    int Slot_Counter;
    int Cap_Request;
    int Collusion;
    int Max_Rety_Count;
    double Past_Time;
    double Delay_Time;

    bool Data_Sent;
    bool Enabled_BufferOverflow;
    bool Random_Slot_Selected;

    Peer(int id, const InputInfo &Input);
    ~Peer();

    PeerOutput *beacon(const TimeSlots &Slots);
    int cap(int SlotNumber);
    int cfp(int SlotNumber);

    void callBackCapResponse(bool CollutionOccured, int CfpSlotStart, int SlotLenght);
    void reset();
    PeerOutput Peer_Output;

private:
    volatile int Peer_Id;

    volatile int Contantion_Window;
    volatile int Random_CapSlot;
    volatile int Rety_Count;

    volatile bool Reservation_Succesfull;

    volatile int Own_Cfp_Slot_Start;
    volatile int Own_Cfp_Slot_Lenght;

    TimeSlots *Time_Slots;

    void getRandomSlot();
    void generatePackage();

};


#endif // PEER_H
