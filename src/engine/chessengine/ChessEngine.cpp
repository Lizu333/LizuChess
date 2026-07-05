#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
    resetGame();
}

Board& ChessEngine::getBoard()
{
    return board;
}

GameState& ChessEngine::getGameState()
{
    return gameState;
}

void ChessEngine::resetGame()
{
    board.setupStartingPosition();
}