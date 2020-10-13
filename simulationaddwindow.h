#ifndef SIMULATIONADDWINDOW_H
#define SIMULATIONADDWINDOW_H
#include <memory>
#include <QMainWindow>
#include "useradd.h"
#include "coordinator.h"



struct MainWindow;

namespace Ui {
class SimulationAddWindow;
}

class SimulationAddWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationAddWindow(QWidget *parent = nullptr);
    virtual ~SimulationAddWindow();

    void userAddCallBack(PeerInfo Info);
    void editSimulationInputs(int Index, const InputInfo &Inputs);
    void closeEvent(QCloseEvent *Event);

private slots:
    void acceptedButtonClicked();
    void rejectedButtonClicked();
    void userAddButtonClicked();
    void autoAddButtonClicked();
    void clearListClicked();

private:
    Ui::SimulationAddWindow *ui;
    MainWindow *Main_Window;
    UserAdd User_Add_Window;
    InputInfo Input_Info;

    bool Edit_Enable;
    int Edit_Index;


};

#endif // SIMULATIONADDWINDOW_H
