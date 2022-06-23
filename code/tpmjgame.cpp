#include "tpmjgame.h"

TPMJGame::TPMJGame()
{
    std::shared_ptr<Deck> deck(new Deck("D112233p456s789m11z"));
    this->_decks.emplace_back();
}
