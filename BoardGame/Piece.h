#pragma once
#include "Common.h"

class Piece
{
public:
	Piece(Cell, Kind);
	char repr() const;
	Cell getPosition() const;
	Kind getKind() const;
	void setKind(Kind);
	~Piece();
private:
	Kind kind;
	Cell cell;
};

