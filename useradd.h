#ifndef USERADD_H
#define USERADD_H

#include <QDialog>

class SimulationAddWindow;

namespace Ui {
class UserAdd;
}

class UserAdd : public QDialog
{
    Q_OBJECT

public:
    explicit UserAdd(QWidget *parent = nullptr);
    ~UserAdd();

private slots:
    void acceptedButtonClicked();
    void rejectedButtonClicked();


private:
    Ui::UserAdd *ui;

    SimulationAddWindow *Simulation_Add_Window;
};

#endif // USERADD_H
