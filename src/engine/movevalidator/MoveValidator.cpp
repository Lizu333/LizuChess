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

    PieceColor attackerColor =
        (color == PieceColor::White)
        ? PieceColor::Black
        : PieceColor::White;

    if (isSquareAttackedByKnight(board, kingPosition, attackerColor))
        return true;

    if (isSquareAttackedByPawn(board, kingPosition, attackerColor))
        return true;

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

bool MoveValidator::isSquareAttackedByKnight(
    const Board& board,
    const Position& square,
    PieceColor attackerColor
) const
{
    const int offsetX[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int offsetY[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };

    for (int i = 0; i < 8; i++)
    {
        Position attackerPosition(
            square.getX() + offsetX[i],
            square.getY() + offsetY[i]
        );

        if (!board.isInsideBoard(attackerPosition))
            continue;

        Piece piece = board.getPiece(attackerPosition);

        if (piece.isEmpty())
            continue;

        if (piece.getColor() != attackerColor)
            continue;

        if (piece.getType() != PieceType::Knight)
            continue;

        return true;
    }

    return false;
}


bool MoveValidator::isSquareAttackedByPawn(
    const Board& board,
    const Position& square,
    PieceColor attackerColor
) const
{
    int direction =
        (attackerColor == PieceColor::White) ? 1 : -1;

    const int offsets[2] = { -1, 1 };

    for (int dx : offsets)
    {
        Position attackerPosition(
            square.getX() + dx,
            square.getY() + direction
        );

        if (!board.isInsideBoard(attackerPosition))
            continue;

        Piece piece = board.getPiece(attackerPosition);

        if (piece.isEmpty())
            continue;

        if (piece.getColor() != attackerColor)
            continue;

        if (piece.getType() != PieceType::Pawn)
            continue;

        return true;
    }

    return false;
}