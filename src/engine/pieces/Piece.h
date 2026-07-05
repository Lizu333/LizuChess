#pragma once

enum class PieceType
{
    None,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class PieceColor
{
    None,
    White,
    Black
};

class Piece
{
public:
    Piece();

    Piece(PieceType type, PieceColor color);

    PieceType getType() const;
    PieceColor getColor() const;

    bool isEmpty() const;

private:
    PieceType type;
    PieceColor color;
};