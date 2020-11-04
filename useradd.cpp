
#include <iostream>
#include "useradd.h"
#include "ui_simulationaddwindow.h"
#include "ui_useradd.h"
#include "simulationaddwindow.h"
#include "logging.h"

UserAdd::UserAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdd)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptedButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectedButtonClicked()));
    connect(ui->transmission_delay, SIGNAL(valueChanged(double)), this, SLOT(transmissionDelayChanged(double)));

    Simulation_Add_Window = dynamic_cast<SimulationAddWindow *>(parent);

}



UserAdd::~UserAdd()
{

    delete ui;
}



void UserAdd::acceptedButtonClicked()
{
    PeerInfo info;

    info.Desired_DataRate = ui->desired_datarate->value();
    info.Transmission_Delay = ui->transmission_delay->value();
    info.Rety_Count = ui->rety_count->value();
    info.Peer_Buffer = ui->buffer_box->value();

    Simulation_Add_Window->userAddCallBack(info);

}



void UserAdd::rejectedButtonClicked()
{

}

void UserAdd::transmissionDelayChanged(double Delay)
{
    double beacon_period_time = Simulation_Add_Window->ui->beacon_slot_box->value() *
            Simulation_Add_Window->ui->beacon_slot_lenght->value();

    double cap_period_time = Simulation_Add_Window->ui->cap_slot_box->value() *
            Simulation_Add_Window->ui->cap_slot_lenght->value();

    double cfp_period_time = Simulation_Add_Window->ui->cfp_lot_box->value() *
            Simulation_Add_Window->ui->cfp_slot_lenght->value() *
            Simulation_Add_Window->ui->user_number_box->value();

    Logging::printAll(Logging::white, "beacon period: ", beacon_period_time);
    Logging::printAll(Logging::white, "cap period: ", cap_period_time);
    Logging::printAll(Logging::white, "cfp period: ", cfp_period_time);

    double total_package_per_cfp_slot = (double) Simulation_Add_Window->ui->cfp_slot_lenght->value() / Delay;

    Logging::printAll(Logging::white, "total_package_per_cfp_slot: ", total_package_per_cfp_slot);

    double estimated_data_rate = (std::floor(total_package_per_cfp_slot * Simulation_Add_Window->ui->cfp_lot_box->value()) *
            (PACKAGE_SIZE * 8))/(beacon_period_time + cap_period_time + cfp_period_time);

    int assumed_buffer = (beacon_period_time + cap_period_time + cfp_period_time) * total_package_per_cfp_slot;

    ui->desired_datarate->setValue(estimated_data_rate);
    ui->buffer_box->setValue(assumed_buffer);
}
