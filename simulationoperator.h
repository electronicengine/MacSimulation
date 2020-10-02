#ifndef SIMULATIONOPERATOR_H
#define SIMULATIONOPERATOR_H

#include <QThreadPool>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <memory>
#include "simulation.h"

class MainWindow;



class SimulationOperator : public QObject
{

    Q_OBJECT

public:
    volatile bool Terminate_;

    SimulationOperator(int Id, MainWindow *Window);

    void start(Simulation *Sim);

private slots:
    void ping();


private:
    QTimer *Timer_;
    int Operator_Id;
    MainWindow *Main_Window;

    int Ping_Counter;
    int Simulation_Duration;
    Simulation *Current_Simulation_Pointer;
};

#endif // SIMULATIONOPERATOR_H
