#pragma once

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"
#include "../pieces/Piece.h"
#include "../position/Position.h"
#include "../attackdetector/AttackDetector.h"

class MoveValidator
{
public:
    MoveValidator();

    bool isMoveLegal(
        const Board& board,
        const GameState& gameState,
        const Move& move
    ) const;

    //isKingInCheck privatbol public a 3. verzio kiadasa utan
    bool isKingInCheck(
        const Board& board,
        PieceColor color
    ) const;

private:
    bool leavesKingInCheck(
        const Board& board,
        const GameState& gameState,
        const Move& move
    ) const;

    Position findKing(
        const Board& board,
        PieceColor color
    ) const;

private:
    AttackDetector attackDetector;
};