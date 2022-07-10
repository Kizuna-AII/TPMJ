#ifndef CARD_H
#define CARD_H

#include "common.h"
class Card
{
public:
    Card(const CardColor& color, const int& num,
         const bool& isTransparent = false, const bool& isRed = false,
         const bool& isHorizontal = false):
        _color(color), _num(num), _isTransparent(isTransparent),
        _isRed(isRed), _isHorizontal(isHorizontal)

    {
//        if (_color == CardColor::E)
//            throw "Bad Card Color";
    }
    Card(const std::string& statusCode, const int& num)
    {
        this->_num = num;
        this->setStatusFromCode(statusCode);
//        if (this->_isRed)
//            this->_num = 5;
//        if (_color == CardColor::E)
//            throw "Bad Card Color";
    }
    Card(const std::string& code)
    {
        this->_num = code[0] - '0';
        this->setStatusFromCode(code.substr(1, code.length()));
//        if (this->_isRed)
//            this->_num = 5;
//        if (_color == CardColor::E)
//            throw "Bad Card Color";
    }
    Card(const Card& rhs)
    {
        this->_color = rhs._color;
        this->_num = rhs._num;
        this->_isTransparent = rhs._isTransparent;
        this->_isRed = rhs._isRed;
        this->_isHorizontal = rhs._isHorizontal;
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
    bool isHorizontal() const
    {
        return this->_isHorizontal;
    }


    int getPseudoNum() const
    {
        return getPseudoNum(this->getColor(), this->getNum());
    }

    std::string getCode() const
    {
        std::string result = "";
//        if (this->_isRed)
//            result += "0";
//        else
        result += std::to_string(this->getNum());
        result += Common::getCodeFromColor(this->getColor()/*, this->_isTransparent*/);
        if (this->isRed())
            result += "r";
        if (this->isTransparent())
            result += "t";
        if (this->isHorizontal())
            result += "h";
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
            return num + 100;
            break;
        case CardColor::P:
            return num + 200;
            break;
        case CardColor::S:
            return num + 300;
            break;
        case CardColor::Z:
            return num * 10 + 400;
            break;
        case CardColor::U:
            return 1000;
            break;
        case CardColor::E:
            throw "Bad Card Color";
            break;
        }
        throw "Bad Card Color";
    };

    // e.g. return 410 from "1z"
    static int getPseudoNumFromCode(const std::string& code)
    {
        Card card(code);
        return getPseudoNum(card.getColor(), card.getNum());
    }

    static Card getCardFromPseudoNum(const int& pseudoNum)
    {
        CardColor color = CardColor::E;
        int num = 0;
        if (pseudoNum >= 101 and pseudoNum <= 109)
        {
            color = CardColor::M;
            num = pseudoNum - 100;
        }
        else if (pseudoNum >= 201 and pseudoNum <= 209)
        {
            color = CardColor::P;
            num = pseudoNum - 200;
        }
        else if (pseudoNum >= 301 and pseudoNum <= 309)
        {
            color = CardColor::S;
            num = pseudoNum - 300;
        }
        else if (pseudoNum >= 410 and pseudoNum <= 470 and pseudoNum % 10 == 0)
        {
            color = CardColor::Z;
            num = (pseudoNum - 400) / 10;
        }
        else if (pseudoNum == 1000)
        {
            color = CardColor::U;
            num = 1;
        }
        else
        {
            color = CardColor::E;
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
    void setStatusFromCode(const std::string& colorCode)
    {
        this->_isRed = false;
        this->_isTransparent = false;
        this->_isHorizontal = false;

        this->_color = Common::getColorFromCode(colorCode.substr(0, 1));
        for (int index = 1; index < colorCode.length(); index++)
        {
            switch (colorCode[index])
            {
            case 'r':
                this->_isRed = true;
                break;
            case 't':
                this->_isTransparent = true;
                break;
            case 'h':
                this->_isHorizontal = true;
                break;
            }
        }
    }
private:
    CardColor _color;
    int _num;
    bool _isTransparent;
    bool _isRed;
    bool _isHorizontal;

};

#endif // CARD_H
