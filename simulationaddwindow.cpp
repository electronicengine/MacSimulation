
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
    connect(ui->auto_add_button, SIGNAL(clicked()), this, SLOT(autoAddButtonClicked()));
    connect(ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearListClicked()));

    Edit_Enable = false;
    Main_Window = dynamic_cast<MainWindow *>(parent);

    //std::cout << "SimulationAddWindow::"<<  std::endl;

}



SimulationAddWindow::~SimulationAddWindow()
{
    //std::cout << "SimulationAddWindow::~"<<  std::endl;

    delete ui;
}



void SimulationAddWindow::acceptedButtonClicked()
{

    Input_Info.cap_slot_num = ui->cap_slot_box->value();
    Input_Info.Cfp_Slot_Per = ui->cfp_lot_box->value();
    Input_Info.Slot_Lenght = ui->slot_lenght_box->value();
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
    double estimated_datarate = (double)((PACKAGE_SIZE * 8) * ui->cfp_lot_box->value()) /
            ((1 + ui->cap_slot_box->value() + (ui->user_number_box->value() * ui->cfp_lot_box->value())) * ui->slot_lenght_box->value());

    std::cout << "estimated_datarate: " << std::to_string(estimated_datarate) << std::endl;

    ui->estimated_datarate->setText(QString::number(estimated_datarate));
    User_Add_Window.show();
}



void SimulationAddWindow::autoAddButtonClicked()
{
    double estimated_datarate = (double)((PACKAGE_SIZE * 8) * ui->cfp_lot_box->value()) /
            ((1 + ui->cap_slot_box->value() + (ui->user_number_box->value() * ui->cfp_lot_box->value())) * ui->slot_lenght_box->value());

    int assumed_buffer = 30;
//            (ui->user_number_box->value() * ui->cfp_lot_box->value()) +
//            ui->cap_slot_box->value();
    int rety_count = 5;

    ui->estimated_datarate->setText(QString::number(estimated_datarate));

    std::cout << "estimated_datarate: " << std::to_string(estimated_datarate) << std::endl;

    for(int i=0; i<ui->user_number_box->value(); i++)
    {
        ui->user_list->addItem("Peer - " + QString::number(Input_Info.Peer_List.size()) +
                               " - DataRate: " + QString::number(estimated_datarate) + " KBPS - Buffer: " +
                               QString::number(assumed_buffer) + " Packages");

        Input_Info.Peer_List.push_back(PeerInfo{estimated_datarate, assumed_buffer, rety_count});
    }

}



void SimulationAddWindow::clearListClicked()
{
    ui->user_list->clear();
    Input_Info.Peer_List.clear();
    Edit_Enable = false;

}



void SimulationAddWindow::userAddCallBack(double DataRate, int Buffer, int Rety_Count)
{

    ui->user_list->addItem("Peer - " + QString::number(Input_Info.Peer_List.size()) +
                           " - DataRate: " + QString::number(DataRate) + " KBPS - Buffer: " +
                           QString::number(Buffer) + " Packages");

    Input_Info.Peer_List.push_back(PeerInfo{DataRate, Buffer, Rety_Count});

}



void SimulationAddWindow::editSimulationInputs(int Index, const InputInfo &Inputs)
{
    ui->cap_slot_box->setValue(Inputs.cap_slot_num);
    ui->cfp_lot_box->setValue(Inputs.Cfp_Slot_Per);
    ui->slot_lenght_box->setValue(Inputs.Slot_Lenght);
    ui->simulation_duration_box->setValue(Inputs.Simulation_Duration);
    ui->simulation_name_box->setText(Inputs.Simulation_Name);
    ui->enable_bufferoverflow_button->setChecked(Inputs.Enable_Buffer_Overflow);

    ui->user_list->clear();

    for(size_t i= 0; i < Inputs.Peer_List.size(); i++)
    {
        ui->user_list->addItem("Peer - " + QString::number(i) +
                               " - DataRate: " + QString::number(Inputs.Peer_List[i].Data_Rate) + " KBPS - Buffer: " +
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





