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

bool ChessEngine::makeMove(const Move& move)
{
    std::vector<Move> legalMoves = generateLegalMoves();

    for (const Move& legalMove : legalMoves)
    {
        if (legalMove.getFrom() == move.getFrom() &&
            legalMove.getTo() == move.getTo())
        {
            board.makeMove(move);

            PieceColor current = gameState.getSideToMove();

            gameState.setSideToMove(
                current == PieceColor::White
                ? PieceColor::Black
                : PieceColor::White
            );

            return true;
        }
    }

    return false;
}

std::vector<Move> ChessEngine::getMovesForPiece(
    const Position& position) const
{
    std::vector<Move> allMoves = generateLegalMoves();
    std::vector<Move> pieceMoves;

    for (const Move& move : allMoves)
    {
        if (move.getFrom() == position)
        {
            pieceMoves.push_back(move);
        }
    }

    return pieceMoves;
}