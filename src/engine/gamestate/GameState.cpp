#include "GameState.h"

GameState::GameState()
    : sideToMove(PieceColor::White),
    whiteKingSideCastle(true),
    whiteQueenSideCastle(true),
    blackKingSideCastle(true),
    blackQueenSideCastle(true),
    enPassantAvailable(false),
    enPassantSquare(-1, -1),
    halfMoveClock(0),
    fullMoveNumber(1)
{
}

PieceColor GameState::getSideToMove() const
{
    return sideToMove;
}

void GameState::setSideToMove(PieceColor color)
{
    sideToMove = color;
}

bool GameState::canWhiteCastleKingSide() const
{
    return whiteKingSideCastle;
}

bool GameState::canWhiteCastleQueenSide() const
{
    return whiteQueenSideCastle;
}

bool GameState::canBlackCastleKingSide() const
{
    return blackKingSideCastle;
}

bool GameState::canBlackCastleQueenSide() const
{
    return blackQueenSideCastle;
}

void GameState::setWhiteCastleKingSide(bool value)
{
    whiteKingSideCastle = value;
}

void GameState::setWhiteCastleQueenSide(bool value)
{
    whiteQueenSideCastle = value;
}

void GameState::setBlackCastleKingSide(bool value)
{
    blackKingSideCastle = value;
}

void GameState::setBlackCastleQueenSide(bool value)
{
    blackQueenSideCastle = value;
}

bool GameState::hasEnPassant() const
{
    return enPassantAvailable;
}

Position GameState::getEnPassantSquare() const
{
    return enPassantSquare;
}

void GameState::setEnPassantSquare(const Position& position)
{
    enPassantAvailable = true;
    enPassantSquare = position;
}

void GameState::clearEnPassant()
{
    enPassantAvailable = false;
}

int GameState::getHalfMoveClock() const
{
    return halfMoveClock;
}

void GameState::setHalfMoveClock(int value)
{
    halfMoveClock = value;
}

int GameState::getFullMoveNumber() const
{
    return fullMoveNumber;
}

void GameState::setFullMoveNumber(int value)
{
    fullMoveNumber = value;
}