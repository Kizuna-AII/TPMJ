#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "cardwidget.h"
#include "deckwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

signals:
    void switchHomeSignal(void);

private:
    QScopedPointer<Ui::GameWindow> ui;
    QScopedPointer<CardWidget> _card;
    QVector<QSharedPointer<DeckWidget>> _decks;


};

#endif // GAMEWINDOW_H
