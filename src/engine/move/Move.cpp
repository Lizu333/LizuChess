#include "Move.h"

Move::Move()
    : from(),
    to(),
    type(MoveType::Normal),
    promotionPiece(PieceType::None)
{
}

Move::Move(
    const Position& from,
    const Position& to
)
    : from(from),
    to(to),
    type(MoveType::Normal),
    promotionPiece(PieceType::None)
{
}

Move::Move(
    const Position& from,
    const Position& to,
    MoveType type
)
    : from(from),
    to(to),
    type(type),
    promotionPiece(PieceType::None)
{
}

Move::Move(
    const Position& from,
    const Position& to,
    MoveType type,
    PieceType promotionPiece
)
    : from(from),
    to(to),
    type(type),
    promotionPiece(promotionPiece)
{
}

const Position& Move::getFrom() const
{
    return from;
}

const Position& Move::getTo() const
{
    return to;
}

MoveType Move::getType() const
{
    return type;
}

PieceType Move::getPromotionPiece() const
{
    return promotionPiece;
}

void Move::setFrom(const Position& from)
{
    this->from = from;
}

void Move::setTo(const Position& to)
{
    this->to = to;
}

void Move::setType(MoveType type)
{
    this->type = type;
}

void Move::setPromotionPiece(PieceType promotionPiece)
{
    this->promotionPiece = promotionPiece;
}