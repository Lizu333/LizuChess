#pragma once

#include "../pieces/Piece.h"
#include "../position/Position.h"
#include "../move/Move.h"

class Board
{
public:
    Board();

    void reset();

    bool isInsideBoard(const Position& position) const;

    Piece getPiece(const Position& position) const;
    void setPiece(const Position& position, const Piece& piece);

    bool isSquareEmpty(const Position& position) const;

    void makeMove(const Move& move);

private:
    Piece squares[8][8];
};