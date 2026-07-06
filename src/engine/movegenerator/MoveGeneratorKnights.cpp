#include "MoveGenerator.h"

void MoveGenerator::generateKnightMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    const int offsetX[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int offsetY[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Knight)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            for (int i = 0; i < 8; i++)
            {
                Position to(x + offsetX[i], y + offsetY[i]);

                if (!board.isInsideBoard(to))
                    continue;

                Piece targetPiece = board.getPiece(to);

                if (!targetPiece.isEmpty() &&
                    targetPiece.getColor() == sideToMove)
                    continue;

                moves.emplace_back(from, to);
            }
        }
    }
}