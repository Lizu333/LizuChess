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

void MoveGenerator::generateCastlingMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    if (sideToMove == PieceColor::White)
    {
        Position kingFrom(4, 7);

        if (gameState.canWhiteCastleKingSide() &&
            board.isSquareEmpty(Position(5, 7)) &&
            board.isSquareEmpty(Position(6, 7)))
        {
            moves.emplace_back(kingFrom, Position(6, 7));
        }

        if (gameState.canWhiteCastleQueenSide() &&
            board.isSquareEmpty(Position(1, 7)) &&
            board.isSquareEmpty(Position(2, 7)) &&
            board.isSquareEmpty(Position(3, 7)))
        {
            moves.emplace_back(kingFrom, Position(2, 7));
        }
    }

    if (sideToMove == PieceColor::Black)
    {
        Position kingFrom(4, 0);

        if (gameState.canBlackCastleKingSide() &&
            board.isSquareEmpty(Position(5, 0)) &&
            board.isSquareEmpty(Position(6, 0)))
        {
            moves.emplace_back(kingFrom, Position(6, 0));
        }

        if (gameState.canBlackCastleQueenSide() &&
            board.isSquareEmpty(Position(1, 0)) &&
            board.isSquareEmpty(Position(2, 0)) &&
            board.isSquareEmpty(Position(3, 0)))
        {
            moves.emplace_back(kingFrom, Position(2, 0));
        }
    }
}