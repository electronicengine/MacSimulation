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

                double beacon_period_time = input.beacon_slot_num * input.Beacon_Slot_Lenght;

                double cap_period_time = input.cap_slot_num * input.Cap_Slot_Lenght;

                double cfp_period_time = input.Cfp_Slot_Lenght * input.Cfp_Slot_Lenght * input.Peer_List.size();

                double total_package_per_cfp_slot = (double) input.Cfp_Slot_Lenght / input.Peer_List[i].Transmission_Delay;

                double estimated_data_rate = (std::floor(total_package_per_cfp_slot * input.Cfp_Slot_Lenght) *
                                              (PACKAGE_SIZE * 8))/(beacon_period_time + cap_period_time + cfp_period_time);

                double assumed_buffer = (beacon_period_time + cap_period_time + cfp_period_time) /
                        total_package_per_cfp_slot;


                input.Peer_List[i].Transmission_Delay = input.Peer_List[i].Transmission_Delay;
                input.Peer_List[i].Desired_DataRate = estimated_data_rate;
                input.Peer_List[i].Peer_Buffer = assumed_buffer;
                input.Peer_List[i].Rety_Count = input.Peer_List[i].Rety_Count;


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

                double beacon_period_time = input.beacon_slot_num * input.Beacon_Slot_Lenght;

                double cap_period_time = input.cap_slot_num * input.Cap_Slot_Lenght;

                double cfp_period_time = input.Cfp_Slot_Lenght * input.Cfp_Slot_Lenght * input.Peer_List.size();

                double total_package_per_cfp_slot = (double) input.Cfp_Slot_Lenght / input.Peer_List[i].Transmission_Delay;

                double estimated_data_rate = (std::floor(total_package_per_cfp_slot * input.Cfp_Slot_Lenght) *
                                              (PACKAGE_SIZE * 8))/(beacon_period_time + cap_period_time + cfp_period_time);

                double assumed_buffer = (beacon_period_time + cap_period_time + cfp_period_time) /
                        total_package_per_cfp_slot;


                input.Peer_List[i].Transmission_Delay = input.Peer_List[i].Transmission_Delay;
                input.Peer_List[i].Desired_DataRate = estimated_data_rate;
                input.Peer_List[i].Peer_Buffer = assumed_buffer;
                input.Peer_List[i].Rety_Count = input.Peer_List[i].Rety_Count;


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

            double beacon_period_time = input.beacon_slot_num * input.Beacon_Slot_Lenght;

            double cap_period_time = input.cap_slot_num * input.Cap_Slot_Lenght;

            double cfp_period_time = input.Cfp_Slot_Lenght * input.Cfp_Slot_Lenght * input.Peer_List.size();

            int transmission_delay = (double)(rand() % 300) / 100;

            double total_package_per_cfp_slot = (double) input.Cfp_Slot_Lenght / transmission_delay;

            double estimated_data_rate = (std::floor(total_package_per_cfp_slot * input.Cfp_Slot_Lenght) *
                                          (PACKAGE_SIZE * 8))/(beacon_period_time + cap_period_time + cfp_period_time);

            double assumed_buffer = (beacon_period_time + cap_period_time + cfp_period_time) /
                    total_package_per_cfp_slot;


            int rety_count = 5;

            input.Simulation_Name = QString("Cap:") + QString::number(input.cap_slot_num);

            for(int i = 0; i<(int)input.Peer_List.size(); i++)
            {

                input.Peer_List[i].Transmission_Delay = transmission_delay;
                input.Peer_List[i].Desired_DataRate = estimated_data_rate;
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

