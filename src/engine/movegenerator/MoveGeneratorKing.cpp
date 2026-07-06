#include "MoveGenerator.h"


void MoveGenerator::generateKingMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::King)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    Position to(x + dx, y + dy);

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
}