#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>
#include <QPointer>
#include "coordinator.h"
#include "peer.h"

#include "simulationresultwindow.h"
#include "peersimulation.h"


class Simulation
{

public:
    Simulation(const InputInfo &Info);
    ~Simulation();    
    void ping();
    void resetSimulation();
    void saveSimulation(const QString &UpperDir, const QString &MainDir);
    void setInputs(const InputInfo &Info);
    const PeerSimulationOutput &getSimulationAvarageOutput();
    InputInfo Input_Info;
    int Ticket_Number;
    int Operator_Id;

private:
    Coordinator Coordinator_;
    int Ping_Counter;


    std::vector<PeerSimulation> Peer_Simulation_Result;
    PeerSimulationOutput Overall_Simulation_Output;

};

#endif // SIMULATION_H
