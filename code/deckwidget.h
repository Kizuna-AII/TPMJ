#ifndef DECKWIDGET_H
#define DECKWIDGET_H

#include <QWidget>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include "cardwidget.h"
#include "deck.h"

constexpr int WidthBetweenCards = int(0.1 * DefaultCardWidth);
constexpr int HeightBetweenCards = int(0.1 * DefaultCardHeight);
//constexpr int DeckWidth = ;
//constexpr int DeckHeight = 200;

class DeckWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DeckWidget(const Deck& deck, QWidget *parent = nullptr);

signals:

public:
    void rendDeck();

protected:
    QRect getCardGeo(const size_t& index) const;
    double getCardScalar() const;
    int getViewWidth() const;
    int getViewHeight() const;
    int getViewX() const;
    int getViewY() const;
    int getCardRealWidth() const;
    int getCardRealHeight() const;
private:
    QVector<QPointer<CardWidget>> _cardWidgets;
    QScopedPointer<QGraphicsScene> _scene;
    Deck _deck;
};

#endif // DECKWIDGET_H
