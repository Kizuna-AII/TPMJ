#include "homewindow.h"
#include "./ui_homewindow.h"


HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

//    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(this->switchHomeSignal()));
    connect(ui->gameStartButton, SIGNAL(clicked()), this, SLOT(switchHomeSlots()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SIGNAL(exitAppSignal()));
}


HomeWindow::~HomeWindow()
{

}

void HomeWindow::switchHomeSlots(void)
{
    emit switchHomeSignal();
//    this->hide();
}

