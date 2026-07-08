#include "Board.h"
#include <iostream>

Board::Board()
{
    setupStartingPosition();
}

void Board::reset()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            squares[y][x] = Piece();
        }
    }
}

void Board::setupStartingPosition()
{
    reset();

    //feketek
    setPiece(Position(0, 0), Piece(PieceType::Rook, PieceColor::Black));
    setPiece(Position(1, 0), Piece(PieceType::Knight, PieceColor::Black));
    setPiece(Position(2, 0), Piece(PieceType::Bishop, PieceColor::Black));
    setPiece(Position(3, 0), Piece(PieceType::Queen, PieceColor::Black));
    setPiece(Position(4, 0), Piece(PieceType::King, PieceColor::Black));
    setPiece(Position(5, 0), Piece(PieceType::Bishop, PieceColor::Black));
    setPiece(Position(6, 0), Piece(PieceType::Knight, PieceColor::Black));
    setPiece(Position(7, 0), Piece(PieceType::Rook, PieceColor::Black));

    for (int x = 0; x < 8; x++)
    {
        setPiece(Position(x, 1), Piece(PieceType::Pawn, PieceColor::Black));
    }

    //feherek
    setPiece(Position(0, 7), Piece(PieceType::Rook, PieceColor::White));
    setPiece(Position(1, 7), Piece(PieceType::Knight, PieceColor::White));
    setPiece(Position(2, 7), Piece(PieceType::Bishop, PieceColor::White));
    setPiece(Position(3, 7), Piece(PieceType::Queen, PieceColor::White));
    setPiece(Position(4, 7), Piece(PieceType::King, PieceColor::White));
    setPiece(Position(5, 7), Piece(PieceType::Bishop, PieceColor::White));
    setPiece(Position(6, 7), Piece(PieceType::Knight, PieceColor::White));
    setPiece(Position(7, 7), Piece(PieceType::Rook, PieceColor::White));

    for (int x = 0; x < 8; x++)
    {
        setPiece(Position(x, 6), Piece(PieceType::Pawn, PieceColor::White));
    }
}

bool Board::isInsideBoard(const Position& position) const
{
    return position.getX() >= 0 &&
        position.getX() < 8 &&
        position.getY() >= 0 &&
        position.getY() < 8;
}

Piece Board::getPiece(const Position& position) const
{
    return squares[position.getY()][position.getX()];
}

void Board::setPiece(const Position& position, const Piece& piece)
{
    squares[position.getY()][position.getX()] = piece;
}

bool Board::isSquareEmpty(const Position& position) const
{
    return getPiece(position).isEmpty();
}

//makeMove w enpassant
void Board::makeMove(const Move& move)
{
    Piece piece = getPiece(move.getFrom());

    if (piece.isEmpty())
        return;

    bool isCastling =
        piece.getType() == PieceType::King &&
        (move.getTo().getX() - move.getFrom().getX() == 2 ||
            move.getTo().getX() - move.getFrom().getX() == -2);

    if (isCastling)
    {
        int y = move.getFrom().getY();

        if (move.getTo().getX() == 6)
        {
            setPiece(Position(6, y), piece);
            setPiece(Position(4, y), Piece());

            Piece rook = getPiece(Position(7, y));
            setPiece(Position(5, y), rook);
            setPiece(Position(7, y), Piece());

            return;
        }

        if (move.getTo().getX() == 2)
        {
            setPiece(Position(2, y), piece);
            setPiece(Position(4, y), Piece());

            Piece rook = getPiece(Position(0, y));
            setPiece(Position(3, y), rook);
            setPiece(Position(0, y), Piece());

            return;
        }
    }

    bool isEnPassant =
        piece.getType() == PieceType::Pawn &&
        move.getFrom().getX() != move.getTo().getX() &&
        getPiece(move.getTo()).isEmpty();

    if (isEnPassant)
    {
        int capturedPawnY = move.getFrom().getY();

        setPiece(
            Position(move.getTo().getX(), capturedPawnY),
            Piece()
        );
    }

    setPiece(move.getTo(), piece);
    setPiece(move.getFrom(), Piece());
}

 

  

void Board::printToConsole() const
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece piece = getPiece(Position(x, y));

            if (piece.isEmpty())
            {
                std::cout << ". ";
                continue;
            }

            char symbol = '?';

            switch (piece.getType())
            {
            case PieceType::Pawn:   symbol = 'P'; break;
            case PieceType::Knight: symbol = 'N'; break;
            case PieceType::Bishop: symbol = 'B'; break;
            case PieceType::Rook:   symbol = 'R'; break;
            case PieceType::Queen:  symbol = 'Q'; break;
            case PieceType::King:   symbol = 'K'; break;
            default:                symbol = '?'; break;
            }

            if (piece.getColor() == PieceColor::Black)
                symbol = static_cast<char>(std::tolower(symbol));

            std::cout << symbol << ' ';
        }

        std::cout << '\n';
    }
}

void Board::setupCheckTestPosition()
{
    reset();

    //white king
    setPiece(Position(4, 7), Piece(PieceType::King, PieceColor::White));

    //black king
    setPiece(Position(4, 0), Piece(PieceType::King, PieceColor::Black));

    //black rook gives check on white king
    setPiece(Position(4, 3), Piece(PieceType::Rook, PieceColor::Black));
}

void Board::setupCastlingTestPosition()
{
    reset();

    //feher
    setPiece(Position(4, 7), Piece(PieceType::King, PieceColor::White));
    setPiece(Position(0, 7), Piece(PieceType::Rook, PieceColor::White));
    setPiece(Position(7, 7), Piece(PieceType::Rook, PieceColor::White));

    //fekete
    setPiece(Position(4, 0), Piece(PieceType::King, PieceColor::Black));
    setPiece(Position(0, 0), Piece(PieceType::Rook, PieceColor::Black));
    setPiece(Position(7, 0), Piece(PieceType::Rook, PieceColor::Black));
}


//enpassant
void Board::setupEnPassantTestPosition()
{
    reset();

    //kiralyok
    setPiece(Position(4, 7), Piece(PieceType::King, PieceColor::White));
    setPiece(Position(4, 0), Piece(PieceType::King, PieceColor::Black));

    //fehergyalog
    setPiece(Position(4, 3), Piece(PieceType::Pawn, PieceColor::White));

    //feketegyalog
    setPiece(Position(5, 1), Piece(PieceType::Pawn, PieceColor::Black));
}