#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include "card.h"

constexpr int DefaultCardWidth = 36;
constexpr int DefaultCardHeight = 48;

//namespace Ui {
//class CardWidget;
//}

class CardWidget : public QLabel
{
    Q_OBJECT

public:
    explicit CardWidget(const Card& card, QWidget *parent = nullptr);
    ~CardWidget();

protected:
    Card _card;
};

#endif // CARDWIDGET_H
