#ifndef DECKANALYZER_H
#define DECKANALYZER_H

#include "deck.h"
#include "gamestatus.h"
#include "agaripoint.h"
#include <set>
#include <QDebug>
#include <iostream>



class DeckAnalyzer
{
public:
    DeckAnalyzer(
            std::shared_ptr<Deck> handDeck, std::shared_ptr<Card> judgeCard,
            const WindType& fieldWind, const WindType& selfWind,
            const bool& isClean, const AgariInfo& info)
        : _handDeck(handDeck), _judgeCard(judgeCard),
          _fieldWind(fieldWind), _selfWind(selfWind),
          _isClean(isClean), _info(info)
    {

    }
    AgariInfo getInfo() const
    {
        return this->_info;
    }
    DeckStatus checkDeckStatus()
    {
        this->_bestPoint = 0;
        this->_bestDeckStatus = DeckStatus::NoTen;
        this->_pseudoArr = getPseudoArray();
        this->_pseudoJudgeCard = _judgeCard->getPseudoNum();
        this->_waitingCardsNow = -1;
        this->_waitingCardsTotal.clear();
        if (this->_handDeck->getCardSize() % 3 != 1)
            return DeckStatus::NoTen;
        dfs(1, this->_handDeck->getCardSize(), true, false, 1);
        qDebug() << "status: " << int(this->_bestDeckStatus);
        qDebug() << "best point: " << int(this->_bestPoint);
        qDebug() << "check cards: ";
        for (const auto& cardNum: this->_waitingCardsTotal)
            qDebug() << Card::getCardFromPseudoNum(cardNum).getCode().c_str() << " ";
        qDebug() << "\n";
        return this->_bestDeckStatus;
    }

protected:
    ///
    /// \brief dfs
    /// \param pseudoNumNow: pseudo number now, 1~170
    /// \param cardsNum: number of remaining cards now, 1~13
    /// \param hasBlank: true means there are blank chances
    /// \param foundHead: whether has found head (two-pieces)
    /// \param threeIndex: index of three-pieces
    /// \return
    ///
    void dfs(
            const int& num, const int& cardsNum,
            const bool& hasBlank, const bool& foundHead,
            const int& threeIndex)
    {
        if (cardsNum == 0) // tenpai
        {
            if (this->_waitingCardsNow == _pseudoJudgeCard) // agari
            {
                int point = getDeckTotalPoint();
                // update best point
                if (point > this->_bestPoint)
                    this->_bestPoint = point;
                if (point > 0)  // Yaku existed
                    _bestDeckStatus = Common::BestDeckStatus(_bestDeckStatus, DeckStatus::Agari);
                else            // Yaku non-existed
                    _bestDeckStatus = Common::BestDeckStatus(_bestDeckStatus, DeckStatus::YakunaiAgari);
            } else // non-agari
            {
                _bestDeckStatus = Common::BestDeckStatus(_bestDeckStatus, DeckStatus::Ten);
            }
            this->_waitingCardsTotal.insert(_waitingCardsNow);
            return;
        }
        if (num >= Card::getPseudoNumFromCode("7z") + 1)
            return;
        if (_pseudoArr[num] == 0) // no card here
        {
            // try to consume straight with head blank
            if (_pseudoArr[num + 1] > 0 && _pseudoArr[num + 2] > 0 && hasBlank && threeIndex <= 4 && Card::isValidPseudoNum(num))
            {
                _pseudoArr[num + 1]--;
                _pseudoArr[num + 2]--;
                _pieces[threeIndex] = {num, num + 1, num + 2};
                this->_waitingCardsNow = num;
                this->_waitingType = WaitingType::TwoSide;
                this->_agariPieceIndex = threeIndex;
                dfs(num, cardsNum - 2, false, foundHead, threeIndex + 1);
                _pseudoArr[num + 1]++;
                _pseudoArr[num + 2]++;
                _pieces[threeIndex].clear();
            }

            // directly go on
            dfs(num + 1, cardsNum, hasBlank, foundHead, threeIndex);
        }
        else // card existed here
        {
            if (threeIndex <= 4) // three pieces remains
            {
                if (_pseudoArr[num] >= 3)
                    // try to consume three of a kind
                {
                    _pseudoArr[num] -= 3;
                    _pieces[threeIndex] = {num, num, num};
                    dfs(num, cardsNum - 3, hasBlank, foundHead, threeIndex + 1);
                    _pseudoArr[num] += 3;
                    _pieces[threeIndex].clear();
                }
                if (_pseudoArr[num] >= 2 && hasBlank && Card::isValidPseudoNum(num))
                    // try to consume three of a kind with blank
                {
                    _pseudoArr[num] -= 2;
                    _pieces[threeIndex] = {num, num, num};
                    this->_waitingCardsNow = num;
                    this->_waitingType = WaitingType::Tile;
                    this->_agariPieceIndex = threeIndex;
                    dfs(num, cardsNum - 2, false, foundHead, threeIndex + 1);
                    _pseudoArr[num] += 2;
                    _pieces[threeIndex].clear();
                }
                if (_pseudoArr[num + 1] >= 1 && _pseudoArr[num + 2] >= 1)
                    // try to consume straight
                {
                    _pseudoArr[num]--;
                    _pseudoArr[num + 1]--;
                    _pseudoArr[num + 2]--;
                    _pieces[threeIndex] = {num, num + 1, num + 2};
                    dfs(num, cardsNum - 3, hasBlank, foundHead, threeIndex + 1);
                    _pseudoArr[num]++;
                    _pseudoArr[num + 1]++;
                    _pseudoArr[num + 2]++;
                    _pieces[threeIndex].clear();
                }
                if (_pseudoArr[num + 1] == 0 && _pseudoArr[num + 2] >= 1 && hasBlank && Card::isValidPseudoNum(num + 1))
                    // try to consume straight with middle blank
                {
                    _pseudoArr[num]--;
                    _pseudoArr[num + 2]--;
                    _pieces[threeIndex] = {num, num + 1, num + 2};
                    this->_waitingCardsNow = num + 1;
                    this->_waitingType = WaitingType::Middle;
                    this->_agariPieceIndex = threeIndex;
                    dfs(num, cardsNum - 2, false, foundHead, threeIndex + 1);
                    _pseudoArr[num]++;
                    _pseudoArr[num + 2]++;
                    _pieces[threeIndex].clear();
                }
                if (_pseudoArr[num + 1] >= 1 && _pseudoArr[num + 2] == 0 && hasBlank && Card::isValidPseudoNum(num + 2))
                    // try to consume straight with tail blank
                {
                    _pseudoArr[num]--;
                    _pseudoArr[num + 1]--;
                    _pieces[threeIndex] = {num, num + 1, num + 2};
                    this->_waitingCardsNow = num + 2;
                    this->_waitingType = WaitingType::TwoSide;
                    this->_agariPieceIndex = threeIndex;
                    dfs(num, cardsNum - 2, false, foundHead, threeIndex + 1);
                    _pseudoArr[num]++;
                    _pseudoArr[num + 1]++;
                    _pieces[threeIndex].clear();
                }
            }
            if (not foundHead) // head remains
            {
                if (_pseudoArr[num] >= 2)
                    // try to consume head
                {
                    _pseudoArr[num] -= 2;
                    _pieces[0] = {num, num};
                    dfs(num, cardsNum - 2, hasBlank, false, threeIndex);
                    _pseudoArr[num] += 2;
                    _pieces[0].clear();
                }
                if (_pseudoArr[num] >= 1 && hasBlank && Card::isValidPseudoNum(num))
                    // try to consume head with blank
                {
                    _pseudoArr[num] -= 1;
                    _pieces[0] = {num, num};
                    this->_waitingCardsNow = num;
                    this->_waitingType = WaitingType::Single;
                    this->_agariPieceIndex = 0;
                    dfs(num, cardsNum - 1, false, false, threeIndex);
                    _pseudoArr[num] += 1;
                    _pieces[0].clear();
                }
            }
        }
    }
    int getDeckTotalPoint()
    {
        _agariPoint.reset(new AgariPoint(this->getHan(), this->getFu(), this->getInfo()));
        return _agariPoint->getTotalPoint();
    }
    int getFu() const
    {
        int fu = 20;
        if (this->_waitingType == WaitingType::Single ||
            this->_waitingType == WaitingType::Middle ||
            this->_waitingType == WaitingType::OneSide)
        {
            fu += 2;
        }
        int fieldWindNum = (int(this->_fieldWind) + 1) * 10 + 400;
        int selfWindNum = (int(this->_selfWind) + 1) * 10 + 400;
        // ???????????????????????????
        if (this->_pieces[0][0] == fieldWindNum)
            fu += 2;
        if (this->_pieces[0][0] == selfWindNum)
            fu += 2;
        if (this->_pieces[0][0] == 150)
            fu += 2;
        if (this->_pieces[0][0] == 160)
            fu += 2;
        if (this->_pieces[0][0] == 170)
            fu += 2;
        if (this->_isClean && !this->getInfo().isTsumo())
            fu += 10;
        for (int i = 1; i <= 4; i++)
        {
            if (_pieces[i][0] == _pieces[i][1] && _pieces[i][1] == _pieces[i][2])
                // three of a kind
            {
                Card card = Card::getCardFromPseudoNum(_pieces[i][0]);
                bool Dark = true;
                if (!this->getInfo().isTsumo() && this->_agariPieceIndex == i) // ???????????????
                    Dark = false;
                int addBase = 2;
                if (card.is19Card())
                    addBase *= 2;
                if (Dark)
                    addBase *= 2;
                fu += addBase;
            }
        }
        if (this->getInfo().isTsumo())
        {
            if (fu == 20 && this->_isClean) // ???????????????20
                fu = 20;
            else fu += 2;
        }
        if (!this->getInfo().isTsumo() && fu == 20) // ??????????????????30
        {
            fu = 30;
        }
        if (fu % 10 != 0) // ??????
        {
            fu = fu / 10 * 10 + 10;
        }
        return fu;
    }
    int getYaku() const;
    int getDoraNum() const
    {
        return 1;
    }
    int getHan() const
    {
        int yaku = getYaku();
        if (yaku == 0) // Yaku nashi
        {
            return 0;
        }
        int doraNum = getDoraNum();
        return yaku + doraNum;
    }
    int getRedCardsNum() const
    {
        int cnt = 0;
        for (const Card& card: this->_handDeck->getCards())
            if (card.isRed())
                cnt++;
        return cnt;
    }
    std::array<int, 1010> getPseudoArray() const
    {
        std::array<int, 1010> result {0};
        for (const Card& card: this->_handDeck->getCards())
            result[card.getPseudoNum()]++;
        return result;
    }

protected:

private:
    std::array<int, 1010> _pseudoArr {0};
    int _pseudoJudgeCard = 0;
    DeckStatus _bestDeckStatus = DeckStatus::NoTen;
    int _bestPoint = 0;
    int _waitingCardsNow; // the cards are able to formally agari now
    std::set<int> _waitingCardsTotal; // the cards are able to formally agari in total
    std::array<std::vector<int>, 10> _pieces;
    WaitingType _waitingType;
    int _agariPieceIndex;
    std::shared_ptr<AgariPoint> _agariPoint;
    AgariInfo _info;

    bool _isClean;
//    bool _isTsumo;
//    bool _isBanker;
    WindType _fieldWind;
    WindType _selfWind;
    std::shared_ptr<Deck> _handDeck;
    std::shared_ptr<Card> _judgeCard;
};

#endif // DECKANALYZER_H
