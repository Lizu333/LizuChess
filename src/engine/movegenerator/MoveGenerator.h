#pragma once

#include <vector>

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"
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
    // Pawn moves
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

    void generateEnPassantMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    void generatePromotionMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    // Knight
    void generateKnightMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    // Bishop
    void generateBishopMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    // Rook
    void generateRookMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    // Queen
    void generateQueenMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves
    ) const;

    // King
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

    // Shared helper for bishop, rook and queen
    void addSlidingMoves(
        const Board& board,
        const GameState& gameState,
        std::vector<Move>& moves,
        const Position& from,
        int dx,
        int dy
    ) const;
};