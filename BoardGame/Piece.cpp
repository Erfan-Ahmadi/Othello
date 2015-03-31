#include "Piece.h"

#include<iostream>


Piece::Piece(Cell cel, Kind c) : cell(cel), kind(c) { /*std::cout << "Piece Generated : " << repr() << std::endl;*/ }

//char Piece::repr() const { return (kind == Kind::White) ? 'W' : 'B'; }
char Piece::repr() const { return (kind == Kind::White) ? (char)176 : (char)219; }

Cell Piece::getPosition() const { return cell; }

Kind Piece::getKind() const { return kind; }

void Piece::setKind(Kind k) { kind = k; }

Piece::~Piece()
{
}
