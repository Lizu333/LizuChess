#include "MoveGenerator.h"

void MoveGenerator::generateRookMoves(
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

            if (piece.getType() != PieceType::Rook)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            addSlidingMoves(board, gameState, moves, from, 1, 0);
            addSlidingMoves(board, gameState, moves, from, -1, 0);
            addSlidingMoves(board, gameState, moves, from, 0, 1);
            addSlidingMoves(board, gameState, moves, from, 0, -1);
        }
    }
}