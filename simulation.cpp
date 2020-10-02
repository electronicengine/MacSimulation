#include "simulation.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QDir>
#include "QTimer"


Simulation::Simulation(const InputInfo &Info) :
    Overall_Simulation_Output{0,0,0,0,0,0,0}
{

    Ping_Counter = 0;

    Input_Info = Info;

}



Simulation::~Simulation()
{
}





void Simulation::ping()
{
    OutputInfo *output;

    Ping_Counter++;

    if(Ping_Counter > Input_Info.Slot_Lenght)
    {

//        std::cout << "ping - " << Input_Info.Simulation_Name.toStdString() << std::endl;

        Ping_Counter = 0;
        output = Coordinator_.ping();

        if(output != NULL)
        {
            for(size_t i=0; i<Coordinator_.Peer_List.size(); i++)
            {
                Peer_Simulation_Result[i].refreshValues(output->Peer_Output[i], output);
            }
        }
    }
}



void Simulation::resetSimulation()
{
    Ping_Counter = 0;

    Overall_Simulation_Output.reset();

    Peer_Simulation_Result.clear();

    Coordinator_.reset();

    for(int i =0 ; i < (int)Input_Info.Peer_List.size(); i++)
        Peer_Simulation_Result.push_back(PeerSimulation(i, Input_Info));



    for(int i =0 ; i < (int)Input_Info.Peer_List.size(); i++)
    {
        Peer_Simulation_Result[i].setTitle(Input_Info.Simulation_Name);
        Peer_Simulation_Result[i].setInputInfo(i, Input_Info);
        Peer_Simulation_Result[i].setFormTitle(Input_Info.Simulation_Name + QString(" - Result For Peer - ") + QString::number(i));
    }
}



void Simulation::saveSimulation(const QString &UpperDir, const QString &MainDir)
{
    QString dir ;
    std::cout << "saveSimulation - " << Input_Info.Simulation_Name.toStdString() << std::endl;


    if(!QDir("graphs").exists())
        QDir().mkdir("graphs");

    dir = "graphs/" + UpperDir;

    if(!QDir(dir).exists())
        QDir().mkdir(dir);

    dir += "/" + MainDir;

    if(!QDir(dir).exists())
        QDir().mkdir(dir);

    dir += "/" + Input_Info.Simulation_Name;


    if(!QDir(dir).exists())
        QDir().mkdir(dir);


    for(size_t i = 0; i < Peer_Simulation_Result.size(); i++)
    {
        Peer_Simulation_Result[i].setFormTitle(Input_Info.Simulation_Name + QString(" - Result For Peer - ") + QString::number(i));
        Peer_Simulation_Result[i].saveGraphInfo(dir);
    }
}



void Simulation::setInputs(const InputInfo &Info)
{

    Peer_Simulation_Result.clear();

//    Result_Windows.clear();

    Input_Info = Info;

    Coordinator_.setInputInformation(Info);

    for(int i =0 ; i < (int)Input_Info.Peer_List.size(); i++)
        Peer_Simulation_Result.push_back(PeerSimulation(i, Input_Info));



    for(int i =0 ; i < (int)Input_Info.Peer_List.size(); i++)
    {
        Peer_Simulation_Result[i].setTitle(Info.Simulation_Name);
        Peer_Simulation_Result[i].setInputInfo(i, Info);
        Peer_Simulation_Result[i].setFormTitle(Info.Simulation_Name + QString(" - Result For Peer - ") + QString::number(i));
    }
}



const PeerSimulationOutput &Simulation::getSimulationAvarageOutput()
{

    std::cout << "getSimulationAvarageOutput - " << Input_Info.Simulation_Name.toStdString() << std::endl;

    if(Peer_Simulation_Result.size() > 0)
    {
        for(size_t i = 0; i < Peer_Simulation_Result.size(); i++)
        {
            const PeerSimulationOutput &peer_output = Peer_Simulation_Result[i].getPeerSimulationOutput();

            Overall_Simulation_Output.Avarage_Delay_Value += peer_output.Avarage_Delay_Value;
            Overall_Simulation_Output.Max_DataRate_Value += peer_output.Max_DataRate_Value;

            Overall_Simulation_Output.Max_Dropped_Package_Value += peer_output.Max_Dropped_Package_Value;
            Overall_Simulation_Output.Max_Unsuccesfull_Reservation += peer_output.Max_Unsuccesfull_Reservation;

            if(Overall_Simulation_Output.Max_Delay < peer_output.Max_Delay)
                Overall_Simulation_Output.Max_Delay = peer_output.Max_Delay;

            if(Overall_Simulation_Output.Max_Total_Collusion_Value < peer_output.Max_Total_Collusion_Value)
                Overall_Simulation_Output.Max_Total_Collusion_Value = peer_output.Max_Total_Collusion_Value;

            if(Overall_Simulation_Output.Max_Buffer_Value < peer_output.Max_Buffer_Value)
                Overall_Simulation_Output.Max_Buffer_Value = peer_output.Max_Buffer_Value;

        }

        Overall_Simulation_Output.Avarage_Delay_Value /= Peer_Simulation_Result.size();
        Overall_Simulation_Output.Max_DataRate_Value /= Peer_Simulation_Result.size();
    }

    return Overall_Simulation_Output;
}




