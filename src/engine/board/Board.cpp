#include "Board.h"

Board::Board()
{
    reset();
}

void Board::reset()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            squares[y][x] = Piece();
        }
    }
}

bool Board::isInsideBoard(const Position& position) const
{
    return position.getX() >= 0 &&
        position.getX() < 8 &&
        position.getY() >= 0 &&
        position.getY() < 8;
}

Piece Board::getPiece(const Position& position) const
{
    return squares[position.getY()][position.getX()];
}

void Board::setPiece(const Position& position, const Piece& piece)
{
    squares[position.getY()][position.getX()] = piece;
}

bool Board::isSquareEmpty(const Position& position) const
{
    return getPiece(position).isEmpty();
}

void Board::makeMove(const Move& move)
{
    Piece piece = getPiece(move.getFrom());

    setPiece(move.getTo(), piece);

    setPiece(move.getFrom(), Piece());
}