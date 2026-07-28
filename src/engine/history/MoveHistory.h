#pragma once

#include <vector>

#include "../move/Move.h"

class MoveHistory
{
public:
    void clear();

    void addMove(const Move& move);

    const std::vector<Move>& getMoves() const;

private:
    std::vector<Move> moves;
};