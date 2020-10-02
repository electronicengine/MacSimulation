
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

    Simulation_Add_Window->userAddCallBack(ui->datarate_box->value(), ui->buffer_box->value(),
                            ui->rety_count->value());

}



void UserAdd::rejectedButtonClicked()
{

}
