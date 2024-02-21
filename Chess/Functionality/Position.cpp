#include "Position.h"

bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.row == pos2.row && pos1.column == pos2.column;
}

bool operator!=(const Position& pos1, const Position& pos2) {
    return !(pos1 == pos2);
}