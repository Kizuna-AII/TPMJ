#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    homeWin.reset(new HomeWindow(this));
    gameWin.reset(new GameWindow(this));

    ui.reset(new Ui::MainWindow());
    ui->setupUi(this);

//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(switchHomePageSlot()));
    connect(homeWin.get(), SIGNAL(switchHomeSignal()), this, SLOT(switchGamePageSlot()));
    connect(homeWin.get(), SIGNAL(exitAppSignal()), this, SLOT(exitAppSlot()));
    connect(gameWin.get(), SIGNAL(switchHomeSignal()), this, SLOT(switchHomePageSlot()));

    this->switchHomePageSlot();
}

MainWindow::~MainWindow()
{
//    delete home_win;
}

void MainWindow::hideAll()
{
    this->hide();
    this->homeWin->hide();
    this->gameWin->hide();
}

void MainWindow::switchHomePageSlot()
{
    qDebug() << "Switch to Home Page";
    this->hideAll();
    homeWin->show();
}

void MainWindow::switchGamePageSlot()
{
    qDebug() << "Switch to Game Page";
    this->hideAll();
    gameWin->show();
}

void MainWindow::exitAppSlot()
{
    this->close();
}
