#ifndef CARD_H
#define CARD_H

#include "common.h"
class Card
{
public:
    Card(const CardColor& color, const int& num):
        _color(color), _num(num)
    {
    }
    Card(const std::string& color, const int& num):
        _num(num)
    {
        _color = Common::getColorFromCode(color);
        if (_color == CardColor::E)
            throw "Bad Card Color";
    }
    Card(const std::string& code)
    {
        this->_num = code[0] - '0';
        _color = Common::getColorFromCode(code.substr(1,1));
        if (_color == CardColor::E)
            throw "Bad Card Color";
    }
    Card(const Card& rhs)
    {
        this->_color = rhs._color;
        this->_num = rhs._num;
    }

    Card operator=(const Card& rhs)
    {
        this->_color = rhs._color;
        this->_num = rhs._num;
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
    std::string getCode() const
    {
        std::string result = "";
        result += std::to_string(this->getNum());
        result += Common::getCodeFromColor(this->getColor());
        return result;
    }

private:
    CardColor _color;
    int _num;
};

#endif // CARD_H
