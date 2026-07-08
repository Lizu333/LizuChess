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

    if (isCastlingMove(board, move))
    {
        if (!isCastlingLegal(board, gameState, move))
            return false;
    }

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

    return attackDetector.isSquareAttacked(
        board,
        kingPosition,
        attackerColor
    );
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

bool MoveValidator::isCastlingMove(
    const Board& board,
    const Move& move
) const
{
    Piece piece = board.getPiece(move.getFrom());

    if (piece.isEmpty())
        return false;

    if (piece.getType() != PieceType::King)
        return false;

    int dx = move.getTo().getX() - move.getFrom().getX();

    return dx == 2 || dx == -2;
}

bool MoveValidator::isCastlingLegal(
    const Board& board,
    const GameState& gameState,
    const Move& move
) const
{
    PieceColor kingColor = gameState.getSideToMove();

    Position from = move.getFrom();
    Position to = move.getTo();

    PieceColor enemyColor =
        (kingColor == PieceColor::White)
        ? PieceColor::Black
        : PieceColor::White;

    if (attackDetector.isSquareAttacked(board, from, enemyColor))
        return false;

    int direction = (to.getX() > from.getX()) ? 1 : -1;

    Position passingSquare(from.getX() + direction, from.getY());

    if (attackDetector.isSquareAttacked(board, passingSquare, enemyColor))
        return false;

    if (attackDetector.isSquareAttacked(board, to, enemyColor))
        return false;

    return true;
}