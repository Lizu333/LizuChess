#include "MoveValidator.h"

MoveValidator::MoveValidator()
{
}

bool MoveValidator::isMoveLegal(
    const Board& board,
    const GameState& gameState,
    const Move& move
) const
{
    Piece movingPiece = board.getPiece(move.getFrom());

    if (movingPiece.isEmpty())
        return false;

    if (movingPiece.getColor() != gameState.getSideToMove())
        return false;

    return !leavesKingInCheck(board, gameState, move);
}

bool MoveValidator::leavesKingInCheck(
    const Board& board,
    const GameState& gameState,
    const Move& move
) const
{
    Board temporaryBoard = board;

    temporaryBoard.makeMove(move);

    return isKingInCheck(
        temporaryBoard,
        gameState.getSideToMove()
    );
}

bool MoveValidator::isKingInCheck(
    const Board& board,
    PieceColor color
) const
{
    Position kingPosition = findKing(board, color);

    if (kingPosition.getX() == -1)
        return false;

    //ide ellenfel tamadasanak vizsgalatai kesobb

    return false;
}

Position MoveValidator::findKing(
    const Board& board,
    PieceColor color
) const
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position position(x, y);

            Piece piece = board.getPiece(position);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::King)
                continue;

            if (piece.getColor() != color)
                continue;

            return position;
        }
    }

    return Position(-1, -1);
}