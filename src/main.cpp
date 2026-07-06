#include <iostream>

#include "core/Game.h"
#include "engine/chessengine/ChessEngine.h"

int main()
{
    ChessEngine engine;

    std::vector<Move> moves = engine.generateLegalMoves();

    std::cout << "Generated moves: " << moves.size() << std::endl;

    for (const Move& move : moves)
    {
        std::cout
            << "(" << move.getFrom().getX()
            << ", " << move.getFrom().getY()
            << ") -> ("
            << move.getTo().getX()
            << ", " << move.getTo().getY()
            << ")"
            << std::endl;
    }

    Game game;
    game.run();

    return 0;
}