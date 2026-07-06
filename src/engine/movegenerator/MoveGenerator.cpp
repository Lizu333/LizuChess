#include "MoveGenerator.h"

MoveGenerator::MoveGenerator()
{
}

std::vector<Move> MoveGenerator::generateMoves(
    const Board& board,
    const GameState& gameState) const
{
    std::vector<Move> moves;

    generatePawnMoves(board, gameState, moves);
    generateKnightMoves(board, gameState, moves);
    generateBishopMoves(board, gameState, moves);
    generateRookMoves(board, gameState, moves);
    generateQueenMoves(board, gameState, moves);
    generateKingMoves(board, gameState, moves);

    return moves;
}








