#include "MoveHistory.h"

void MoveHistory::clear()
{
    moves.clear();
}

void MoveHistory::addMove(const Move& move)
{
    moves.push_back(move);
}

const std::vector<Move>& MoveHistory::getMoves() const
{
    return moves;
}