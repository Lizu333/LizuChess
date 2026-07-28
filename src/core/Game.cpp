#include "Game.h"

#include <string>
#include <vector>

#include "../theme/ThemeManager.h"

Game::Game()
    : window(
        sf::VideoMode({ 1048, 768 }),
        "LizuChess"
    )
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

        if (const auto* key =
            event->getIf<sf::Event::KeyPressed>())
        {
            // Új játék mindig működjön
            if (key->code == sf::Keyboard::Key::G)
            {
                startNewGame();
                continue;
            }

            // A további billentyűk csak promóciónál működnek
            if (!promotionPending)
                continue;

            switch (key->code)
            {
            case sf::Keyboard::Key::Q:
                handlePromotionChoice(PieceType::Queen);
                break;

            case sf::Keyboard::Key::R:
                handlePromotionChoice(PieceType::Rook);
                break;

            case sf::Keyboard::Key::B:
                handlePromotionChoice(PieceType::Bishop);
                break;

            case sf::Keyboard::Key::K:
                handlePromotionChoice(PieceType::Knight);
                break;

            default:
                break;
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

    if (promotionPending)
    {
        title += "Choose promotion: Q, R, B or K";
    }
    else if (chessEngine.isCheckmate())
    {
        title += "Checkmate";
    }
    else if (chessEngine.isStalemate())
    {
        title += "Stalemate";
    }
    else
    {
        const PieceColor sideToMove =
            chessEngine.getGameState().getSideToMove();

        title +=
            sideToMove == PieceColor::White
            ? "White"
            : "Black";

        if (chessEngine.isCurrentSideInCheck())
        {
            title += " is in check";
        }
        else
        {
            title += " to move";
        }

        title += " | Press \'G\' to start a new match";
    }

    window.setTitle(title);

    const Theme& theme =
        ThemeManager::getTheme();

    window.clear(theme.background);

    renderer.draw(
        window,
        chessEngine.getBoard(),
        highlightedSquares,
        pieceSelected,
        selectedSquare,
        hasLastMove,
        lastMoveFrom,
        lastMoveTo,
        promotionPending,
        chessEngine.getGameState().getSideToMove()
    );

    window.display();
}

void Game::handleMouseClick(
    int mouseX,
    int mouseY
)
{
    if (promotionPending)
    {
        handlePromotionMouseClick(
            mouseX,
            mouseY
        );

        return;
    }

    if (chessEngine.isGameOver())
        return;

    constexpr float tileSize = 96.f;

    const int boardX =
        static_cast<int>(mouseX / tileSize);

    const int boardY =
        static_cast<int>(mouseY / tileSize);

    const Position clickedSquare(
        boardX,
        boardY
    );

    if (!chessEngine.getBoard()
        .isInsideBoard(clickedSquare))
    {
        return;
    }

    if (pieceSelected)
    {
        const Piece clickedPiece =
            chessEngine.getBoard()
            .getPiece(clickedSquare);

        const PieceColor sideToMove =
            chessEngine.getGameState()
            .getSideToMove();

        //masik babura kattintassal az lesz kivalasztva
        if (!clickedPiece.isEmpty() &&
            clickedPiece.getColor() == sideToMove)
        {
            selectPiece(clickedSquare);
            return;
        }

        const std::vector<Move> pieceMoves =
            chessEngine.getMovesForPiece(
                selectedSquare
            );

        //promotalas celmezejenek vizsgalata
        for (const Move& legalMove : pieceMoves)
        {
            if (legalMove.getTo() != clickedSquare)
                continue;

            if (legalMove.getType() !=
                MoveType::Promotion)
            {
                continue;
            }

            promotionPending = true;
            promotionFrom = selectedSquare;
            promotionTo = clickedSquare;

            pieceSelected = false;
            highlightedSquares.clear();

            return;
        }

        const Move move(
            selectedSquare,
            clickedSquare
        );

        const bool moveWasMade =
            chessEngine.makeMove(move);

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

    const Piece piece =
        chessEngine.getBoard()
        .getPiece(clickedSquare);

    if (piece.isEmpty())
        return;

    if (piece.getColor() !=
        chessEngine.getGameState()
        .getSideToMove())
    {
        return;
    }

    selectPiece(clickedSquare);
}

void Game::selectPiece(
    const Position& position
)
{
    pieceSelected = true;
    selectedSquare = position;

    highlightedSquares.clear();

    const std::vector<Move> moves =
        chessEngine.getMovesForPiece(
            selectedSquare
        );

    for (const Move& move : moves)
    {
        highlightedSquares.push_back(
            move.getTo()
        );
    }
}

void Game::handlePromotionMouseClick(
    int mouseX,
    int mouseY
)
{
    constexpr int panelX = 820;
    constexpr int firstButtonY = 190;

    constexpr int buttonSize = 64;
    constexpr int buttonSpacing = 20;

    if (mouseX < panelX ||
        mouseX >= panelX + buttonSize)
    {
        return;
    }

    constexpr PieceType promotionPieces[4] =
    {
        PieceType::Queen,
        PieceType::Rook,
        PieceType::Bishop,
        PieceType::Knight
    };

    for (int index = 0; index < 4; index++)
    {
        const int buttonY =
            firstButtonY +
            index * (buttonSize + buttonSpacing);

        const bool insideButton =
            mouseY >= buttonY &&
            mouseY < buttonY + buttonSize;

        if (!insideButton)
            continue;

        handlePromotionChoice(
            promotionPieces[index]
        );

        return;
    }
}

void Game::handlePromotionChoice(
    PieceType pieceType
)
{
    if (!promotionPending)
        return;

    const Move promotionMove(
        promotionFrom,
        promotionTo,
        MoveType::Promotion,
        pieceType
    );

    const bool moveWasMade =
        chessEngine.makeMove(promotionMove);

    if (!moveWasMade)
        return;

    hasLastMove = true;
    lastMoveFrom = promotionFrom;
    lastMoveTo = promotionTo;

    promotionPending = false;
    pieceSelected = false;

    highlightedSquares.clear();
}

void Game::startNewGame()
{
    chessEngine.resetGame();

    pieceSelected = false;
    highlightedSquares.clear();

    hasLastMove = false;

    promotionPending = false;

    selectedSquare = Position();
    lastMoveFrom = Position();
    lastMoveTo = Position();
    promotionFrom = Position();
    promotionTo = Position();
}