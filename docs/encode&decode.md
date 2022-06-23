# Card

String Encode:

- [1-9]m: normal 1-9 MAN, [1-9]M: transparent 1-9 MAN
- [1-9]p: normal 1-9 PIN, [1-9]P: transparent 1-9 PIN
- [1-9]s: normal 1-9 SOU, [1-9]S: transparent 1-9 SOU
- 0m, 0p, 0s: red(aka) and normal 5 MAN/PIN/SOU,  0M, 0P, 0S: red(aka) and transparent 5 MAN/PIN/SOU
- [1-7]z: 东南西北中白发
- 1u: unknown card

Pseudo Number Encode(for Mahjong cards analysis):

- [1-9]m: 1~9
- [1-9]p: 21~29
- [1-9]s: 41~49
- [1-7]z: 110, 120, 130, 140, 150, 160, 170

# Deck

e.g.

"D123S406m789p11Z"

means

Down Side, "1S2S3S4m0m6m7p8p9p1Z1Z" cards

