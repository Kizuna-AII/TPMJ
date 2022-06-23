#ifndef TPMJGAME_H
#define TPMJGAME_H

#include <vector>
#include <array>
#include <memory>

#include "deck.h"
#include "deckanalyzer.h"


class TPMJGame
{
public:
    explicit TPMJGame();
    virtual ~TPMJGame() {}
private:
    std::vector<std::shared_ptr<Deck>> _decks;
};

#endif // TPMJGAME_H
