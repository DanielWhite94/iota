## Introduction
iota aims to be a tiny C chess engine, supporting the full rules of chess, as
well as a standard protocol. More precisely, it aims to:

1. support (a subset of) a standard protocol (UCI or CECP) such that a full game
can be played, and
2. for every *legal position* in which a legal move exists, be able to give one.

Where we define a *legal position* as one which can be reached from the initial
position by a sequence of legal moves. It includes the full game state. While it
may be arbitrary, we require a standard protocol because one could imagine a
pathological protocol where the GUI sends a list of legal moves, from which the
engine then selects one. This would reduce the exercise to writing the smallest
program which repeatedly chooses the first move (say).

For the first criteria we use the UCI protocol, in particular the following
commands are used: 'uci'/'uciok', 'isready'/'readyok', 'position' and
'go'/'bestmove'. While iota does obey the second requirement - so accepting
en-passent captures, under-promotions and castling - it will never castle
itself. Note that this is not a violation because if we have the option to
castle, then we always have the alternatives of simply moving either one of the
king or rook toward the other.

## Acknowledgements
I would like to give thanks to H. G. Muller (HGM) both for his engine MicroMax
and its description, and also for his practical
[definition](http://home.hccnet.nl/h.g.muller/definition.txt) of a chess
program:
> A Chess program is a program that can finish more than 50% of the games it
> plays against an opponent that plays moves randomly chosen from the set of
> Chess moves that are legal from the current position according to the FIDE
> rules.
