#pragma once

#include <vector>

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"
#include "../movegenerator/MoveGenerator.h"
#include "../movevalidator/MoveValidator.h"

class ChessEngine
{
public:
    ChessEngine();

    Board& getBoard();
    const Board& getBoard() const;

    GameState& getGameState();
    const GameState& getGameState() const;

    void resetGame();

    std::vector<Move> generateLegalMoves() const;
    std::vector<Move> getMovesForPiece(const Position& position) const;

    bool makeMove(const Move& move);

private:
    Board board;
    GameState gameState;
    MoveGenerator moveGenerator;
    MoveValidator moveValidator;
};