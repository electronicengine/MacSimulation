#include "peer.h"
#include "coordinator.h"
#include "QRandomGenerator"
#include <iostream>
#include <cstdlib>
#include <ctime>


Peer::Peer(int Id, const InputInfo &Input) :
    Peer_Output{0, 0, 0, 0, 0, 0, 0}

{

    Total_Package_Sent = 0;
    Queued_Packets = 0;
    Rety_Count = 0;
    Cfp_Slot_Start = 0;
    Cfp_Slot_Lenght = 0;
    Contantion_Window = 0;
    SuperFrame_Slot_Number = 1;
    Total_Slot_Number = 0;
    Reservation_Succesfull = false;
    Random_CapSlot = 0;
    Slot_Counter = 0;
    Cap_Request = 0;
    Collusion = 0;
    Dropped_Packages = 0;
    Delay_Counter = 1;
    Random_Slot_Selected = false;

    Data_Sent = true;

    Peer_Id = Id;
    Max_Rety_Count = Input.Peer_List[Id].Rety_Count;
    Requested_DataRate = Input.Peer_List[Id].Data_Rate;
    Available_Buffer = Input.Peer_List[Id].Peer_Buffer;
    Enabled_BufferOverflow = Input.Enable_Buffer_Overflow;
    Slot_Lenght = Input.Slot_Lenght;

    //std::cout << "Peer::"<<  std::endl;

}



Peer::~Peer()
{
    //std::cout << "Peer::~"<<  std::endl;
}



PeerOutput *Peer::beacon(const TimeSlots &Slots)
{

    Time_Slots = const_cast<TimeSlots *>(&Slots);

    generatePackage();

    std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Beacon " << std::endl;

    Reservation_Succesfull = false;
    getRandomSlot();

    Total_Slot_Number += SuperFrame_Slot_Number;
    Peer_Output.Data_Rate = (double)(Total_Package_Sent * PACKAGE_SIZE * 8 )
            / (Total_Slot_Number * Slot_Lenght); // in KBPS

    SuperFrame_Slot_Number = 1;
    Slot_Counter++;


    return &Peer_Output;
}



int Peer::cap(int SlotNumber)
{

    std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Cap Slot Num: " << std::to_string(SlotNumber) << std::endl;
    (void)SlotNumber;

    SuperFrame_Slot_Number++;
    Slot_Counter++;

    if(Random_CapSlot == 0 && Reservation_Succesfull != true && Queued_Packets > 1 &&
            Random_Slot_Selected == true)
    {
        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Aloha Send " << std::endl;

        Random_Slot_Selected = false;

        Cap_Request++;
        if(Random_CapSlot != 0)
            Random_CapSlot--;

        return REQUEST;
    }
    else
    {
        if(Random_CapSlot != 0)
            Random_CapSlot--;

        return RESPONSE;
    }
}



int Peer::cfp(int SlotNumber)
{
    std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Cfp Slot Num: " << std::to_string(SlotNumber) << std::endl;

    SuperFrame_Slot_Number++;
    Slot_Counter++;

    if((SlotNumber >= Cfp_Slot_Start) &&
            (SlotNumber < (Cfp_Slot_Start + Cfp_Slot_Lenght)))
    {

        if(std::floor(Queued_Packets) != 0)
        {
            if(SlotNumber == Cfp_Slot_Start && Data_Sent == false)
            {
                Peer_Output.Delay_ = Slot_Counter - Delay_Counter;
                Data_Sent = true;
            }

            Queued_Packets--;

            Total_Package_Sent++;
            Peer_Output.Total_Package = Total_Package_Sent;

            std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Sending Package Number: " <<
                         Total_Package_Sent << std::endl;

            if(SlotNumber == (Cfp_Slot_Lenght + Cfp_Slot_Start - 1)) // in the last cfp slot
            {
                Cfp_Slot_Lenght = 0;
                Cfp_Slot_Start = 0;
            }
        }
    }

    return 0;
}



void Peer::callBackCapResponse(bool CollutionOccured, int CfpSlotStart, int SlotLenght)
{
    if(CollutionOccured == false)
    {
        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - CallBackResponse" << std::endl;
        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - CfpSlotStart " << std::to_string(CfpSlotStart) << std::endl;
        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - SlotLenght " << std::to_string(SlotLenght) << std::endl;

        Reservation_Succesfull = true;

        Contantion_Window = 0;
        Cfp_Slot_Start = CfpSlotStart;
        Cfp_Slot_Lenght = SlotLenght;
        Random_CapSlot = 0;

    }
    else
    {
        Collusion++;
        Peer_Output.Collusion_ = Collusion;

        Reservation_Succesfull = false;
        Rety_Count++;

        if(Rety_Count >= Max_Rety_Count)
        {
           Peer_Output.Unsuccessful_Reservation++;
            std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Rety Count is Overflowed" << std::endl;
            Rety_Count = 0;
            Contantion_Window = 0;
        }

        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Collution Occured" << std::endl;

        if(Contantion_Window != 0)
            Contantion_Window *= 2;
        else
            Contantion_Window = Time_Slots->Cap_Slot_Number;

        getRandomSlot();


    }
}



void Peer::reset()
{

    Total_Package_Sent = 0;
    Queued_Packets = 0;
    Rety_Count = 0;
    Cfp_Slot_Start = 0;
    Cfp_Slot_Lenght = 0;
    Contantion_Window = 0;
    SuperFrame_Slot_Number = 1;
    Total_Slot_Number = 0;
    Reservation_Succesfull = false;
    Random_CapSlot = 0;
    Slot_Counter = 0;
    Cap_Request = 0;
    Collusion = 0;
    Dropped_Packages = 0;
    Delay_Counter = 1;

    Data_Sent = true;



}



void Peer::getRandomSlot()
{

    if(Random_CapSlot == 0 && Random_Slot_Selected == false && std::floor(Queued_Packets) >= 1)
    {

        Random_Slot_Selected = true;

        if(Contantion_Window == 0)
            Contantion_Window = Time_Slots->Cap_Slot_Number;

        Random_CapSlot = rand() % Contantion_Window;

        std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Random Slot Selected: "
                  << std::to_string(Random_CapSlot) << "- Contantion Window: " << std::to_string(Contantion_Window) << std::endl;
    }
}



void Peer::generatePackage()
{


    double per_slot_bit = (double) Requested_DataRate * Slot_Lenght;
    std::cout << "Peer Id " << std::to_string(Peer_Id)
              << "per_slot_bit: " << std::to_string(per_slot_bit) << std::endl;
    double per_slot_pack = (double) per_slot_bit / (PACKAGE_SIZE * 8);
    std::cout << "Peer Id " << std::to_string(Peer_Id)
              << "per_slot_pack: " << std::to_string(per_slot_pack) << std::endl;


    Queued_Packets += per_slot_pack * (SuperFrame_Slot_Number);


    std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Number Of Package: "
              << std::to_string(Queued_Packets) << " generated" << std::endl;

//    if(Enabled_BufferOverflow == true)
//    {
        if(std::floor(Queued_Packets) > Available_Buffer)
        {
            Dropped_Packages += (std::floor(Queued_Packets) - Available_Buffer);

            std::cout << "Peer Id " << std::to_string(Peer_Id) << " - Number Of Package: "
                      << std::to_string(Dropped_Packages) << " dropped" << std::endl;

            double remain = Queued_Packets - (std::floor(Queued_Packets) - Available_Buffer)
                    - Available_Buffer;

            Queued_Packets = (double) Available_Buffer + remain;

        }
//    }

    Peer_Output.Buffer_ = Queued_Packets;
    Peer_Output.Dropped_Packages = Dropped_Packages;

    if(Data_Sent == true)
    {
        Delay_Counter = Slot_Counter;
        Data_Sent = false;
    }

}
