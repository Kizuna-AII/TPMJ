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


namespace Common
{
    constexpr int RiverCardsPerRow = 6;
    constexpr int DefaultCardMaxNum = 14;
    constexpr int WindowWidth = 1600;
    constexpr int WindowHeight = 900;

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

    // code: like "M"
    inline std::string getCodeFromColor(const CardColor& color)
    {
        switch(color)
        {
        case CardColor::M:
            return "m";
            break;
        case CardColor::P:
            return "p";
            break;
        case CardColor::S:
            return "s";
            break;
        case CardColor::Z:
            return "z";
            break;
        case CardColor::U:
            return "u";
            break;
        case CardColor::E:
            return "e";
            break;
        }
    }
}

#endif // COMMON_H
