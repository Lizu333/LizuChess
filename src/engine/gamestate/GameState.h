#pragma once

#include "../pieces/Piece.h"
#include "../position/Position.h"

class GameState
{
public:
    GameState();

    PieceColor getSideToMove() const;
    void setSideToMove(PieceColor color);
    void switchSideToMove();

    bool canWhiteCastleKingSide() const;
    bool canWhiteCastleQueenSide() const;
    bool canBlackCastleKingSide() const;
    bool canBlackCastleQueenSide() const;

    void setWhiteCastleKingSide(bool value);
    void setWhiteCastleQueenSide(bool value);
    void setBlackCastleKingSide(bool value);
    void setBlackCastleQueenSide(bool value);

    bool hasEnPassantSquare() const;
    Position getEnPassantSquare() const;
    void setEnPassantSquare(const Position& position);
    void clearEnPassantSquare();

    int getHalfMoveClock() const;
    void setHalfMoveClock(int value);

    int getFullMoveNumber() const;
    void setFullMoveNumber(int value);

private:
    PieceColor sideToMove;

    bool whiteCastleKingSide;
    bool whiteCastleQueenSide;
    bool blackCastleKingSide;
    bool blackCastleQueenSide;

    bool enPassantAvailable;
    Position enPassantSquare;

    int halfMoveClock;
    int fullMoveNumber;
};