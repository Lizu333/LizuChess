#include "MoveGenerator.h"

void MoveGenerator::generateQueenMoves(
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

            if (piece.getType() != PieceType::Queen)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            // Rook directions
            addSlidingMoves(board, gameState, moves, from, 1, 0);
            addSlidingMoves(board, gameState, moves, from, -1, 0);
            addSlidingMoves(board, gameState, moves, from, 0, 1);
            addSlidingMoves(board, gameState, moves, from, 0, -1);

            // Bishop directions
            addSlidingMoves(board, gameState, moves, from, 1, 1);
            addSlidingMoves(board, gameState, moves, from, 1, -1);
            addSlidingMoves(board, gameState, moves, from, -1, 1);
            addSlidingMoves(board, gameState, moves, from, -1, -1);
        }
    }
}