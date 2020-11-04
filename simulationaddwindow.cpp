
#include "mainwindow.h"
#include "simulationaddwindow.h"
#include "ui_simulationaddwindow.h"


SimulationAddWindow::SimulationAddWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationAddWindow),
    User_Add_Window(this)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptedButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectedButtonClicked()));
    connect(ui->user_add_button, SIGNAL(clicked()), this, SLOT(userAddButtonClicked()));
    connect(ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearListClicked()));

    Edit_Enable = false;
    Main_Window = dynamic_cast<MainWindow *>(parent);


}



SimulationAddWindow::~SimulationAddWindow()
{

    delete ui;
}



void SimulationAddWindow::acceptedButtonClicked()
{

    Input_Info.cap_slot_num = ui->cap_slot_box->value();
    Input_Info.Cfp_Slot_Per = ui->cfp_lot_box->value();
    Input_Info.beacon_slot_num = ui->beacon_slot_box->value();

    Input_Info.Cap_Slot_Lenght = ui->cap_slot_lenght->value();
    Input_Info.Cfp_Slot_Lenght = ui->cfp_slot_lenght->value();
    Input_Info.Beacon_Slot_Lenght = ui->beacon_slot_lenght->value();
    Input_Info.Slot_Duration = ui->slot_duration->value();
    Input_Info.Simulation_Duration = ui->simulation_duration_box->value();
    Input_Info.Simulation_Name = ui->simulation_name_box->text();
    Input_Info.Enable_Buffer_Overflow = ui->enable_bufferoverflow_button->isChecked();

    this->hide();

    if(Edit_Enable == false)
        Main_Window->simulationAddCallBack(Input_Info);
    else
    {
        Main_Window->simulationEditCallBack(Edit_Index, Input_Info);
        Edit_Enable = false;
    }

}



void SimulationAddWindow::rejectedButtonClicked()
{
    Edit_Enable = false;
    this->hide();
}



void SimulationAddWindow::userAddButtonClicked()
{
    User_Add_Window.show();
}



void SimulationAddWindow::autoAddButtonClicked()
{



}



void SimulationAddWindow::clearListClicked()
{
    ui->user_list->clear();
    Input_Info.Peer_List.clear();
    Edit_Enable = false;

}



void SimulationAddWindow::userAddCallBack(PeerInfo Info)
{

    ui->user_list->addItem("Peer - " + QString::number(Input_Info.Peer_List.size()) +
                           " - Desired: " + QString::number(Info.Desired_DataRate) + " KBPS - Transmission Delay: " +
                           QString::number(Info.Transmission_Delay) +
                                                                                     " ms - Buffer: " +
                           QString::number(Info.Peer_Buffer) + " Packages");

    Input_Info.Peer_List.push_back(Info);

}



void SimulationAddWindow::editSimulationInputs(int Index, const InputInfo &Inputs)
{
    ui->cap_slot_box->setValue(Inputs.cap_slot_num);
    ui->cfp_lot_box->setValue(Inputs.Cfp_Slot_Per);
    ui->beacon_slot_box->setValue(Inputs.beacon_slot_num);
    ui->cap_slot_lenght->setValue(Inputs.Cap_Slot_Lenght);
    ui->cfp_slot_lenght->setValue(Inputs.Cfp_Slot_Lenght);
    ui->beacon_slot_lenght->setValue(Inputs.Beacon_Slot_Lenght);
    ui->slot_duration->setValue(Inputs.Slot_Duration);
    ui->simulation_duration_box->setValue(Inputs.Simulation_Duration);
    ui->simulation_name_box->setText(Inputs.Simulation_Name);
    ui->enable_bufferoverflow_button->setChecked(Inputs.Enable_Buffer_Overflow);

    ui->user_list->clear();

    for(size_t i= 0; i < Inputs.Peer_List.size(); i++)
    {
        ui->user_list->addItem("Peer - " + QString::number(i) +
                               " - DataRate: " + QString::number(Inputs.Peer_List[i].Desired_DataRate) + " KBPS - Buffer: " +
                               QString::number(Inputs.Peer_List[i].Peer_Buffer) + " Packages");
    }



    Edit_Enable = true;
    Edit_Index = Index;
}



void SimulationAddWindow::closeEvent(QCloseEvent *Event)
{
    (void)Event;
    Edit_Enable = false;
    this->hide();
}





