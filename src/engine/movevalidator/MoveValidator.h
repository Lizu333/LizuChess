#pragma once

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"

class MoveValidator
{
public:
    MoveValidator();

    bool isMoveLegal(
        const Board& board,
        const GameState& gameState,
        const Move& move
    ) const;
};