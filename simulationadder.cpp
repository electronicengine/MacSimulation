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
    int initial_cap_number = Input.cap_slot_num;
    Main_Window->clearSimulationList();

    for(int k=0; k<25; k++)
    {
        input.cap_slot_num = initial_cap_number;

        for(int i=0; i<20; i++)
        {

            input.Simulation_Name = QString("Cap:") + QString::number(input.cap_slot_num);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {
                double supported_datarate = (double)(PACKAGE_SIZE * 8) / input.Slot_Lenght;

                double bit_per_slot = (double)(input.Slot_Lenght * supported_datarate);

                double estimated_datarate = (double)(bit_per_slot * input.Cfp_Slot_Per) /
                        ((1 + input.cap_slot_num + (input.Peer_List.size() *input.Cfp_Slot_Per)) *
                         input.Slot_Lenght);

                int assumed_buffer = std::floor(
                        ((input.Peer_List.size() * input.Cfp_Slot_Per) +
                        input.cap_slot_num + 1) * (input.Slot_Lenght));

                int rety_count = 5;

                input.Peer_List[i].Supported_DataRate = supported_datarate;
                input.Peer_List[i].Desired_DataRate = estimated_datarate;
                input.Peer_List[i].Peer_Buffer = assumed_buffer;
                input.Peer_List[i].Rety_Count = rety_count;


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
    int initial_cfp_number = Input.Cfp_Slot_Per;

    Main_Window->clearSimulationList();

    for(int k=0; k<25; k++)
    {
        input.Cfp_Slot_Per = initial_cfp_number;

        for(int i=0; i<20; i++)
        {

            input.Simulation_Name = QString("Cfp:") + QString::number(input.Cfp_Slot_Per);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {
                double supported_datarate = (double)(PACKAGE_SIZE * 8) / input.Slot_Lenght;

                double bit_per_slot = (double)(input.Slot_Lenght * supported_datarate);

                double estimated_datarate = (double)(bit_per_slot * input.Cfp_Slot_Per) /
                        ((1 + input.cap_slot_num + (input.Peer_List.size() *input.Cfp_Slot_Per)) *
                         input.Slot_Lenght);

                int assumed_buffer = std::floor(
                        ((input.Peer_List.size() * input.Cfp_Slot_Per) +
                        input.cap_slot_num + 1) * (input.Slot_Lenght));

                int rety_count = 5;
                input.Peer_List[i].Supported_DataRate = supported_datarate;
                input.Peer_List[i].Desired_DataRate = estimated_datarate;
                input.Peer_List[i].Peer_Buffer = assumed_buffer;
                input.Peer_List[i].Rety_Count = rety_count;


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
    int initial_cap_number = Input.cap_slot_num;

    Main_Window->clearSimulationList();


    for(int k=0; k<14; k++)
    {

        input.cap_slot_num = initial_cap_number;

        for(int l=0; l<25; l++)
        {
            double supported_datarate = (double)(PACKAGE_SIZE * 8) / input.Slot_Lenght;

            double bit_per_slot = (double)(input.Slot_Lenght * supported_datarate);

            double estimated_datarate = (double)(bit_per_slot * input.Cfp_Slot_Per) /
                    ((1 + input.cap_slot_num + (input.Peer_List.size() *input.Cfp_Slot_Per)) *
                     input.Slot_Lenght);

            int assumed_buffer = std::floor(
                    ((input.Peer_List.size() * input.Cfp_Slot_Per) +
                    input.cap_slot_num + 1) * (input.Slot_Lenght));

            int rety_count = 5;

            input.Simulation_Name = QString("Cap:") + QString::number(input.cap_slot_num);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {

                input.Peer_List[i].Supported_DataRate = supported_datarate;
                input.Peer_List[i].Desired_DataRate = estimated_datarate;
                input.Peer_List[i].Peer_Buffer = assumed_buffer;
                input.Peer_List[i].Rety_Count = rety_count;

            }

            Main_Window->addSimulation(input);
            input.cap_slot_num++;

        }

        Main_Window->setSimulationArrayListName(QString("User:") + QString::number(input.Peer_List.size()));
        Main_Window->importListToArray();
        Main_Window->clearSimulationList();

        if(k < 13)
            input.Peer_List.push_back(PeerInfo());
    }


}

