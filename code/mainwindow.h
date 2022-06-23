#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPointer>
#include <memory>
#include "homewindow.h"
#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void hideAll(void);
    void switchHomePageSlot(void);
    void switchGamePageSlot(void);
    void exitAppSlot(void);

private:
// sub windows
    QScopedPointer<HomeWindow> homeWin;
    QScopedPointer<GameWindow> gameWin;

// UI for main window
    QScopedPointer<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
