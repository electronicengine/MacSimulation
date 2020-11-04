#include "peer.h"
#include "coordinator.h"
#include "QRandomGenerator"
#include "logging.h"

#include <iostream>
#include <cstdlib>
#include <ctime>



Peer::Peer(int Id, const InputInfo &Input) :
    Peer_Output{0, 0, 0, 0, 0, 0, 0}

{

    Total_Package_Sent = 0;
    Queued_Packets = 0;
    Rety_Count = 0;
    Own_Cfp_Slot_Start = 0;
    Own_Cfp_Slot_Lenght = 0;
    Contantion_Window = 0;
    Reservation_Count = 0;
    Failed_Reservation = 0;
    Reservation_Succesfull = false;
    Random_CapSlot = 0;
    Slot_Counter = 0;
    Cap_Request = 0;
    Collusion = 0;
    Dropped_Packages = 0;
    Random_Slot_Selected = false;
    Total_Package_Generated = 0;
    Total_Beacon_Slot_Number = 0;
    Total_Cap_Slot_Number = 0;
    Total_Cfp_Slot_Number = 0;
    Past_Time = 0;

    Data_Sent = true;

    Peer_Id = Id;
    Max_Rety_Count = Input.Peer_List[Id].Rety_Count;
    Desired_DataRate = Input.Peer_List[Id].Desired_DataRate;
    Transmission_Delay = Input.Peer_List[Id].Transmission_Delay;
    Available_Buffer = Input.Peer_List[Id].Peer_Buffer;
    Enabled_BufferOverflow = Input.Enable_Buffer_Overflow;

    Beacon_Slot_Lenght = Input.Beacon_Slot_Lenght;
    Cap_Slot_Lenght = Input.Cap_Slot_Lenght;
    Cfp_Slot_Lenght = Input.Cfp_Slot_Lenght;

    PackageTransfer_PerSlot = ((double)((Cfp_Slot_Lenght) / Transmission_Delay));

    Logging::printAll((Logging::LogColor)Id, "PackageTransfer_PerSlot : ", std::to_string(PackageTransfer_PerSlot));

}



Peer::~Peer()
{
}



PeerOutput *Peer::beacon(const TimeSlots &Slots)
{

    Total_Beacon_Slot_Number++;
    Time_Slots = const_cast<TimeSlots *>(&Slots);

    generatePackage();

    Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id), " - Beacon ");

    Reservation_Succesfull = false;
    getRandomSlot();

    Peer_Output.Data_Rate = (double)(Total_Package_Sent * PACKAGE_SIZE * 8 )
            / ((Total_Beacon_Slot_Number * Beacon_Slot_Lenght) +
               (Total_Cap_Slot_Number * Cap_Slot_Lenght) +
               (Total_Cfp_Slot_Number * Cfp_Slot_Lenght));


    return &Peer_Output;
}



int Peer::cap(int SlotNumber)
{

    Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                      " - Cap Slot Num: ", std::to_string(SlotNumber));


    Total_Cap_Slot_Number++;

    if(Random_CapSlot == 0 && Reservation_Succesfull != true && Queued_Packets > 1 &&
            Random_Slot_Selected == true)
    {
        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id), " - Aloha Send ");


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
    Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id), " - Cfp Slot Num: ", std::to_string(SlotNumber));

    Total_Cfp_Slot_Number++;

    int total_time = (Beacon_Slot_Lenght * Total_Beacon_Slot_Number) +
            (Cap_Slot_Lenght * Total_Cap_Slot_Number) +
            (Cfp_Slot_Lenght * Total_Cfp_Slot_Number);


    if((SlotNumber >= Own_Cfp_Slot_Start) &&
            (SlotNumber < (Own_Cfp_Slot_Start + Own_Cfp_Slot_Lenght)))
    {

        if(std::floor(Queued_Packets) != 0)
        {
            if(SlotNumber == Own_Cfp_Slot_Start && Data_Sent == false)
            {
                Peer_Output.Delay_ = total_time - Delay_Time;
                Data_Sent = true;
            }


            if(SlotNumber == (Own_Cfp_Slot_Lenght + Own_Cfp_Slot_Start - 1)) // in the last cfp slot
            {
                int rounded = std::floor(Own_Cfp_Slot_Lenght * PackageTransfer_PerSlot);

                if(rounded > Queued_Packets)
                    rounded = std::floor(Queued_Packets);

                Queued_Packets = Queued_Packets - rounded;
                Total_Package_Sent = Total_Package_Sent + rounded;
                Peer_Output.Total_Package_Sent = (double)Total_Package_Sent / Total_Package_Generated;

                Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                                  " - Sending Package Number: ", rounded );
                Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                                  " - Queue Number: ", Queued_Packets);


                Own_Cfp_Slot_Lenght = 0;
                Own_Cfp_Slot_Start = 0;

            }
        }
    }

    return 0;
}



void Peer::callBackCapResponse(bool CollutionOccured, int CfpSlotStart, int SlotLenght)
{
    if(CollutionOccured == false)
    {
        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                          " - CallBackResponse");
        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                          " - CfpSlotStart ", std::to_string(CfpSlotStart));
        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                          " - SlotLenght ", std::to_string(SlotLenght));


        Reservation_Succesfull = true;
        Reservation_Count++;

        Contantion_Window = 0;
        Own_Cfp_Slot_Start = CfpSlotStart;
        Own_Cfp_Slot_Lenght = SlotLenght;
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
            Failed_Reservation++;

           Peer_Output.Unsuccessful_Reservation = (Failed_Reservation / (Reservation_Count + Failed_Reservation));
           Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                             " - Rety Count is Overflowed");

            Rety_Count = 0;
            Contantion_Window = 0;
        }

        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id), " - Collution Occured");

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
    Own_Cfp_Slot_Start = 0;
    Own_Cfp_Slot_Lenght = 0;
    Contantion_Window = 0;
    Reservation_Succesfull = false;
    Random_CapSlot = 0;
    Slot_Counter = 0;
    Cap_Request = 0;
    Collusion = 0;
    Dropped_Packages = 0;
    Past_Time = 0;

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

        Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                          " - Random Slot Selected: ",std::to_string(Random_CapSlot), "- Contantion Window: ",
                          std::to_string(Contantion_Window));

    }
}



void Peer::generatePackage()
{

    double total_time = (Beacon_Slot_Lenght * (double)Total_Beacon_Slot_Number) +
            (Cap_Slot_Lenght * (double)Total_Cap_Slot_Number) +
            (Cfp_Slot_Lenght * (double)Total_Cfp_Slot_Number);

    Past_Time = total_time - Past_Time;

    Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                      " - Total_Time: ", std::to_string(total_time), " ms",
                      " - Past_Time: ", std::to_string(Past_Time), " ms");

    Queued_Packets += (double) (Desired_DataRate * Past_Time) / (PACKAGE_SIZE * 8);

    Total_Package_Generated += (double) (Desired_DataRate * Past_Time) / (PACKAGE_SIZE * 8);

    Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id), " - Number Of Package: "
                      , std::to_string(Queued_Packets), " generated");


    if(Enabled_BufferOverflow == true)
    {
        if(std::floor(Queued_Packets) > Available_Buffer)
        {
            Dropped_Packages += (std::floor(Queued_Packets) - Available_Buffer);

            Logging::printAll((Logging::LogColor)Peer_Id, "Peer Id ", std::to_string(Peer_Id),
                              " - Number Of Package: ", std::to_string(Dropped_Packages), " dropped");


            double remain = Queued_Packets - (std::floor(Queued_Packets) - Available_Buffer)
                    - Available_Buffer;

            Queued_Packets = (double) Available_Buffer + remain;

        }
    }

    Peer_Output.Buffer_ = Queued_Packets / Available_Buffer;
    Peer_Output.Dropped_Packages = (double) Dropped_Packages / Total_Package_Generated;

    if(Data_Sent == true)
    {
        Delay_Time = total_time;
        Data_Sent = false;
    }

    Past_Time = total_time;

}
