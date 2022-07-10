# General Design

整体而言，透明麻雀游戏的模块聚类有四种：Base模块、GUI模块、Server模块、Networking模块

若模块不涉及Qt，则使用std函数与成员；反则使用Qt函数与成员

## Base Modules

主要包含一些在GUI和Server中通用的参数和类

- Common: 游戏中大部分的常数，全部的枚举类，以及枚举类相应的操作函数
- Card: 单独一张麻雀牌的类
- Deck: 多张麻雀牌组成的一套牌（例如手牌、牌河等）
- AgariInfo: 一次和牌所需要的场况信息（和牌者、点炮者等）
- DeckAnalyzer: 对Deck进行穷举拆分、符数计算、番数计算的分析器
- AgariPoint: 根据番数、符数、AgariInfo等计算全场分数变化的类
- GameStatus: 游戏的整体状态，包括四家手牌、牌河、点数等

## GUI Modules

主要包含构成客户端GUI的类

- CardWidget: Qt类，根据Card信息构造一枚GUI上的麻雀牌
- DeckWidget: Qt类，根据Deck信息构造一组GUI上的麻雀牌
- GameWindow: Qt类，游戏窗口
- HomeWindow: Qt类，home页窗口
- MainWindow: Qt类，界面不会被显示，但维护顶层的窗口切换逻辑

## Server Modules

主要包含在服务端逻辑所需的类，待续

## Networking Modules

主要包含网络交互所需的类

- GameMessage: 将GameStatus根据需要发送的玩家id进行信息遮盖，打包为字符串
- NetworkInteractor: 朴素的建立连接、收发信息的交互器
- ClientInteractor: 继承NetworkInteractor，实现信息与GUI的交互
- ServerInteractor: 继承NetworkInteractor，实现信息与Server的交互

