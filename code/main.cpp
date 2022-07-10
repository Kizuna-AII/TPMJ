#include "mainwindow.h"
#include "tpmjgame.h"
#include "deckanalyzer.h"
#include "agariinfo.h"
#include <QApplication>

#define TESTMAIN (2)

#if TESTMAIN == 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif

#if TESTMAIN == 2
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
    std::shared_ptr<Deck> deck(new Deck("D445566m456s455p5prt"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
    std::shared_ptr<Card> card(new Card("6p"));
//    std::shared_ptr<Card> card(new Card("1m"));
    AgariInfo info(0,0,0);
    DeckAnalyzer anal(
        deck, card,
        WindType::East, WindType::East,
        true, info
    );
    anal.checkDeckStatus();
    qDebug() << deck->getCode().c_str();
    return 0;
}
#endif
