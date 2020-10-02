#ifndef PEER_H
#define PEER_H

#include <memory>
#include <QRandomGenerator>

#define PACKAGE_SIZE    2000    //bytes


struct TimeSlots;
struct PeerOutput;
struct InputInfo;


struct PeerOutput
{
    double Collusion_;
    double Data_Rate;
    int Total_Package;
    int Delay_;
    int Buffer_;
    int Dropped_Packages;
    int Unsuccessful_Reservation;

    void reset()
    {
        Collusion_ = 0;
        Data_Rate = 0;
        Total_Package = 0;
        Delay_ = 0;
        Buffer_ = 0;
        Dropped_Packages = 0;
        Unsuccessful_Reservation = 0;

    }
};

class Peer
{

public:

    int Requested_DataRate;
    int Current_DataRate;
    int Max_Buffer;
    int Available_Buffer;
    int Current_Buffer;
    int Dropped_Packages;
    double Queued_Packets;
    int Total_Package_Sent;
    int SuperFrame_Slot_Number;
    int Total_Slot_Number;
    int Slot_Lenght;
    int Slot_Counter;
    int Cap_Request;
    int Collusion;
    int Delay_Counter;
    int Max_Rety_Count;

    bool Data_Sent;
    bool Enabled_BufferOverflow;

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

    volatile int Cfp_Slot_Start;
    volatile int Cfp_Slot_Lenght;

    TimeSlots *Time_Slots;

    void getRandomSlot();
    void generatePackage();

};


#endif // PEER_H
