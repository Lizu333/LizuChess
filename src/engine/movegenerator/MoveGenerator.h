#pragma once

#include <vector>

#include "../move/Move.h"
#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../position/Position.h"

class MoveGenerator
{
public:
    MoveGenerator();

    std::vector<Move> generateMoves(
        const Board& board,
        const GameState& gameState
    ) const;

private:
    void generatePawnMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generatePawnPushes(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generatePawnDoublePushes(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generatePawnCaptures(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateKnightMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateBishopMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateRookMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateQueenMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateKingMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generateCastlingMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void addSlidingMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves,
        const Position& from,
        int dx,
        int dy
    ) const;
};