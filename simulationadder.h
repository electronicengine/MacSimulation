#ifndef SIMULATIONADDER_H
#define SIMULATIONADDER_H

#include <vector>
#include <memory>

class MainWindow;
struct InputInfo;
class Simulation;

class SimulationAdder
{
public:
    SimulationAdder(MainWindow *Window);

    void autoAddSimulationIncreasingCap(const InputInfo &Input);
    void autoAddSimulationIncreasingCfp(const InputInfo &Input);
    void autoAddSimulationIncreasingUser(const InputInfo &Input);
private:
    MainWindow *Main_Window;



};

#endif // SIMULATIONADDER_H
