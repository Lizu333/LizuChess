#include "Game.h"

#include "../theme/ThemeManager.h"

Game::Game()
    : window(sf::VideoMode({ 1048, 768 }), "LizuChess")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* mouse =
            event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                handleMouseClick(
                    mouse->position.x,
                    mouse->position.y
                );
            }
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    std::string title = "LizuChess - ";

    if (chessEngine.isCheckmate())
    {
        title += "Checkmate";
    }
    else if (chessEngine.isStalemate())
    {
        title += "Stalemate";
    }
    else
    {
        if (chessEngine.getGameState().getSideToMove() == PieceColor::White)
        {
            title += "White";
        }
        else
        {
            title += "Black";
        }

        if (chessEngine.isCurrentSideInCheck())
        {
            title += " is in check";
        }
        else
        {
            title += " to move";
        }
    }

    window.setTitle(title);

    const Theme& theme = ThemeManager::getTheme();

    window.clear(theme.background);

    renderer.draw(
        window,
        chessEngine.getBoard(),
        highlightedSquares,
        pieceSelected,
        selectedSquare,
        hasLastMove,
        lastMoveFrom,
        lastMoveTo
    );

    window.display();
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    if (chessEngine.isGameOver())
        return;

    constexpr float tileSize = 96.f;

    int boardX = static_cast<int>(mouseX / tileSize);
    int boardY = static_cast<int>(mouseY / tileSize);

    Position clickedSquare(boardX, boardY);

    if (!chessEngine.getBoard().isInsideBoard(clickedSquare))
        return;

        //masodik kattintasra lepes
    if (pieceSelected)
    {
        Piece clickedPiece =
            chessEngine.getBoard().getPiece(clickedSquare);

        if (!clickedPiece.isEmpty() &&
            clickedPiece.getColor() ==
            chessEngine.getGameState().getSideToMove())
        {
            selectedSquare = clickedSquare;

            highlightedSquares.clear();

            std::vector<Move> moves =
                chessEngine.generateLegalMoves();

            for (const Move& move : moves)
            {
                if (move.getFrom() == selectedSquare)
                {
                    highlightedSquares.push_back(move.getTo());
                }
            }

            return;
        }

        Move move(selectedSquare, clickedSquare);

        bool moveWasMade = chessEngine.makeMove(move);

        if (moveWasMade)
        {
            pieceSelected = false;
            highlightedSquares.clear();

            hasLastMove = true;
            lastMoveFrom = move.getFrom();
            lastMoveTo = move.getTo();
        }

        return;
    }

    Piece piece =
        chessEngine.getBoard().getPiece(clickedSquare);

    if (piece.isEmpty())
        return;

    if (piece.getColor() !=
        chessEngine.getGameState().getSideToMove())
        return;

    pieceSelected = true;
    selectedSquare = clickedSquare;

    highlightedSquares.clear();

    std::vector<Move> moves =
        chessEngine.getMovesForPiece(selectedSquare);

    for (const Move& move : moves)
    {
        highlightedSquares.push_back(move.getTo());
    }
}