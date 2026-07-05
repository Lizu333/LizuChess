#pragma once

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../movegenerator/MoveGenerator.h"
#include "../movevalidator/MoveValidator.h"

class ChessEngine
{
public:
    ChessEngine();

    Board& getBoard();
    GameState& getGameState();

    void resetGame();

private:
    Board board;
    GameState gameState;
    MoveGenerator moveGenerator;
    MoveValidator moveValidator;
};