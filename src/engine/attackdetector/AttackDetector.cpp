#include "AttackDetector.h"

AttackDetector::AttackDetector()
{
}

bool AttackDetector::isSquareAttacked(
    const Board& board,
    const Position& square,
    PieceColor attackerColor
) const
{
    if (isAttackedByPawn(board, square, attackerColor))
        return true;

    if (isAttackedByKnight(board, square, attackerColor))
        return true;

    // Bishop / Queen diagonals
    if (isAttackedBySlidingPiece(board, square, attackerColor, 1, 1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, 1, -1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, -1, 1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, -1, -1, PieceType::Bishop, PieceType::Queen))
        return true;

    // Rook / Queen straight lines
    if (isAttackedBySlidingPiece(board, square, attackerColor, 1, 0, PieceType::Rook, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, -1, 0, PieceType::Rook, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, 0, 1, PieceType::Rook, PieceType::Queen))
        return true;

    if (isAttackedBySlidingPiece(board, square, attackerColor, 0, -1, PieceType::Rook, PieceType::Queen))
        return true;

    if (isAttackedByKing(board, square, attackerColor))
        return true;

    return false;
}

bool AttackDetector::isAttackedByPawn(
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

bool AttackDetector::isAttackedByKnight(
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

bool AttackDetector::isAttackedBySlidingPiece(
    const Board& board,
    const Position& square,
    PieceColor attackerColor,
    int dx,
    int dy,
    PieceType validType1,
    PieceType validType2
) const
{
    int x = square.getX() + dx;
    int y = square.getY() + dy;

    while (true)
    {
        Position current(x, y);

        if (!board.isInsideBoard(current))
            break;

        Piece piece = board.getPiece(current);

        if (piece.isEmpty())
        {
            x += dx;
            y += dy;
            continue;
        }

        if (piece.getColor() != attackerColor)
            return false;

        return piece.getType() == validType1 ||
            piece.getType() == validType2;
    }

    return false;
}

bool AttackDetector::isAttackedByKing(
    const Board& board,
    const Position& square,
    PieceColor attackerColor
) const
{
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;

            Position attackerPosition(
                square.getX() + dx,
                square.getY() + dy
            );

            if (!board.isInsideBoard(attackerPosition))
                continue;

            Piece piece = board.getPiece(attackerPosition);

            if (piece.isEmpty())
                continue;

            if (piece.getColor() != attackerColor)
                continue;

            if (piece.getType() != PieceType::King)
                continue;

            return true;
        }
    }

    return false;
}