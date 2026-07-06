#include "MoveGenerator.h"

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