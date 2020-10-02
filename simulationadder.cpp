#include "simulationadder.h"
#include "mainwindow.h"
#include "simulation.h"



SimulationAdder::SimulationAdder(MainWindow *Window)
{
    Main_Window = Window;
}


void SimulationAdder::autoAddSimulationIncreasingCap(const InputInfo &Input)
{
    InputInfo input = Input;

    Main_Window->clearSimulationList();

    for(int k=0; k<25; k++)
    {
        input.cap_slot_num = Input.cap_slot_num;

        for(int i=0; i<20; i++)
        {

            input.Simulation_Name = QString("Cap:") + QString::number(input.cap_slot_num);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {
                double estimated_datarate = (double)((PACKAGE_SIZE * 8) * input.Cfp_Slot_Per) /
                        ((1 + input.cap_slot_num + (input.Peer_List.size() * input.Cfp_Slot_Per)) * input.Slot_Lenght);

                input.Peer_List[i].Data_Rate = estimated_datarate;
                input.Peer_List[i].Peer_Buffer = (input.Cfp_Slot_Per * input.Peer_List.size()) +
                        input.cap_slot_num + 1;
                input.Peer_List[i].Rety_Count = 5;


            }

            Main_Window->addSimulation(input);

            input.cap_slot_num += 1;

        }

        Main_Window->setSimulationArrayListName(QString("Cfp:") + QString::number(input.Cfp_Slot_Per));
        Main_Window->importListToArray();
        Main_Window->clearSimulationList();

        input.Cfp_Slot_Per++;
    }
}



void SimulationAdder::autoAddSimulationIncreasingCfp(const InputInfo &Input)
{

    InputInfo input = Input;

    Main_Window->clearSimulationList();

    for(int k=0; k<25; k++)
    {
        input.Cfp_Slot_Per = Input.Cfp_Slot_Per;

        for(int i=0; i<20; i++)
        {

            input.Simulation_Name = QString("Cfp:") + QString::number(input.Cfp_Slot_Per);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {
                double estimated_datarate = (double)((PACKAGE_SIZE * 8) * input.Cfp_Slot_Per) /
                        ((1 + input.cap_slot_num + (input.Peer_List.size() * input.Cfp_Slot_Per)) * input.Slot_Lenght);

                input.Peer_List[i].Data_Rate = estimated_datarate;
                input.Peer_List[i].Peer_Buffer = (input.Cfp_Slot_Per * input.Peer_List.size()) +
                        input.cap_slot_num + 1;
                input.Peer_List[i].Rety_Count = 5;


            }

            Main_Window->addSimulation(input);

            input.Cfp_Slot_Per += 1;

        }

        Main_Window->setSimulationArrayListName(QString("Cap:") + QString::number(input.cap_slot_num));
        Main_Window->importListToArray();
        Main_Window->clearSimulationList();

        input.cap_slot_num++;
    }



}




void SimulationAdder::autoAddSimulationIncreasingUser(const InputInfo &Input)
{
    InputInfo input = Input;

    Main_Window->clearSimulationList();



    for(int k=0; k<9; k++)
    {
        double estimated_datarate = (double)((PACKAGE_SIZE * 8) * input.Cfp_Slot_Per) /
                ((1 + input.cap_slot_num + (input.Peer_List.size() * input.Cfp_Slot_Per)) * input.Slot_Lenght);

        int estimated_buffer = (input.Cfp_Slot_Per * input.Peer_List.size()) +
                                input.cap_slot_num + 1;

        input.Simulation_Name = QString("User:") + QString::number(input.Peer_List.size());

        for(int i = 0; i<(int)input.Peer_List.size(); i++)
        {
            input.Peer_List[i].Data_Rate = estimated_datarate;
            input.Peer_List[i].Peer_Buffer = estimated_buffer;
            input.Peer_List[i].Rety_Count = 5;

        }

        Main_Window->addSimulation(input);


        if(k < 8)
            input.Peer_List.push_back(PeerInfo());


    }
}

