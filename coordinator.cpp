#include "coordinator.h"



Coordinator::Coordinator() : Time_Slots{0,0,0,0}
{
    Output_Info.Total_Collution = 0;
    Output_Info.Super_Frame_Duration = 0;
    Total_Collution = 0;
    Total_Cap_Request = 0;
    Ping_Counter = 0;

}



Coordinator::~Coordinator()
{

}



OutputInfo *Coordinator::ping()
{


    if(Ping_Counter == 0)
    {
        beacon();
        Ping_Counter++;

        return NULL;

    }
    else if(Ping_Counter >= Time_Slots.Becon_Slot_Number &&
            Ping_Counter < Time_Slots.Cap_Slot_Number + Time_Slots.Becon_Slot_Number )
    {
        cap(Ping_Counter - Time_Slots.Becon_Slot_Number);
        Ping_Counter++;

        return NULL;

    }
    else if(Ping_Counter >= (Time_Slots.Becon_Slot_Number + Time_Slots.Cap_Slot_Number) &&
            Ping_Counter < (Time_Slots.Becon_Slot_Number + Time_Slots.Cap_Slot_Number + Time_Slots.Cfp_Slot_Number))
    {
        cfp(Ping_Counter - (Time_Slots.Becon_Slot_Number + Time_Slots.Cap_Slot_Number));
        Ping_Counter++;

        return NULL;
    }
    else if(Ping_Counter >= (Time_Slots.Becon_Slot_Number + Time_Slots.Cap_Slot_Number + Time_Slots.Cfp_Slot_Number))
    {
        Ping_Counter = 1;
        beacon();

        if(Total_Cap_Request == 0)
            Output_Info.Total_Collution = 0;
        else
            Output_Info.Total_Collution = (double) Total_Collution / Total_Cap_Request;


        return &Output_Info;

    }
    else
    {
        return NULL;
    }

}



void Coordinator::beacon()
{

//    std::cout << "Coordinator BEACON" << std::endl;

    Time_Slots.Cfp_Slot_Number = 0;

    for(int i=0; i<Time_Slots.Becon_Slot_Number; i++)
    {
        for(size_t k=0; k<Peer_List.size(); k++)
        {
            Output_Info.Peer_Output[k] = Peer_List[k]->beacon(Time_Slots);
        }
    }

    Output_Info.Super_Frame_Duration = Super_Frame_Duration;
    Super_Frame_Duration = 1;
}



void Coordinator::cap(int SLotNum)
{

    std::vector<Peer *> requested_peer;
    int response = 0;

    for(size_t k=0; k<Peer_List.size(); k++)
    {
        response = Peer_List[k]->cap(SLotNum);
        if(response == REQUEST)
        {
            requested_peer.push_back(Peer_List[k].get());
        }
    }


    if(requested_peer.size() > 1)
    {
        Total_Cap_Request += (double)requested_peer.size();
        Total_Collution += (double)requested_peer.size();

//        std::cout << "There is number of " << std::to_string(requested_peer.size() - 1)
//                  << " collution occured!" << std::endl;

        for(size_t i=0; i<requested_peer.size(); i++)
            requested_peer[i]->callBackCapResponse(true, 0, 0);

        requested_peer.clear();
    }
    else if(requested_peer.size() == 1)
    {
        Total_Cap_Request++;

        if(requested_peer[0]->Queued_Packets <= Cfp_Slot_Per)
        {
            requested_peer[0]->callBackCapResponse(false,Time_Slots.Cfp_Slot_Number,
                                                   requested_peer[0]->Queued_Packets);
            Time_Slots.Cfp_Slot_Number += requested_peer[0]->Queued_Packets;

        }
        else
        {
            requested_peer[0]->callBackCapResponse(false,Time_Slots.Cfp_Slot_Number, Cfp_Slot_Per);
            Time_Slots.Cfp_Slot_Number += Cfp_Slot_Per;
        }


        requested_peer.clear();

    }
    else
    {
//        std::cout << "There is no cap request " << std::endl;

        requested_peer.clear();

    }

    Super_Frame_Duration++;
}



void Coordinator::cfp(int SLotNum)
{

    for(size_t k=0; k<Peer_List.size(); k++)
    {
        Peer_List[k]->cfp(SLotNum);
    }

    Super_Frame_Duration++;
}



void Coordinator::setInputInformation(const InputInfo &Input)
{

    Input_Info = Input;

    Time_Slots.Becon_Slot_Number = 1;
    Time_Slots.Cap_Slot_Number = Input_Info.cap_slot_num;
    Time_Slots.Cfp_Slot_Number = 0;
    Time_Slots.Slot_Lenght = Input_Info.Slot_Duration;

    Cfp_Slot_Per = Input_Info.Cfp_Slot_Per;

    Peer_List.clear();

    for(int i = 0; i<(int)Input_Info.Peer_List.size(); i++)
    {
//        std::cout << "Created Peer: * " << std::to_string(i) << std::endl;

        Peer_List.push_back(std::move(std::make_unique<Peer>(i, Input_Info)));
    }

}



void Coordinator::reset()
{

    Output_Info.Total_Collution = 0;
    Output_Info.Super_Frame_Duration = 0;
    Total_Collution = 0;
    Total_Cap_Request = 0;
    Ping_Counter = 0;


    Time_Slots.Becon_Slot_Number = 1;
    Time_Slots.Cap_Slot_Number = Input_Info.cap_slot_num;
    Time_Slots.Cfp_Slot_Number = 0;
    Time_Slots.Slot_Lenght = Input_Info.Slot_Lenght;

    Cfp_Slot_Per = Input_Info.Cfp_Slot_Per;

    Peer_List.clear();

    for(int i = 0; i<(int)Input_Info.Peer_List.size(); i++)
    {
        Peer_List.push_back(std::move(std::make_unique<Peer>(i, Input_Info)));
    }

}
