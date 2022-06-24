#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "common.h"

class GameStatus
{
public:
    GameStatus()
    {
        init();
    }

    void init()
    {
        _bankerIndex = 0;
        _fieldWind = WindType::East;
        _comboNum = 0;
        _reachBarNum = 0;
        _playerPoints.assign(Common::TotalPlayerNum, Common::DefaultPlayerPoint);
        _isGameOver = false;
    }

    void passBanker() // 过庄
    {
        _bankerIndex++;
        if (_bankerIndex == Common::TotalPlayerNum)
        {
            _bankerIndex = 0;
            _fieldWind = Common::NextWind(_fieldWind);
        }
        if (_fieldWind == Common::EndFieldWind)
            setGameOver(true);
    }

    void keepFlow() // 连庄流局
    {
        addCombo();
    }

    void passFlow() // 过庄流局
    {
        addCombo();
        passBanker();
    }

    void childAgari() // 子家和牌
    {
        passBanker();
        clearCombo();
        clearReachBar();
    }

    void bankerAgari() // 亲家和牌
    {
        addCombo();
        clearReachBar();
    }

    WindType getFieldWind() const
    {
        return _fieldWind;
    }

    WindType getSelfWind(const int& index) const
    {
        int diff = index - _bankerIndex;
        if (diff < 0)
            diff += Common::TotalPlayerNum;
        WindType result = WindType::East;
        for (int i = 0; i < diff; i++)
            result = Common::NextWind(result);
        return result;
    }

    int getBankerIndex() const
    {
        return _bankerIndex;
    }

    int getComboNum() const
    {
        return _comboNum;
    }

    int getReachBarNum() const
    {
        return _reachBarNum;
    }

    bool isGameOver() const
    {
        return _isGameOver;
    }

    int getPlayerPoint(const int& index) const
    {
        return _playerPoints[index];
    }

    std::vector<int>& getPlayerPoints()
    {
        return _playerPoints;
    }

    int addPlayerPoint(const int& index, const int& increment)
    {
        _playerPoints[index] += increment;
        return _playerPoints[index];
    }
protected:
    void setGameOver(const bool& isGameOver)
    {
        _isGameOver = isGameOver;
    }
    void addCombo(const int& increment = 1) // 增加本场棒
    {
        _comboNum += increment;
    }

    void clearCombo() // 清除连庄
    {
        _comboNum = 0;
    }

    void addReachBar(const int& increment = 1) // 增加立直棒
    {
        _reachBarNum += increment;
    }

    void clearReachBar() // 清除立直棒
    {
        _reachBarNum = 0;
    }

private:
    int _bankerIndex;
    WindType _fieldWind;
    int _comboNum;
    int _reachBarNum;
    std::vector<int> _playerPoints;
    bool _isGameOver;
};

#endif // GAMESTATUS_H
