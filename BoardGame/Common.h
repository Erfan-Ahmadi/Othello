#pragma once
#include<iostream>
#include<string>
#include <vector>

using std::string;

enum Kind {
	White,
	Black,
	Invalid
};

enum Winner
{
	W,
	B,
	I,
	D,
};
struct Cell
{
	int x;
	int y;

	Cell() : x(-1), y(-1) {};
	Cell(int x, int y) : x(x), y(y) {};

	void print();

	friend bool operator== (Cell, Cell);
	friend bool operator!= (Cell, Cell);
	Cell operator+ (Cell);
	Cell operator- ();
};

string KindToString(Kind t);
string WinnerToString(Winner t);
Cell distance(Cell, Cell);