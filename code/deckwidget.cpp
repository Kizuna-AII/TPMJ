#include "deckwidget.h"

DeckWidget::DeckWidget(const Deck& deck, QWidget *parent)
//    : _deck(deck), QWidget{parent}
    :_deck(deck), QGraphicsView(parent)
{
    this->rendDeck();
}

void DeckWidget::rendDeck()
{
//    double cardWidth = this->getCardRealWidth();
//    double cardHeight = this->getCardRealHeight();
    DeckPosition deckPos = this->_deck.getDeckPosition();
    this->_scene.reset(new QGraphicsScene(this));
    int viewWidth = getViewWidth();
    int viewHeight = getViewHeight();
    int viewX = getViewX();
    int viewY = getViewY();
    this->setGeometry(viewX, viewY, viewWidth, viewHeight);

    Deck& deck = this->_deck;

    for (int i = 0; i < deck.getCardSize(); i++)
    {
        Card card = this->_deck.getCard(i);
        QRect cardGeo = getCardGeo(i);
        QPointer<CardWidget> cardWidget(new CardWidget(card));
        cardWidget->setGeometry(cardGeo);

        this->_cardWidgets.push_back(cardWidget);
        QGraphicsProxyWidget * pw = this->_scene->addWidget(cardWidget.get());

        double angle = 0.0;
        switch (deckPos)
        {
        case DeckPosition::Down:
            angle = 0.0;
            break;
        case DeckPosition::Right:
            angle = -90.0;
            break;
        case DeckPosition::Up:
            angle = -180.0;
            break;
        case DeckPosition::Left:
            angle = -270.0;
            break;
        }
        pw->setRotation(angle);
        pw->setPos(cardGeo.x(), cardGeo.y());
    }
    this->setStyleSheet("border:none; background:lightgray;");
    this->setScene(this->_scene.get());
}

int DeckWidget::getViewX() const
{
    DeckPosition deckPos = this->_deck.getDeckPosition();

    int viewWidth = getViewWidth();
    switch (deckPos)
    {
    case DeckPosition::Down:
        return Common::WindowWidth * 0.5 - viewWidth / 2.0;
        break;
    case DeckPosition::Right:
        return Common::WindowWidth * 0.9 - viewWidth / 2.0;
        break;
    case DeckPosition::Up:
        return Common::WindowWidth * 0.5 - viewWidth / 2.0;
        break;
    case DeckPosition::Left:
        return Common::WindowWidth * 0.1 - viewWidth / 2.0;
        break;
    }
    return 0;
}

int DeckWidget::getViewY() const
{
    DeckPosition deckPos = this->_deck.getDeckPosition();

    int viewHeight = getViewHeight();
    switch (deckPos)
    {
    case DeckPosition::Down:
        return Common::WindowHeight * 0.9 - viewHeight / 2.0;
        break;
    case DeckPosition::Up:
        return Common::WindowHeight * 0.12 - viewHeight / 2.0;
        break;
    case DeckPosition::Right:
    case DeckPosition::Left:
        return Common::WindowHeight * 0.5 - viewHeight / 2.0;
        break;
    }
    return 0;
}

int DeckWidget::getViewWidth() const
{
    DeckPosition deckPos = this->_deck.getDeckPosition();
    double cardWidth = this->getCardRealWidth();
    double cardHeight = this->getCardRealHeight();
    int num = Common::DefaultCardMaxNum;
    switch (deckPos)
    {
    case DeckPosition::Down:
    case DeckPosition::Up:
        return num * cardWidth + (num - 1) * getCardScalar() * WidthBetweenCards;
        break;
    case DeckPosition::Right:
    case DeckPosition::Left:
        return cardHeight;
        break;
    }
    return 0;
}

int DeckWidget::getViewHeight() const
{
    DeckPosition deckPos = this->_deck.getDeckPosition();
    double cardWidth = this->getCardRealWidth();
    double cardHeight = this->getCardRealHeight();
    int num = Common::DefaultCardMaxNum;
    switch (deckPos)
    {
    case DeckPosition::Down:
    case DeckPosition::Up:
        return cardHeight;
        break;
    case DeckPosition::Right:
    case DeckPosition::Left:
        return num * cardWidth + (num - 1) * getCardScalar() * WidthBetweenCards;
        break;
    }
    return 0;
}

double DeckWidget::getCardScalar() const
{
    DeckPosition deckPos = this->_deck.getDeckPosition();
    switch (deckPos)
    {
    case DeckPosition::Down:
        return 1.5;
        break;
    case DeckPosition::Right:
        return 1.0;
        break;
    case DeckPosition::Up:
        return 1.0;
        break;
    case DeckPosition::Left:
        return 1.0;
        break;
    }
    return 1.0;
}

int DeckWidget::getCardRealWidth() const
{
    int width = int(DefaultCardWidth * this->getCardScalar());
    return width;
}

int DeckWidget::getCardRealHeight() const
{
    int height = int(DefaultCardHeight * this->getCardScalar());
    return height;
}

QRect DeckWidget::getCardGeo(const size_t& index) const
{
//    Card card = this->_deck.getCard(index);
    DeckPosition deckPos = this->_deck.getDeckPosition();
//    int cardNum = this->_deck.getCardSize();
    double width = this->getCardRealWidth();
    double height = this->getCardRealHeight();
    double x = 0.0, y = 0.0;

    switch (deckPos)
    {
    case DeckPosition::Down:
        x = index * (width + WidthBetweenCards * getCardScalar());
        y = 0.0;
        break;
    case DeckPosition::Right:
        x = 0.0;
        y = this->getViewHeight() - index * (width + WidthBetweenCards * getCardScalar());
        break;
    case DeckPosition::Up:
        x = this->getViewWidth() - index * (width + WidthBetweenCards * getCardScalar());
        y = 0.0;
        break;
    case DeckPosition::Left:
        x = 0.0;
        y = index * (width + WidthBetweenCards * getCardScalar());
        break;
    }
    return QRect(x, y, width, height);
}
