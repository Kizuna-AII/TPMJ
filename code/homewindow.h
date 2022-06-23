#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class HomeWindow; }
QT_END_NAMESPACE

class HomeWindow : public QMainWindow
{
    Q_OBJECT
public:
    HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

public slots:
    void switchHomeSlots(void);

signals:
    void switchHomeSignal(void);
    void exitAppSignal(void);

private:
    QScopedPointer<Ui::HomeWindow> ui;
};

#endif // HOMEWINDOW_H
