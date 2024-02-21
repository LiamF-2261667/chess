#ifndef POSITION_H
#define POSITION_H

class Position {
public:
	int row{};
	int column{};

    /* Constructors */
    Position() { }
    Position(const int _row, const int _column) : row{ _row }, column{ _column } { }

    /* Operators */
    friend bool operator==(const Position& pos1, const Position& pos2);
    friend bool operator!=(const Position& pos1, const Position& pos2);
};

#endif
