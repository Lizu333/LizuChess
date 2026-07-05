#include "Piece.h"

Piece::Piece()
    : type(PieceType::None),
    color(PieceColor::None)
{
}

Piece::Piece(PieceType type, PieceColor color)
    : type(type),
    color(color)
{
}

PieceType Piece::getType() const
{
    return type;
}

PieceColor Piece::getColor() const
{
    return color;
}

bool Piece::isEmpty() const
{
    return type == PieceType::None;
}