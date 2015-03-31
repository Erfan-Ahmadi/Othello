#include "Common.h"

bool operator== (Cell n, Cell m){ return (n.x == m.x && n.y == m.y) ? true : false; }

bool operator!= (Cell n, Cell m){ return (n.x != m.x || n.y != m.y) ? true : false; }

Cell Cell::operator+ (Cell t){ return (Cell(x + t.x, y + t.y)); }

Cell Cell::operator- () { return (Cell(-x, -y)); }

void Cell::print(){ std::cout << "x : " << x << " , y : " << y << std::endl; }

Cell distance(Cell f, Cell t) 
{
	int x = (t.x > f.x) ? t.x - f.x : f.x - t.x;
	int y = (t.y > f.y) ? t.y - f.y : f.y - t.y;
	return Cell(x, y);
}

string KindToString(Kind t){ return (Kind::White == t) ? "White" : "Black"; }
string WinnerToString(Winner t)
{
	if (Winner::W == t)
		return "White";
	else if (Winner::B == t)
		return "Black";
	else if (Winner::D == t)
		return "Draw";
	return "Invalid";
}