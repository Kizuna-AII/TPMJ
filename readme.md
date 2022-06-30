# Transparent Mahjong

本项目为参考斗牌传说瓦西子麻雀战规则，制作的透明麻雀（Transparent Mahjong）。预计支持线上对战。不打算商用，可能包含无版权素材。
目前仍在前期开发中。

# Environment

- Programming Language: C++
- Framework: Qt Creator 7.0.0, Qt 6.2.3, MSVC 2019 64bit
- Make Tool: CMake

# Develop Plan

- ~~Qt环境搭建~~
- ~~主页GUI-基本按钮~~
- ~~游戏页GUI-四家手牌~~
- 游戏页GUI-出牌
- 游戏页GUI-吃、碰、杠、荣和、自摸
- 游戏页GUI-剩余牌数、本场、宝牌、四家分数、庄家标记
- 游戏页GUI-和牌番种、分数显示
- 游戏页GUI-终局分数显示
- ~~麻雀规则-牌（Card）~~
- ~~麻雀规则-一组牌（Deck）~~
- ~~麻雀规则-和牌基本信息（AgariInfo）、游戏基本信息（GameStatus）~~
- ~~麻雀规则-牌型分解（DeckAnalyzer）~~
- ~~麻雀规则-形式听牌、形式和牌判定（DeckAnalyzer）~~~~
- 麻雀规则-役种枚举（YakuAnalyzer）、番数计算（GetHan()）
- 麻雀规则-暗杠/副露（牌型分解DFS前固定副露的面子，并修改DFS参数）
- ~~麻雀规则-符数、点数变化计算（getHu(), AgariPoint)~~
- 麻雀规则-振听判定
- 网络库-信息交互验证
- 服务端-牌山生成、初始手牌分配
- 服务端-摸牌、切牌
- 服务端-吃、碰、杠、荣和、自摸
- 服务端-每局结算
- 服务端-终局结算
- 待补充



