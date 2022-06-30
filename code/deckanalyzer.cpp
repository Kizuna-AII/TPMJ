#include "deckanalyzer.h"



int DeckAnalyzer::getYaku() const
{
    int yaku = 0;
    bool good = true;
    // 断幺
    good = true;
    for (int i = 0; i < Common::TotalPieceNumInDeck && good; i++)
    {

        const std::vector<int>& piece = this->_pieces[i];
        for (const int& pNum: piece)
        {
            Card card = Card::getCardFromPseudoNum(pNum);
            if (card.is19Card())
                good = false;
        }
    }
    if (good)
    {
        yaku += 1;
    }

    return yaku;
}
