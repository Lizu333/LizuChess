#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
    resetGame();
}

Board& ChessEngine::getBoard()
{
    return board;
}

const Board& ChessEngine::getBoard() const
{
    return board;
}

GameState& ChessEngine::getGameState()
{
    return gameState;
}

const GameState& ChessEngine::getGameState() const
{
    return gameState;
}

void ChessEngine::resetGame()
{
    board.setupStartingPosition();
    //feher kiraly sakkban teszteleshez: board.setupCheckTestPosition(); 
    //sancolas tesztallasahoz: board.setupCastlingTestPosition(); 
    //enpassant tesztallashoz: board.setupEnPassantTestPosition();
    //alap: board.setupStartingPosition();
    gameState = GameState();
}

std::vector<Move> ChessEngine::generateLegalMoves() const
{
    std::vector<Move> pseudoLegalMoves =
        moveGenerator.generateMoves(board, gameState);

    std::vector<Move> legalMoves;

    for (const Move& move : pseudoLegalMoves)
    {
        if (moveValidator.isMoveLegal(board, gameState, move))
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

bool ChessEngine::makeMove(const Move& move)
{
    std::vector<Move> legalMoves = generateLegalMoves();

    for (const Move& legalMove : legalMoves)
    {
        if (legalMove.getFrom() == move.getFrom() &&
            legalMove.getTo() == move.getTo())
        {

            updateCastlingRights(move);

            //ha gyalog 2t lep akkor az lesz az en passant mezo ami mogotte van
            Piece movingPiece = board.getPiece(move.getFrom());

            gameState.clearEnPassantSquare();

            if (movingPiece.getType() == PieceType::Pawn)
            {
                int deltaY = move.getTo().getY() - move.getFrom().getY();

                if (deltaY == 2 || deltaY == -2)
                {
                    int enPassantY =
                        (move.getFrom().getY() + move.getTo().getY()) / 2;

                    gameState.setEnPassantSquare(
                        Position(move.getFrom().getX(), enPassantY)
                    );
                }
            }

            board.makeMove(move);

            PieceColor current = gameState.getSideToMove();

            gameState.switchSideToMove();

            return true;
        }
    }

    return false;
}

std::vector<Move> ChessEngine::getMovesForPiece(
    const Position& position) const
{
    std::vector<Move> allMoves = generateLegalMoves();
    std::vector<Move> pieceMoves;

    for (const Move& move : allMoves)
    {
        if (move.getFrom() == position)
        {
            pieceMoves.push_back(move);
        }
    }

    return pieceMoves;
}

bool ChessEngine::isCurrentSideInCheck() const
{
    return moveValidator.isKingInCheck(
        board,
        gameState.getSideToMove()
    );
}


bool ChessEngine::hasLegalMoves() const
{
    return !generateLegalMoves().empty();
}

bool ChessEngine::isGameOver() const
{
    return !hasLegalMoves();
}

bool ChessEngine::isCheckmate() const
{
    return isCurrentSideInCheck() &&
        generateLegalMoves().empty();
}

bool ChessEngine::isStalemate() const
{
    return !isCurrentSideInCheck() &&
        generateLegalMoves().empty();
}

void ChessEngine::updateCastlingRights(const Move& move)
{
    Piece movingPiece = board.getPiece(move.getFrom());

    if (movingPiece.isEmpty())
        return;

    Position from = move.getFrom();

    //ha a feher kiraly lep, elvesziti mindket sancolasi jogat
    if (movingPiece.getType() == PieceType::King &&
        movingPiece.getColor() == PieceColor::White)
    {
        gameState.setWhiteCastleKingSide(false);
        gameState.setWhiteCastleQueenSide(false);
    }

    //ha a fekete kiraly lep, elvesziti mindket sancolasi jogat
    if (movingPiece.getType() == PieceType::King &&
        movingPiece.getColor() == PieceColor::Black)
    {
        gameState.setBlackCastleKingSide(false);
        gameState.setBlackCastleQueenSide(false);
    }

    //feher bastyak
    if (movingPiece.getType() == PieceType::Rook &&
        movingPiece.getColor() == PieceColor::White)
    {
        if (from == Position(0, 7))
            gameState.setWhiteCastleQueenSide(false);

        if (from == Position(7, 7))
            gameState.setWhiteCastleKingSide(false);
    }

    //fekete bastyak
    if (movingPiece.getType() == PieceType::Rook &&
        movingPiece.getColor() == PieceColor::Black)
    {
        if (from == Position(0, 0))
            gameState.setBlackCastleQueenSide(false);

        if (from == Position(7, 0))
            gameState.setBlackCastleKingSide(false);
    }
}