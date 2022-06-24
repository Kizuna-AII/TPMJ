#include "mainwindow.h"
#include "tpmjgame.h"
#include "deckanalyzer.h"

#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
    std::shared_ptr<Deck> deck(new Deck("D445566m456s4555p"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
//    std::shared_ptr<Deck> deck(new Deck("D1112345678999m"));
    std::shared_ptr<Card> card(new Card("6p"));
    DeckAnalyzer anal(
        deck, card,
        WindType::East, WindType::East,
        true, true,
        true
    );
    anal.checkDeckStatus();
    return 0;
}
