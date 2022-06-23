#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include <algorithm>

#include "card.h"

// multiple cards
class Deck
{
public:
    // code: like "D123p456s789m111z11u"
    Deck(const std::string& code)
    {
        this->_pos = Common::getDeckPositionFromCode(code.substr(0, 1));
        this->_cards = getCardsFromCode(code.substr(1));
    }

    Deck(const Deck& rhs)
    {
        this->_pos = rhs._pos;
        this->_cards.assign(rhs._cards.begin(), rhs._cards.end());
    }
    Deck operator=(const Deck& rhs)
    {
        this->_pos = rhs._pos;
        this->_cards.assign(rhs._cards.begin(), rhs._cards.end());
        return *this;
    }

    DeckPosition getDeckPosition() const
    {
        return this->_pos;
    }
    std::vector<Card>& getCards()
    {
        return this->_cards;
    }
    size_t getCardSize() const
    {
        return this->_cards.size();
    }
    Card getCard(const size_t& index) const
    {
        return this->_cards[index];
    }
    std::vector<Card> getCards() const
    {
        return this->_cards;
    }
    void addCard(const Card& card)
    {
        this->_cards.push_back(card);
    }
    void addCard(const std::string& code)
    {
        this->_cards.push_back(Card(code));
    }
    std::string getCode() const
    {
        std::string code = "";
        code += Common::getCodeFromDeckPosition(this->_pos);
        for (const Card& card: this->_cards)
        {
            code += card.getCode();
        }
        return code;
    }



    // code: like 123p456s789m111z11u
    static std::vector<Card> getCardsFromCode(const std::string& code)
    {
        std::string buf = "";
        std::vector<Card> result;
        for (int i = 0; i < code.length(); i++)
        {
            CardColor color = Common::getColorFromCode(code.substr(i, 1));
            if (color != CardColor::E) // color char
            {
                if (buf.length() <= 0) // no number
                {
                    throw "getCardsFromCode::No Enough Number Before Color";
                }
                for (const char& buf_ch: buf)
                {
                    Card card = Card(color, buf_ch - '0');
                    result.push_back(card);
                }
                buf = "";
            } else
            {
                buf += code[i];
            }
        }
        return result;
    }

protected:
    std::vector<Card> _cards;
    DeckPosition _pos;
};



#endif // DECK_H
