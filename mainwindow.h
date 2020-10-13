#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QThreadPool>
#include <iostream>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <memory>
#include <QListWidgetItem>
#include <queue>
#include <QPointer>
#include "simulation.h"
#include "simulationaddwindow.h"
#include "simulationadder.h"
#include "simulationoperator.h"


#define MAX_WORKER_THREAD  10

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    Simulation *getCurrentSimulation();
    void processEndOf();
    void processCurrentSimulationListOutput();
    void processCurrentSimulationOutput(Simulation *Sim);
    void sortSimulations(Simulation *Sim);
    void showMessageBox(const QString &Tittle, const QString &Content);
    void clearSimulationList();
    void setSimulationArrayListName(const QString &Name);
    void simulationEditCallBack(int Index, InputInfo &Input);
    void importListToArray();
    void addSimulation(InputInfo &Input);
    void simulationAddCallBack(InputInfo &Input);
    void contextMenuEvent(QContextMenuEvent *Event);

private slots:
    void autoAddIncreasingUserTriggered(bool);
    void autoAddIncreasingCapTriggered(bool);
    void autoAddIncreasingCfpTriggered(bool);
    void editActionTriggered(bool);
    void importButtonClicked();
    void exportButtonClicked();
    void startButtonToggled(bool);
    void simulationAddButtonClicked();
    void clearListButtonClicked();
    void clearArrayButtonClicked();
    void progressBarUpdate();

    void simulationArrayListDoubleClicked(QListWidgetItem *item);
signals:

private:

    Ui::MainWindow *MainWindow_Ui;

    SimulationAddWindow Simulation_Add_Window;
    SimulationResultWindow Total_Result_Window;
    SimulationAdder Simulation_Adder;

    QMenu Menu_;

    QAction *Auto_Add_Cap;
    QAction *Auto_Add_Cfp;
    QAction *Edit_Action;
    QAction *Auto_Add_User;

    QTimer *Progress_Timer;
    std::mutex Operator_Mutex;
    std::queue<std::shared_ptr<Simulation>> Simulation_Queue;
    std::vector<std::shared_ptr<Simulation>> Simulation_List;
    std::vector<std::vector<std::shared_ptr<Simulation>>> Simulation_List_Array;
    std::vector<QString> Simulation_List_Array_Name;

    std::vector<QPointer<SimulationResultWindow>> Simulation_Result_Windows;
    std::vector<std::shared_ptr<SimulationOperator>> Simulation_Operators;
    std::vector<Simulation *> Sorted_Simulations;
    bool Simulation_Running;
    int Current_Simulation;
    int Current_Simulation_Array;
    int Next_Ticket_Number;
    int Thread_Size;
    int Current_Simulation_Progress;
    int Progress_Duration;
    void loadCurrentSimulationList(int Index);
    void lockButtons();
    void unlockButtons();
    void createOperators();
    void terminateOperators();


};
#endif // MAINWINDOW_H
