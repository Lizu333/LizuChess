#include "MoveGenerator.h"

void MoveGenerator::addSlidingMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves,
    const Position& from,
    int dx,
    int dy) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    int x = from.getX() + dx;
    int y = from.getY() + dy;

    while (true)
    {
        Position to(x, y);

        if (!board.isInsideBoard(to))
            break;

        Piece targetPiece = board.getPiece(to);

        if (targetPiece.isEmpty())
        {
            moves.emplace_back(from, to);
        }
        else
        {
            if (targetPiece.getColor() != sideToMove)
            {
                moves.emplace_back(from, to);
            }

            break;
        }

        x += dx;
        y += dy;
    }
}