#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
    resetGame();
}

Board& ChessEngine::getBoard()
{
    return board;
}

const Board& ChessEngine::getBoard() const
{
    return board;
}

GameState& ChessEngine::getGameState()
{
    return gameState;
}

const GameState& ChessEngine::getGameState() const
{
    return gameState;
}

void ChessEngine::resetGame()
{
    board.setupStartingPosition();
}

std::vector<Move> ChessEngine::generateLegalMoves() const
{
    std::vector<Move> pseudoLegalMoves =
        moveGenerator.generateMoves(board, gameState);

    std::vector<Move> legalMoves;

    for (const Move& move : pseudoLegalMoves)
    {
        if (moveValidator.isMoveLegal(board, gameState, move))
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}