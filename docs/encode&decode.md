# Card

String Encode:

- Card Number: 1~9 (1~7 for z, 东南西北中白发)
- Card Color: m(man), p(pin), s(sou), z(zi), u(unknown)
- [Optional] Red Card: r
- [Optional] Transparent Card: t
- [Optional] Horizontal Card: h

Pseudo Number Encode(for Mahjong cards analysis):

- [1-9]m: 101~109
- [1-9]p: 201~209
- [1-9]s: 301~309
- [1-7]z: 410, 420, 430, 440, 450, 460, 470

# Deck

- First char "D", "R", "U" or "L" means down, right, up or left side
- "|" means the division between cards （副露）

e.g.

"D123s456m5p5pat|88ph8ph8p"

means

Down Side, "1s2s3s4m5m6m5p5pat" cards + "8p8ph8ph8p" kan cards

