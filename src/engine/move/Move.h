#pragma once

#include "../position/Position.h"

class Move
{
public:
    Move();
    Move(const Position& from, const Position& to);

    const Position& getFrom() const;
    const Position& getTo() const;

    void setFrom(const Position& from);
    void setTo(const Position& to);

private:
    Position from;
    Position to;
};