#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Position.h"

class Movement {
public:
	Position from{};
	Position to{};

	Movement() { }
	Movement(const Position _from, const Position _to) : from{ _from }, to{ _to } { }
};

#endif
