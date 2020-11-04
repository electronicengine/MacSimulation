#include "simulationoperator.h"
#include "mainwindow.h"
#include "logging.h"

SimulationOperator::SimulationOperator(int Id, MainWindow *Window) : QObject(Window)
{
    Operator_Id = Id;
    Main_Window = Window;
    Terminate_ = false;
    Ping_Counter = 0;
    Simulation_Duration = 0;

    Timer_ = new QTimer(this);

    connect(Timer_, SIGNAL(timeout()), this, SLOT(ping()));
}



void SimulationOperator::start(Simulation *Sim)
{
    if(Sim != nullptr)
    {
        Current_Simulation_Pointer = Sim;
        Simulation_Duration = Sim->Input_Info.Simulation_Duration;

        Terminate_ = false;
        Timer_->start(1);
    }
    else
    {
        Logging::printAll(Logging::white, "Operator: ", Operator_Id, " - Simulations are done");

        Timer_->stop();
        Terminate_ = true;
        Ping_Counter = 0;
    }

}



void SimulationOperator::ping()
{

    if(Terminate_ == true)
    {
        Timer_->stop();
        Ping_Counter = 0;
        Simulation_Duration = 0;
        Current_Simulation_Pointer = nullptr;

        Logging::printAll(Logging::white, "Operator: ", Operator_Id, " - Terminated");

        return;
    }

    Current_Simulation_Pointer->ping();

    if(Ping_Counter >= Simulation_Duration)
    {
        Timer_->stop();
        Main_Window->sortSimulations(Current_Simulation_Pointer);
        Ping_Counter = 0;
    }
    else
    {
        Ping_Counter++;
    }

}


