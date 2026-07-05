#pragma once

class Position
{
public:
    Position();
    Position(int x, int y);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

private:
    int x;
    int y;
};