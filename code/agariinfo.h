#ifndef AGARIINFO_H
#define AGARIINFO_H


class AgariInfo
{
public:
    // rongPlayerIndex == agariPlayerIndex means tsumo
    AgariInfo(const int& agariPlayerIndex, const int & ronPlayerIndex, const int& bankerPlayerIndex)
        : _agariPlayerIndex(agariPlayerIndex), _ronPlayerIndex(ronPlayerIndex), _bankerPlayerIndex(bankerPlayerIndex)
    {}

    int getAgariPlayerIndex() const
    {
        return this->_agariPlayerIndex;
    }
    int getRonPlayerIndex() const
    {
        return this->_ronPlayerIndex;
    }
    int getBankerPlayerIndex() const
    {
        return this->_bankerPlayerIndex;
    }
    bool isTsumo() const
    {
        return this->getAgariPlayerIndex() == this->getRonPlayerIndex();
    }
    bool isBanker() const
    {
        return this->getAgariPlayerIndex() == this->getBankerPlayerIndex();
    }

protected:
    int _agariPlayerIndex;
    int _ronPlayerIndex;
    int _bankerPlayerIndex;

};

#endif // AGARIINFO_H
