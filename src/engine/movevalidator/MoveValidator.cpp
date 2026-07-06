#include "MoveValidator.h"

MoveValidator::MoveValidator()
{
}

bool MoveValidator::isMoveLegal(
    const Board& board,
    const GameState& gameState,
    const Move& move
) const
{
    (void)board;
    (void)gameState;
    (void)move;

    //Egyelore minden lepes szabalyosnak szamit, kesobb ellenorzesek
    //itt ellenorizni:
    //sakkban marad-e a kiraly
    //sancolas szabalyos-e
    //enpassant szabalyos-e
    //sajat babut nem ut-e
    return true;
}