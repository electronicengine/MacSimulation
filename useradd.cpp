
#include <iostream>
#include "useradd.h"
#include "ui_useradd.h"
#include "simulationaddwindow.h"

UserAdd::UserAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdd)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptedButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectedButtonClicked()));

    Simulation_Add_Window = dynamic_cast<SimulationAddWindow *>(parent);
    //std::cout << "UserAdd::"<<  std::endl;

}



UserAdd::~UserAdd()
{
    //std::cout << "UserAdd::~"<<  std::endl;

    delete ui;
}



void UserAdd::acceptedButtonClicked()
{
    PeerInfo info;

    info.Desired_DataRate = ui->desired_datarate->value();
    info.Supported_DataRate = ui->supported_data_rate->value();
    info.Rety_Count = ui->rety_count->value();
    info.Peer_Buffer = ui->buffer_box->value();

    Simulation_Add_Window->userAddCallBack(info);

}



void UserAdd::rejectedButtonClicked()
{

}
