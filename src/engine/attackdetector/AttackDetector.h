#pragma once

#include "../board/Board.h"
#include "../position/Position.h"
#include "../pieces/Piece.h"

class AttackDetector
{
public:
    AttackDetector();

    bool isSquareAttacked(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;

private:
    bool isAttackedByPawn(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;

    bool isAttackedByKnight(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;

    bool isAttackedBySlidingPiece(
        const Board& board,
        const Position& square,
        PieceColor attackerColor,
        int dx,
        int dy,
        PieceType validType1,
        PieceType validType2
    ) const;

    bool isAttackedByKing(
        const Board& board,
        const Position& square,
        PieceColor attackerColor
    ) const;
};