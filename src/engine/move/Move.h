#pragma once

#include "../position/Position.h"
#include "../pieces/Piece.h"
#include "MoveType.h"

class Move
{
public:
    Move();

    Move(
        const Position& from,
        const Position& to
    );

    Move(
        const Position& from,
        const Position& to,
        MoveType type
    );

    Move(
        const Position& from,
        const Position& to,
        MoveType type,
        PieceType promotionPiece
    );

    const Position& getFrom() const;
    const Position& getTo() const;

    MoveType getType() const;
    PieceType getPromotionPiece() const;

    void setFrom(const Position& from);
    void setTo(const Position& to);

    void setType(MoveType type);
    void setPromotionPiece(PieceType promotionPiece);

private:
    Position from;
    Position to;

    MoveType type;
    PieceType promotionPiece;
};