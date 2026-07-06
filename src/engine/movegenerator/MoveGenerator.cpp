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

void MoveGenerator::generatePawnMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    generatePawnPushes(board, gameState, moves);
    generatePawnDoublePushes(board, gameState, moves);
    generatePawnCaptures(board, gameState, moves);
}

void MoveGenerator::generatePawnPushes(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();
    int direction = (sideToMove == PieceColor::White) ? -1 : 1;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Pawn)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            Position to(x, y + direction);

            if (!board.isInsideBoard(to))
                continue;

            if (!board.isSquareEmpty(to))
                continue;

            moves.emplace_back(from, to);
        }
    }
}

void MoveGenerator::generatePawnDoublePushes(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    int direction = (sideToMove == PieceColor::White) ? -1 : 1;
    int startRow = (sideToMove == PieceColor::White) ? 6 : 1;

    for (int x = 0; x < 8; x++)
    {
        Position from(x, startRow);
        Piece piece = board.getPiece(from);

        if (piece.isEmpty())
            continue;

        if (piece.getType() != PieceType::Pawn)
            continue;

        if (piece.getColor() != sideToMove)
            continue;

        Position oneStep(x, startRow + direction);
        Position twoSteps(x, startRow + 2 * direction);

        if (!board.isSquareEmpty(oneStep))
            continue;

        if (!board.isSquareEmpty(twoSteps))
            continue;

        moves.emplace_back(from, twoSteps);
    }
}

void MoveGenerator::generatePawnCaptures(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();
    int direction = (sideToMove == PieceColor::White) ? -1 : 1;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Pawn)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            for (int dx : { -1, 1 })
            {
                Position targetPosition(x + dx, y + direction);

                if (!board.isInsideBoard(targetPosition))
                    continue;

                Piece targetPiece = board.getPiece(targetPosition);

                if (targetPiece.isEmpty())
                    continue;

                if (targetPiece.getColor() == sideToMove)
                    continue;

                moves.emplace_back(from, targetPosition);
            }
        }
    }
}

void MoveGenerator::generateKnightMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    const int offsetX[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int offsetY[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Knight)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            for (int i = 0; i < 8; i++)
            {
                Position to(x + offsetX[i], y + offsetY[i]);

                if (!board.isInsideBoard(to))
                    continue;

                Piece targetPiece = board.getPiece(to);

                if (!targetPiece.isEmpty() &&
                    targetPiece.getColor() == sideToMove)
                    continue;

                moves.emplace_back(from, to);
            }
        }
    }
}

void MoveGenerator::generateBishopMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Bishop)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            addSlidingMoves(board, gameState, moves, from, 1, 1);
            addSlidingMoves(board, gameState, moves, from, 1, -1);
            addSlidingMoves(board, gameState, moves, from, -1, 1);
            addSlidingMoves(board, gameState, moves, from, -1, -1);
        }
    }
}

void MoveGenerator::generateRookMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position from(x, y);
            Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Rook)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            addSlidingMoves(board, gameState, moves, from, 1, 0);
            addSlidingMoves(board, gameState, moves, from, -1, 0);
            addSlidingMoves(board, gameState, moves, from, 0, 1);
            addSlidingMoves(board, gameState, moves, from, 0, -1);
        }
    }
}

void MoveGenerator::generateQueenMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&) const
{
}

void MoveGenerator::generateKingMoves(
    const Board&,
    const GameState&,
    std::vector<Move>&) const
{
}

void MoveGenerator::addSlidingMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves,
    const Position& from,
    int dx,
    int dy) const
{
    PieceColor sideToMove = gameState.getSideToMove();

    int x = from.getX() + dx;
    int y = from.getY() + dy;

    while (true)
    {
        Position to(x, y);

        if (!board.isInsideBoard(to))
            break;

        Piece targetPiece = board.getPiece(to);

        if (targetPiece.isEmpty())
        {
            moves.emplace_back(from, to);
        }
        else
        {
            if (targetPiece.getColor() != sideToMove)
            {
                moves.emplace_back(from, to);
            }

            break;
        }

        x += dx;
        y += dy;
    }
}