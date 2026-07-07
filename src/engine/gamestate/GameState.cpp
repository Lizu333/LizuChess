#include "GameState.h"

GameState::GameState()
    : sideToMove(PieceColor::White),
    whiteCastleKingSide(true),
    whiteCastleQueenSide(true),
    blackCastleKingSide(true),
    blackCastleQueenSide(true),
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

void GameState::switchSideToMove()
{
    sideToMove =
        (sideToMove == PieceColor::White)
        ? PieceColor::Black
        : PieceColor::White;
}

bool GameState::canWhiteCastleKingSide() const
{
    return whiteCastleKingSide;
}

bool GameState::canWhiteCastleQueenSide() const
{
    return whiteCastleQueenSide;
}

bool GameState::canBlackCastleKingSide() const
{
    return blackCastleKingSide;
}

bool GameState::canBlackCastleQueenSide() const
{
    return blackCastleQueenSide;
}

void GameState::setWhiteCastleKingSide(bool value)
{
    whiteCastleKingSide = value;
}

void GameState::setWhiteCastleQueenSide(bool value)
{
    whiteCastleQueenSide = value;
}

void GameState::setBlackCastleKingSide(bool value)
{
    blackCastleKingSide = value;
}

void GameState::setBlackCastleQueenSide(bool value)
{
    blackCastleQueenSide = value;
}

bool GameState::hasEnPassantSquare() const
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

void GameState::clearEnPassantSquare()
{
    enPassantAvailable = false;
    enPassantSquare = Position(-1, -1);
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