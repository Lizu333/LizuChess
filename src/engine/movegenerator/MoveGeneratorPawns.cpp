#include "MoveGenerator.h"

void MoveGenerator::generatePawnMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    generatePawnPushes(board, gameState, moves);
    generatePawnDoublePushes(board, gameState, moves);
    generatePawnCaptures(board, gameState, moves);
    generateEnPassantMoves(board, gameState, moves);
    generatePromotionMoves(board, gameState, moves);
}

void MoveGenerator::generatePawnPushes(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    const PieceColor sideToMove = gameState.getSideToMove();

    const int direction =
        (sideToMove == PieceColor::White) ? -1 : 1;

    const int promotionRow =
        (sideToMove == PieceColor::White) ? 0 : 7;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Position from(x, y);
            const Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Pawn)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            const Position to(x, y + direction);

            if (!board.isInsideBoard(to))
                continue;

            if (!board.isSquareEmpty(to))
                continue;

            //Az utolsó sorra érkező lépéseket a generatePromotionMoves() kezeli
            if (to.getY() == promotionRow)
                continue;

            moves.emplace_back(from, to);
        }
    }
}

void MoveGenerator::generatePawnDoublePushes(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    const PieceColor sideToMove = gameState.getSideToMove();

    const int direction =
        (sideToMove == PieceColor::White) ? -1 : 1;

    const int startRow =
        (sideToMove == PieceColor::White) ? 6 : 1;

    for (int x = 0; x < 8; x++)
    {
        const Position from(x, startRow);
        const Piece piece = board.getPiece(from);

        if (piece.isEmpty())
            continue;

        if (piece.getType() != PieceType::Pawn)
            continue;

        if (piece.getColor() != sideToMove)
            continue;

        const Position oneStep(
            x,
            startRow + direction
        );

        const Position twoSteps(
            x,
            startRow + 2 * direction
        );

        if (!board.isInsideBoard(oneStep))
            continue;

        if (!board.isInsideBoard(twoSteps))
            continue;

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
    std::vector<Move>& moves
) const
{
    const PieceColor sideToMove = gameState.getSideToMove();

    const int direction =
        (sideToMove == PieceColor::White) ? -1 : 1;

    const int promotionRow =
        (sideToMove == PieceColor::White) ? 0 : 7;

    constexpr int captureOffsets[2] = { -1, 1 };

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Position from(x, y);
            const Piece piece = board.getPiece(from);

            if (piece.isEmpty())
                continue;

            if (piece.getType() != PieceType::Pawn)
                continue;

            if (piece.getColor() != sideToMove)
                continue;

            for (const int dx : captureOffsets)
            {
                const Position targetPosition(
                    x + dx,
                    y + direction
                );

                if (!board.isInsideBoard(targetPosition))
                    continue;

                const Piece targetPiece =
                    board.getPiece(targetPosition);

                if (targetPiece.isEmpty())
                    continue;

                if (targetPiece.getColor() == sideToMove)
                    continue;

                // A promóciós ütéseket külön kezeljük.
                if (targetPosition.getY() == promotionRow)
                    continue;

                moves.emplace_back(
                    from,
                    targetPosition,
                    MoveType::Capture
                );
            }
        }
    }
}

void MoveGenerator::generateEnPassantMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    if (!gameState.hasEnPassantSquare())
        return;

    const PieceColor sideToMove =
        gameState.getSideToMove();

    const Position enPassantSquare =
        gameState.getEnPassantSquare();

    const int pawnRow =
        (sideToMove == PieceColor::White) ? 3 : 4;

    constexpr int offsets[2] = { -1, 1 };

    for (const int dx : offsets)
    {
        const Position from(
            enPassantSquare.getX() + dx,
            pawnRow
        );

        if (!board.isInsideBoard(from))
            continue;

        const Piece piece = board.getPiece(from);

        if (piece.isEmpty())
            continue;

        if (piece.getType() != PieceType::Pawn)
            continue;

        if (piece.getColor() != sideToMove)
            continue;

        const Position capturedPawnPosition(
            enPassantSquare.getX(),
            pawnRow
        );

        if (!board.isInsideBoard(capturedPawnPosition))
            continue;

        const Piece capturedPawn =
            board.getPiece(capturedPawnPosition);

        if (capturedPawn.isEmpty())
            continue;

        if (capturedPawn.getType() != PieceType::Pawn)
            continue;

        if (capturedPawn.getColor() == sideToMove)
            continue;

        moves.emplace_back(
            from,
            enPassantSquare,
            MoveType::EnPassant
        );
    }
}

void MoveGenerator::generatePromotionMoves(
    const Board& board,
    const GameState& gameState,
    std::vector<Move>& moves
) const
{
    const PieceColor sideToMove =
        gameState.getSideToMove();

    const int direction =
        (sideToMove == PieceColor::White) ? -1 : 1;

    const int pawnRow =
        (sideToMove == PieceColor::White) ? 1 : 6;

    const int promotionRow =
        (sideToMove == PieceColor::White) ? 0 : 7;

    constexpr PieceType promotionPieces[4] =
    {
        PieceType::Queen,
        PieceType::Rook,
        PieceType::Bishop,
        PieceType::Knight
    };

    for (int x = 0; x < 8; x++)
    {
        const Position from(x, pawnRow);
        const Piece pawn = board.getPiece(from);

        if (pawn.isEmpty())
            continue;

        if (pawn.getType() != PieceType::Pawn)
            continue;

        if (pawn.getColor() != sideToMove)
            continue;

        const Position forward(x, promotionRow);

        if (board.isSquareEmpty(forward))
        {
            for (const PieceType promotionPiece : promotionPieces)
            {
                moves.emplace_back(
                    from,
                    forward,
                    MoveType::Promotion,
                    promotionPiece
                );
            }
        }

        constexpr int captureOffsets[2] = { -1, 1 };

        for (const int dx : captureOffsets)
        {
            const Position target(
                x + dx,
                pawnRow + direction
            );

            if (!board.isInsideBoard(target))
                continue;

            const Piece targetPiece =
                board.getPiece(target);

            if (targetPiece.isEmpty())
                continue;

            if (targetPiece.getColor() == sideToMove)
                continue;

            for (const PieceType promotionPiece : promotionPieces)
            {
                moves.emplace_back(
                    from,
                    target,
                    MoveType::Promotion,
                    promotionPiece
                );
            }
        }
    }
}