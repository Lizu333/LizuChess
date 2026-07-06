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

    //bishop/queen
    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, 1, 1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, 1, -1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, -1, 1, PieceType::Bishop, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, -1, -1, PieceType::Bishop, PieceType::Queen))
        return true;

    //rook/queen
    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, 1, 0, PieceType::Rook, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, -1, 0, PieceType::Rook, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, 0, 1, PieceType::Rook, PieceType::Queen))
        return true;

    if (isSquareAttackedBySlidingPiece(board, kingPosition, attackerColor, 0, -1, PieceType::Rook, PieceType::Queen))
        return true;

    if (isSquareAttackedByKing(board, kingPosition, attackerColor))
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

bool MoveValidator::isSquareAttackedBySlidingPiece(
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

bool MoveValidator::isSquareAttackedByKing(
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