#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <algorithm>

enum class CardColor
{
    M, // 1-9万
    P, // 1-9饼
    S, // 1-9索
    Z, // 1-7字, 东南西北白发中
    U, // unknown card
    E, // error
};

enum class DeckPosition
{
    Down,   // on your side
    Right,  // on your right side
    Up,     // on your opposite side
    Left,   // on your left side
};


// for 13 + 1 cards
enum class DeckStatus
{
    Agari,          // 有役和牌
    YakunaiAgari,   // 无役和牌
    Ten,            // 13张牌已形式听牌（包含无役听牌）
    NoTen,          // 13张牌未听牌（13+1可能听牌）
};

// 听牌形状s
enum class WaitingType
{
    Single,     // 单骑
    TwoSide,    // 两面
    Middle,     // 嵌张
    OneSide,    // 边张
    Tile,       // 对碰
};

enum class WindType
{
    East,
    South,
    West,
    North,
};

enum class YakuName
{
    // 1 Han
    Reach,          // 立直
    IPpaTsu,        // 一发
    MenTsuMo,       // 门前清自摸和
    TanYao,         // 断幺
    PinHu,          // 平和
    IPeKo,          // 一杯口
    ChanKan,        // 抢杠
    HaiTei,         // 海底捞月
    HoTei,          // 河底捞鱼
    YakuRed,        // 役牌中
    YakuWhite,      // 役牌白
    YakuGreen,      // 役牌发
    YakuEast,       // 役牌东
    YakuSouth,      // 役牌南
    YakuWest,       // 役牌西
    YakuNorth,      // 役牌北
    DoubleEast,     // 役牌东
    DoubleSouth,    // 役牌南
    DoubleWest,     // 役牌西
    DoubleNorth,    // 役牌北

};

namespace Common
{
    constexpr int TotalPlayerNum        = 4;
    constexpr int RiverCardsPerRow      = 6;
    constexpr int DefaultCardMaxNum     = 14;
    constexpr int TotalPieceNumInDeck   = 5;
    constexpr int WindowWidth           = 1600;
    constexpr int WindowHeight          = 900;
    constexpr int DefaultPlayerPoint    = 25000;
    constexpr WindType StartFieldWind   = WindType::East;
    constexpr WindType EndFieldWind     = WindType::West;

    inline WindType getWindFromInt(const int& x)
    {
        switch (x)
        {
        case 0:
            return WindType::East;
            break;
        case 1:
            return WindType::South;
            break;
        case 2:
            return WindType::West;
            break;
        case 3:
            return WindType::North;
            break;
        }
        return StartFieldWind;
    }


    inline WindType NextWind(const WindType& wind)
    {
        switch(wind)
        {
        case WindType::East:
            return WindType::South;
            break;
        case WindType::South:
            return WindType::West;
            break;
        case WindType::West:
            return WindType::North;
            break;
        case WindType::North:
            return WindType::East;
            break;
        }
        return WindType::East;
    }

    inline DeckStatus BestDeckStatus(const DeckStatus& lhs, const DeckStatus& rhs)
    {
        if (lhs > rhs)
            return rhs;
        return lhs;
    }
    // code: like "D"
    inline DeckPosition getDeckPositionFromCode(const std::string& code)
    {
        std::string code_upper = code;
        std::transform(code_upper.begin(),code_upper.end(),code_upper.begin(), ::toupper);
        if (code_upper == "D")
            return DeckPosition::Down;
        if (code_upper == "R")
            return DeckPosition::Right;
        if (code_upper == "U")
            return DeckPosition::Up;
        if (code_upper == "L")
            return DeckPosition::Left;
        return DeckPosition::Down;
    }

    // code: like "D"
    inline std::string getCodeFromDeckPosition(const DeckPosition& pos)
    {
        switch (pos)
        {
        case DeckPosition::Down:
            return "D";
            break;
        case DeckPosition::Right:
            return "R";
            break;
        case DeckPosition::Up:
            return "U";
            break;
        case DeckPosition::Left:
            return "L";
            break;
        }
    }

    // code: like "M"
    inline CardColor getColorFromCode(const std::string& code)
    {
        std::string code_lower = code;
        std::transform(code_lower.begin(),code_lower.end(),code_lower.begin(), ::tolower);
        if(code_lower == "m")
        {
            return CardColor::M;
        }
        if(code_lower == "p")
        {
            return CardColor::P;
        }
        if(code_lower == "s")
        {
            return CardColor::S;
        }
        if(code_lower == "z")
        {
            return CardColor::Z;
        }
        if(code_lower == "u")
        {
            return CardColor::U;
        }
        return CardColor::E;
    }

    // "M": transparent, "m": normal
    inline bool isTransparentCard(const std::string& code)
    {
        if (code == "M" || code == "P" || code == "S" || code == "Z")
            return true;
        return false;
    }

    // 0: red, non-zero: non-red
    inline bool isRedCard(const int& num)
    {
        if (num == 0)
            return true;
        return false;
    }

    // code: like "M"
    inline std::string getCodeFromColor(const CardColor& color, const bool& isTransparent)
    {
        std::string result = "";
        switch(color)
        {
        case CardColor::M:
            result = "m";
            break;
        case CardColor::P:
            result = "p";
            break;
        case CardColor::S:
            result = "s";
            break;
        case CardColor::Z:
            result = "z";
            break;
        case CardColor::U:
            result = "u";
            break;
        case CardColor::E:
            result = "e";
            break;
        }
        if (isTransparent)
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }


}

#endif // COMMON_H
