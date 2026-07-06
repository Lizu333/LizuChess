#pragma once

#include "../board/Board.h"
#include "../gamestate/GameState.h"
#include "../move/Move.h"
#include "../pieces/Piece.h"

class MoveValidator
{
public:
    MoveValidator();

    bool isMoveLegal(
        const Board& board,
        const GameState& gameState,
        const Move& move
    ) const;

private:
    bool leavesKingInCheck(
        const Board& board,
        const GameState& gameState,
        const Move& move
    ) const;

    bool isKingInCheck(
        const Board& board,
        PieceColor color
    ) const;

    Position findKing(
        const Board& board,
        PieceColor color
    ) const;

    bool isSquareAttackedByKnight(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;

    bool isSquareAttackedByPawn(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;

    bool isSquareAttackedBySlidingPiece(
        const Board& board,
        const Position& square,
        PieceColor attackerColor,
        int dx,
        int dy,
        PieceType validType1,
        PieceType validType2
    ) const;

    bool isSquareAttackedByKing(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;
};