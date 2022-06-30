#ifndef CARD_H
#define CARD_H

#include "common.h"
class Card
{
public:
    Card(const CardColor& color, const int& num, const bool& isTransparent = false, const bool& isRed = false):
        _color(color), _num(num), _isTransparent(isTransparent), _isRed(isRed)
    {
//        if (_color == CardColor::E)
//            throw "Bad Card Color";
    }
    Card(const std::string& color, const int& num)
    {
        this->_num = num;
        this->setStatusFromCode(color, this->_num);
        if (this->_isRed)
            this->_num = 5;
        if (_color == CardColor::E)
            throw "Bad Card Color";
    }
    Card(const std::string& code)
    {
        this->_num = code[0] - '0';
        this->setStatusFromCode(code.substr(1,1), this->_num);
        if (this->_isRed)
            this->_num = 5;
        if (_color == CardColor::E)
            throw "Bad Card Color";
    }
    Card(const Card& rhs)
    {
        this->_color = rhs._color;
        this->_num = rhs._num;
        this->_isTransparent = rhs._isTransparent;
        this->_isRed = rhs._isRed;
    }

    Card operator=(const Card& rhs)
    {
        this->_color = rhs._color;
        this->_num = rhs._num;
        this->_isTransparent = rhs._isTransparent;
        this->_isRed = rhs._isRed;
        return *this;
    }
    CardColor getColor() const
    {
        return this->_color;
    }
    int getNum() const
    {
        return this->_num;
    }
    bool isTransparent() const
    {
        return this->_isTransparent;
    }
    bool isRed() const
    {
        return this->_isRed;
    }


    int getPseudoNum() const
    {
        return getPseudoNum(this->getColor(), this->getNum());
    }

    std::string getCode() const
    {
        std::string result = "";
        if (this->_isRed)
            result += "0";
        else
            result += std::to_string(this->getNum());
        result += Common::getCodeFromColor(this->getColor(), this->_isTransparent);
        return result;
    }

    bool is19Card() const
    {
        return this->_num == 1 || this->_num == 9 || this->_color == CardColor::Z;
    }

    bool isOldCard() const
    {
        return (this->_num == 1 || this->_num == 9) && this->_color != CardColor::Z;
    }

    bool isDragonCard() const
    {
        return this->_color == CardColor::Z
                && (this->_num == 5 || this->_num == 6 || this->_num == 7);
    }

    bool isWindCard() const
    {
        return this->_color == CardColor::Z
                && (this->_num == 1 || this->_num == 2 || this->_num == 3 || this->_num == 4);
    }

    bool isTargetWind(const WindType& targetWind) const
    {
        return this->_color == CardColor::Z
                && (Common::getWindFromInt((this->_num - 110) / 10) == targetWind);
    }

    static int getPseudoNum(const CardColor& color, const int& num)
    {
        switch (color)
        {
        case CardColor::M:
            return num;
            break;
        case CardColor::P:
            return num + 20;
            break;
        case CardColor::S:
            return num + 40;
            break;
        case CardColor::Z:
            return 100 + num * 10;
            break;
        case CardColor::U:
            return 200;
            break;
        case CardColor::E:
            throw "Bad Card Color";
            break;
        }
        throw "Bad Card Color";
    };

    static Card getCardFromPseudoNum(const int& pseudoNum)
    {
        CardColor color = CardColor::E;
        int num = 0;
        if (pseudoNum >= 1 and pseudoNum <= 9)
        {
            color = CardColor::M;
            num = pseudoNum;
        }
        if (pseudoNum >= 21 and pseudoNum <= 29)
        {
            color = CardColor::P;
            num = pseudoNum - 20;
        }
        if (pseudoNum >= 41 and pseudoNum <= 49)
        {
            color = CardColor::S;
            num = pseudoNum - 40;
        }
        if (pseudoNum >= 110 and pseudoNum <= 170 and pseudoNum % 10 == 0)
        {
            color = CardColor::Z;
            num = (pseudoNum - 100) / 10;
        }
        if (pseudoNum == 200)
        {
            color = CardColor::U;
            num = 1;
        }
        Card result(color, num);
        return result;
    }

    static bool isValidPseudoNum(const int& pseudoNum)
    {
        Card card = getCardFromPseudoNum(pseudoNum);
        if (card.getColor() == CardColor::E)
            return false;
        return true;
    }

protected:
    void setStatusFromCode(const std::string& colorCode, const int& num)
    {
        this->_color = Common::getColorFromCode(colorCode);
        this->_isTransparent = Common::isTransparentCard(colorCode);
        this->_isRed = Common::isRedCard(num);
    }
private:
    CardColor _color;
    int _num;
    bool _isTransparent;
    bool _isRed;

};

#endif // CARD_H
