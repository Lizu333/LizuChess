#include "MoveGenerator.h"

MoveGenerator::MoveGenerator()
{
}

std::vector<Move> MoveGenerator::generateMoves(
    const Board& board,
    const GameState& gameState)
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

void MoveGenerator::generatePawnMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}

void MoveGenerator::generateKnightMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}

void MoveGenerator::generateBishopMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}

void MoveGenerator::generateRookMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}

void MoveGenerator::generateQueenMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}

void MoveGenerator::generateKingMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&)
{
}