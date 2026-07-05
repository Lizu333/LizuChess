#pragma once

#include <vector>

#include "../move/Move.h"
#include "../board/Board.h"
#include "../gamestate/GameState.h"

class MoveGenerator
{
public:
    MoveGenerator();

    std::vector<Move> generateMoves(
        const Board& board,
        const GameState& gameState);

private:
    void generatePawnMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);

    void generateKnightMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);

    void generateBishopMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);

    void generateRookMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);

    void generateQueenMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);

    void generateKingMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves);
};