#include "Move.h"

Move::Move()
    : from(),
    to()
{
}

Move::Move(const Position& from, const Position& to)
    : from(from),
    to(to)
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

void Move::setFrom(const Position& from)
{
    this->from = from;
}

void Move::setTo(const Position& to)
{
    this->to = to;
}