#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    connect(ui->homeButton, SIGNAL(clicked()), this, SIGNAL(switchHomeSignal()));

    QString filename = "../images/1p.bmp";
    QImage* img = new QImage;
    qDebug() << img->load(filename);
    ui->card->setPixmap(QPixmap::fromImage(*img));
//    QColor crA = QColor(225, 225, 225, 125);
//    QString str = QString("QLabel{background:%1;}").arg(crA.name(QColor::HexRgb));
//    ui->card->setStyleSheet(str);

//    Card c = Card("M", 1);
//    _card.reset(new CardWidget(c, this));
//    QRect geo = _card->geometry();
//    geo.setX(700);
//    geo.setY(600);
//    _card->setGeometry(geo);
    _decks.emplace_back(QSharedPointer<DeckWidget>(new DeckWidget(Deck("D123p456s789m111z11u"), this)));
    _decks.emplace_back(QSharedPointer<DeckWidget>(new DeckWidget(Deck("R123p456s789m111z11u"), this)));
    _decks.emplace_back(QSharedPointer<DeckWidget>(new DeckWidget(Deck("U123p456s789m111z11u"), this)));
    _decks.emplace_back(QSharedPointer<DeckWidget>(new DeckWidget(Deck("L123p456s789m111z11u"), this)));
}

GameWindow::~GameWindow()
{
//    delete ui;
}
