#pragma once
#include "Piece.h"
#include"Common.h"

using std::vector;


class Board
{
public:
	Board();
	void draw();
	Kind getCurPlayer();
	Winner winner();
	bool IsBoardFull(int&, int&);
	void Count(int&,int&);
	void nextTurn();
	bool PlacePiece(Cell);
	bool PieceExsistance(Cell);
	bool CanFlip(Cell,Cell,Kind,bool);
	vector<Piece*> getPiecesInDir(Cell,Cell);
	void Flip(Cell,Cell,Cell,Kind);
	~Board();
private:
	Kind turn;
	int length;
	void printWinner(Kind kind);
	Piece* Board::getPieceAt(Cell pos) const;
	bool IsPlaceValid(Cell pos, bool*,Kind,bool);
	vector <Piece *> pieces;
};

