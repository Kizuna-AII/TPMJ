#ifndef AGARIPOINT_H
#define AGARIPOINT_H

#include "deck.h"
#include "gamestatus.h"
#include "agariinfo.h"

class AgariPoint
{
public:

    AgariPoint(
            const int& han, const int& fu,
            const AgariInfo& info
        )
        : _han(han), _fu(fu), _info(info)
    {
        this->calcPoint();
    }
    int getFu() const
    {
        return this->_fu;
    }
    int getHan() const
    {
        return this->_han;
    }
    AgariInfo getInfo() const
    {
        return this->_info;
    }
    std::vector<int> getPlayerPointChange()
    {
        return this->_playerPointChange;
    }
    int getTotalPoint()
    {
        return this->_totalPoint;
    }

    std::vector<int> calcPoint()
    {
        int fu = getFu();
        int han = getHan();
        int single = fu * (2 << (han + 1));
        int totalPoint = 1000;

        this->_playerPointChange.clear();
        if (han == 0) // 无役
        {
            for (int index = 0; index < Common::TotalPlayerNum; index++)
                this->_playerPointChange.emplace_back(0);
            totalPoint = 0;
            this->_totalPoint = totalPoint;
            return _playerPointChange;
        }
        if (this->getInfo().isTsumo()) // 自摸
        {
            int childPart =  single;
            if (childPart % 100 != 0)
                childPart = childPart / 100 * 100 + 100;
            int bankerPart =  2 * single;
            if (bankerPart % 100 != 0)
                bankerPart = bankerPart / 100 * 100 + 100;
            if (this->getInfo().isBanker())
            {
                totalPoint = bankerPart * 3;
                for (int index = 0; index < Common::TotalPlayerNum; index++)
                {
                    if (index == this->getInfo().getAgariPlayerIndex())
                        this->_playerPointChange.emplace_back(+totalPoint);
                    else
                        this->_playerPointChange.emplace_back(-bankerPart);
                }
            }
            else
            {
                totalPoint = bankerPart + childPart * 2;
                for (int index = 0; index < Common::TotalPlayerNum; index++)
                {
                    if (index == this->getInfo().getAgariPlayerIndex())
                        this->_playerPointChange.emplace_back(+totalPoint);
                    else if (index == this->getInfo().getBankerPlayerIndex())
                        this->_playerPointChange.emplace_back(-bankerPart);
                    else
                        this->_playerPointChange.emplace_back(-childPart);
                }
            }

        }
        else // 荣和
        {
            if (this->getInfo().isBanker())
            {
                totalPoint = 6 * single;
                if (totalPoint % 100 != 0)
                    totalPoint = totalPoint / 100 * 100 + 100;
            }
            else
            {
                totalPoint = 4 * single;
                if (totalPoint % 100 != 0)
                    totalPoint = totalPoint / 100 * 100 + 100;
            }
            for (int index = 0; index < Common::TotalPlayerNum; index++)
            {
                if (index == this->getInfo().getAgariPlayerIndex())
                    this->_playerPointChange.emplace_back(+totalPoint);
                else if (index == this->getInfo().getRonPlayerIndex())
                    this->_playerPointChange.emplace_back(-totalPoint);
                else
                    this->_playerPointChange.emplace_back(0);
            }
        }
        this->_totalPoint = totalPoint;
        return _playerPointChange;
    }
private:
    int _han;
    int _fu;
    AgariInfo _info;

    int _totalPoint;
    std::vector<int> _playerPointChange;
};

#endif // AGARIPOINT_H
