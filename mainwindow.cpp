#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , MainWindow_Ui(new Ui::MainWindow),
      Simulation_Add_Window(this),
      Total_Result_Window("Total Results", this),
      Simulation_Adder(this)
{
    MainWindow_Ui->setupUi(this);

    Progress_Timer = new QTimer(this);

    Edit_Action = new QAction("Edit Simulation Inputs", this);
    Auto_Add_Cap = new QAction("AutoAdd Increasing Cap", this);
    Auto_Add_Cfp = new QAction("AutoAdd Increasing Cfp", this);
    Auto_Add_User = new QAction("AutoAdd Increasing User", this);

    Menu_.addAction(Edit_Action);
    Menu_.addAction(Auto_Add_Cap);
    Menu_.addAction(Auto_Add_Cfp);
    Menu_.addAction(Auto_Add_User);


    Menu_.setStyleSheet("background-color: rgb(46, 52, 54); \
                        color: rgb(114, 159, 207);");

    connect(Progress_Timer, SIGNAL(timeout()), this, SLOT(progressBarUpdate()));
    connect(Edit_Action, SIGNAL(triggered(bool)), this, SLOT(editActionTriggered(bool)));
    connect(Auto_Add_Cap, SIGNAL(triggered(bool)), this, SLOT(autoAddIncreasingCapTriggered(bool)));
    connect(Auto_Add_Cfp, SIGNAL(triggered(bool)), this, SLOT(autoAddIncreasingCfpTriggered(bool)));
    connect(Auto_Add_User, SIGNAL(triggered(bool)), this, SLOT(autoAddIncreasingUserTriggered(bool)));

    connect(MainWindow_Ui->import_button, SIGNAL(clicked()), this, SLOT(importButtonClicked()));
    connect(MainWindow_Ui->export_button, SIGNAL(clicked()), this, SLOT(exportButtonClicked()));
    connect(MainWindow_Ui->start_button, SIGNAL(toggled(bool)), this, SLOT(startButtonToggled(bool)));
    connect(MainWindow_Ui->simulation_add_button, SIGNAL(clicked()), this, SLOT(simulationAddButtonClicked()));
    connect(MainWindow_Ui->clear_list_button, SIGNAL(clicked()), this, SLOT(clearListButtonClicked()));
    connect(MainWindow_Ui->clear_array_button, SIGNAL(clicked()), this, SLOT(clearArrayButtonClicked()));

    connect(MainWindow_Ui->simulation_array_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(simulationArrayListDoubleClicked(QListWidgetItem*)));

    Simulation_Running = false;
    Current_Simulation = 0;
    Current_Simulation_Array = 0;
    Next_Ticket_Number = 0;
    Thread_Size = 0;
    Current_Simulation_Progress = 0;
    Progress_Duration = 0;

    //std::cout << "MainWindow::"<<  std::endl;
    MainWindow_Ui->simulation_progress->setValue(0);


}



MainWindow::~MainWindow()
{
    delete MainWindow_Ui;
}




void MainWindow::showMessageBox(const QString &Tittle, const QString &Content)
{

//    QMessageBox::setStyleSheet("background-color: rgb(46, 52, 54);color: rgb(114, 159, 207);");
    QMessageBox::warning(this, Tittle, Content);

}



void MainWindow::clearSimulationList()
{
    Simulation_List.clear();
    MainWindow_Ui->simulation_list->clear();
}




void MainWindow::setSimulationArrayListName(const QString &Name)
{
    MainWindow_Ui->simulation_array_list_name->setText(Name);
}



void MainWindow::simulationEditCallBack(int Index, InputInfo &Input)
{
    MainWindow_Ui->simulation_list->currentItem()->setText(Input.Simulation_Name +
                                                QString(" - Duration: ") + QString::number(Input.Simulation_Duration));

    Input.Enable_Simulation_Graph = MainWindow_Ui->enable_simulation_log_button->isChecked();

    Simulation_List[Index]->setInputs(Input);
}




void MainWindow::importListToArray()
{
    Simulation_Result_Windows.push_back(new SimulationResultWindow(
                                            MainWindow_Ui->simulation_array_list_name->text()));

    Simulation_List_Array.push_back(Simulation_List);

    std::vector<std::shared_ptr<Simulation>> temp_list;

    for(size_t i=0; i<Simulation_List.size(); i++)
    {
        temp_list.push_back(std::make_shared<Simulation>(Simulation_List[i]->Input_Info));
        temp_list[temp_list.size() - 1]->setInputs(Simulation_List[i]->Input_Info);
    }

    Simulation_List.clear();

    Simulation_List = temp_list;

    MainWindow_Ui->simulation_array_list->addItem(MainWindow_Ui->simulation_array_list_name->text());
    Simulation_List_Array_Name.push_back(MainWindow_Ui->simulation_array_list_name->text());

}



void MainWindow::addSimulation(InputInfo &Input)
{

    MainWindow_Ui->simulation_list->addItem(Input.Simulation_Name +
                                 QString(" - Duration: ") + QString::number(Input.Simulation_Duration));


    Input.Enable_Simulation_Graph = MainWindow_Ui->enable_simulation_log_button->isChecked();

    Simulation_List.push_back(std::make_shared<Simulation>(Input));
    Simulation_List[Simulation_List.size() - 1]->setInputs(Input);


}



void MainWindow::simulationAddCallBack(InputInfo &Input)
{

    MainWindow_Ui->simulation_list->addItem(Input.Simulation_Name +
                                 QString(" - Duration: ") + QString::number(Input.Simulation_Duration));

    Input.Enable_Simulation_Graph = MainWindow_Ui->enable_simulation_log_button->isChecked();

    Simulation_List.push_back(std::make_shared<Simulation>(Input));
    Simulation_List[Simulation_List.size() - 1]->setInputs(Input);

}



void MainWindow::contextMenuEvent(QContextMenuEvent *Event)
{

    (void)Event;


    Menu_.exec(QCursor::pos());

}



void MainWindow::autoAddIncreasingUserTriggered(bool)
{
    if(Simulation_List.size() <= 0)
    {
        showMessageBox("Warning!", "You should add at least one simulation");
        return;

    }

    InputInfo input = Simulation_List[Simulation_List.size() - 1]->Input_Info;

    Simulation_List.clear();
    Simulation_List_Array.clear();
    MainWindow_Ui->simulation_list->clear();
    MainWindow_Ui->simulation_array_list->clear();


    Simulation_Adder.autoAddSimulationIncreasingUser(input);
}



void MainWindow::autoAddIncreasingCapTriggered(bool)
{
    if(Simulation_List.size() <= 0)
    {
        showMessageBox("Warning!", "You should add at least one simulation");
        return;

    }

    InputInfo input = Simulation_List[Simulation_List.size() - 1]->Input_Info;

    Simulation_List.clear();
    Simulation_List_Array.clear();
    MainWindow_Ui->simulation_list->clear();
    MainWindow_Ui->simulation_array_list->clear();


    Simulation_Adder.autoAddSimulationIncreasingCap(input);
}



void MainWindow::autoAddIncreasingCfpTriggered(bool)
{


    if(Simulation_List.size() <= 0)
    {
        showMessageBox("Warning!", "You should add at least one simulation");
        return;

    }

    InputInfo input = Simulation_List[Simulation_List.size() - 1]->Input_Info;

    Simulation_List.clear();
    Simulation_List_Array.clear();
    MainWindow_Ui->simulation_list->clear();
    MainWindow_Ui->simulation_array_list->clear();


    Simulation_Adder.autoAddSimulationIncreasingCfp(input);

}



void MainWindow::editActionTriggered(bool)
{

    int simulation_index =
            MainWindow_Ui->simulation_list->selectionModel()->currentIndex().row();

    if(simulation_index < 0)
    {
        showMessageBox("Warning!", "You should add and select at least one simulation");
        return;
    }

    Simulation_Add_Window.editSimulationInputs(simulation_index, Simulation_List[simulation_index]->Input_Info);
    Simulation_Add_Window.show();

}



void MainWindow::importButtonClicked()
{
    importListToArray();
}



void MainWindow::exportButtonClicked()
{
    int index = MainWindow_Ui->simulation_array_list->selectionModel()->currentIndex().row();

    if(index < 0)
        return;

    loadCurrentSimulationList(index);

}



void MainWindow::clearArrayButtonClicked()
{

    MainWindow_Ui->simulation_array_list->clear();
    Simulation_List_Array.clear();
    Simulation_List_Array_Name.clear();
    Simulation_Result_Windows.clear();

}



void MainWindow::progressBarUpdate()
{

    double progress = ((double)(Current_Simulation_Progress) / ((double)Progress_Duration / 1000)) * 100;

    MainWindow_Ui->simulation_progress->setValue(progress);
    Current_Simulation_Progress++;

}


void MainWindow::simulationAddButtonClicked()
{

    Simulation_Add_Window.show();

}



void MainWindow::clearListButtonClicked()
{
    Simulation_List.clear();
    MainWindow_Ui->simulation_list->clear();
}



void MainWindow::processEndOf()
{
    std::cout <<" All Simulations are done" << std::endl;
    Total_Result_Window.saveGraphtoFile("graphs", MainWindow_Ui->simulation_name->text());
    Total_Result_Window.show();

    MainWindow_Ui->start_button->setChecked(false);
    MainWindow_Ui->start_label->setText("done!");

    Simulation_Running = false;

    Current_Simulation = 0;
    Current_Simulation_Array = 0;

}



void MainWindow::processCurrentSimulationListOutput()
{
    std::cout <<" Current Simulation List Array is done" << std::endl;

    PeerSimulationOutput output =  Simulation_Result_Windows[Current_Simulation_Array]->
            getOutput();

    Total_Result_Window.refreshValues(output,
                                       Simulation_List_Array_Name[Current_Simulation_Array]);


    Simulation_Result_Windows[Current_Simulation_Array]->
            saveGraphtoFile(MainWindow_Ui->simulation_name->text(),
                            Simulation_List_Array_Name[Current_Simulation_Array]);

    Current_Simulation = 0;

    MainWindow_Ui->simulation_array_list->item(Current_Simulation_Array)->setBackground(QColor(Qt::GlobalColor::blue));
    Current_Simulation_Array++;

    if(Current_Simulation_Array >= (int)Simulation_List_Array.size())
    {

        processEndOf();

    }
    else
    {
        loadCurrentSimulationList(Current_Simulation_Array);

    }

}



void MainWindow::processCurrentSimulationOutput(Simulation *Sim)
{

    int operator_id = Sim->Operator_Id;

    std::cout <<" Current Simulation is finished" << std::endl;

    const PeerSimulationOutput &output = Sim->getSimulationAvarageOutput();

    Simulation_Result_Windows[Current_Simulation_Array]->refreshValues(output,
            Sim->Input_Info.Simulation_Name);

    Sim->saveSimulation(MainWindow_Ui->simulation_name->text(),
                           Simulation_List_Array_Name[Current_Simulation_Array]);


    MainWindow_Ui->simulation_list->item(Current_Simulation)->setBackground(QColor(Qt::GlobalColor::blue));
    Current_Simulation++;

    if(Current_Simulation >= (int)Simulation_List_Array[Current_Simulation_Array].size())
    {
        processCurrentSimulationListOutput();
    }

    if(Simulation_Running == true)
    {
        Simulation *ptr = getCurrentSimulation();
        if(ptr != nullptr)
            ptr->Operator_Id = operator_id;

        Simulation_Operators[operator_id]->start(ptr);
    }

}



void MainWindow::sortSimulations(Simulation *Sim)
{
    std::unique_lock<std::mutex> lock(Operator_Mutex);

    Sorted_Simulations[(Sim->Ticket_Number) % Thread_Size] = Sim;
    Next_Ticket_Number++;

    if(Next_Ticket_Number >= Thread_Size)
    {
        Next_Ticket_Number = 0;

        MainWindow_Ui->simulation_progress->setValue(0);
        Current_Simulation_Progress = 0;

        for(int i=0; i < Thread_Size; i++)
        {
            processCurrentSimulationOutput(Sorted_Simulations[i]);
        }
    }
}



Simulation *MainWindow::getCurrentSimulation()
{
    Simulation *simulation;

    if(!Simulation_Queue.empty())
    {
        simulation = Simulation_Queue.front().get();
        Simulation_Queue.pop();

        return simulation;
    }
    else
    {
        return nullptr;
    }

}




void MainWindow::simulationArrayListDoubleClicked(QListWidgetItem *item)
{
    int index = MainWindow_Ui->simulation_array_list->row(item);

    Simulation_Result_Windows[index]->show();
}



void MainWindow::loadCurrentSimulationList(int Index)
{

    Simulation_List.clear();
    MainWindow_Ui->simulation_list->clear();

    for(size_t i = 0; i<Simulation_List_Array[Index].size(); i++)
        Simulation_List.push_back(Simulation_List_Array[Index][i]);

    for(size_t i = 0; i < Simulation_List.size(); i++)
        MainWindow_Ui->simulation_list->addItem(Simulation_List[i]->Input_Info.Simulation_Name +
                                     " - Duration: " + QString::number(Simulation_List[i]->Input_Info.Simulation_Duration));


}



void MainWindow::lockButtons()
{
    MainWindow_Ui->clear_array_button->setEnabled(false);
    MainWindow_Ui->clear_list_button->setEnabled(false);
    MainWindow_Ui->export_button->setEnabled(false);
    MainWindow_Ui->import_button->setEnabled(false);
    MainWindow_Ui->simulation_add_button->setEnabled(false);

    Edit_Action->setEnabled(false);
    Auto_Add_Cfp->setEnabled(false);
}



void MainWindow::unlockButtons()
{
    MainWindow_Ui->clear_array_button->setEnabled(true);
    MainWindow_Ui->clear_list_button->setEnabled(true);
    MainWindow_Ui->export_button->setEnabled(true);
    MainWindow_Ui->import_button->setEnabled(true);
    MainWindow_Ui->simulation_add_button->setEnabled(true);

    Edit_Action->setEnabled(true);
    Auto_Add_Cfp->setEnabled(true);

    Progress_Timer->stop();
    MainWindow_Ui->simulation_progress->setValue(0);
    Current_Simulation_Progress = 0;
    Progress_Duration = 0;
}

void MainWindow::createOperators()
{

    int ticket_counter = 0;

    for(int i=0; i<(int)Simulation_List_Array.size(); i++)
    {
        for(int k = 0; k<(int)Simulation_List_Array[i].size(); k++)
        {
            Simulation_List_Array[i][k]->Ticket_Number = ticket_counter++;
            Simulation_Queue.push(Simulation_List_Array[i][k]);
        }
    }

    Thread_Size = MainWindow_Ui->thread_number->value();

    if(Thread_Size > (int)Simulation_Queue.size())
        Thread_Size = (int)Simulation_Queue.size();

    Sorted_Simulations.resize(Thread_Size);
    for(int i=0; i<Thread_Size; i++)
    {
        Simulation_Operators.push_back(std::make_shared<SimulationOperator>(i, this));
        Simulation *ptr = Simulation_Queue.front().get();
        Simulation_Queue.pop();
        ptr->Operator_Id = i;
        Simulation_Operators[i]->start(ptr);
    }

    MainWindow_Ui->simulation_progress->setValue(0);
    Current_Simulation_Progress = 0;

    if(Simulation_List_Array[0][0] != NULL)
        Progress_Duration = Simulation_List_Array[0][0]->Input_Info.Simulation_Duration;

}



void MainWindow::terminateOperators()
{

    for(int i=0; i< (int)Simulation_Operators.size(); i++)
    {
        Simulation_Operators[i]->Terminate_ = true;
        QThread::sleep(1);
    }

    while (!Simulation_Queue.empty())
    {
       Simulation_Queue.pop();
    }

    Thread_Size = 0;
    Simulation_Operators.clear();
    Sorted_Simulations.clear();

    Progress_Timer->stop();
    MainWindow_Ui->simulation_progress->setValue(0);
    Current_Simulation_Progress = 0;
    Progress_Duration = 0;
}



void MainWindow::startButtonToggled(bool checked)
{


    if(checked == true)
    {
        if(!Simulation_List_Array.empty())
        {

            Simulation_Running = true;
            MainWindow_Ui->start_label->setText("Running...");
            lockButtons();
            loadCurrentSimulationList(0);

            createOperators();
            Progress_Timer->start(1000 + Thread_Size+4);


        }
        else
        {
            MainWindow_Ui->start_button->setChecked(false);
        }

    }
    else
    {
        unlockButtons();
        Current_Simulation = 0;
        Current_Simulation_Array = 0;
        MainWindow_Ui->start_label->setText("stopped!");
        terminateOperators();

        for(int i=0; i < (int)Simulation_List_Array.size(); i++)
            for(int k=0; k < (int)Simulation_List.size(); k++)
                Simulation_List_Array[i][k]->resetSimulation();


    }

}
