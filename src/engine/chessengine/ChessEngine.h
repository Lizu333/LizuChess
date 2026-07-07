#pragma once

#include <vector>

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"
#include "../position/Position.h"
#include "../pieces/Piece.h"
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

    bool isCurrentSideInCheck() const;

    bool hasLegalMoves() const;
    bool isGameOver() const;

    bool isCheckmate() const;
    bool isStalemate() const;

    void updateCastlingRights(const Move& move);

private:
    Board board;
    GameState gameState;

    MoveGenerator moveGenerator;
    MoveValidator moveValidator;
};