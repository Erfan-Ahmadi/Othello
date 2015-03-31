#include "Board.h"

using std::cout;
using std::endl;


Board::Board() : length(8), turn(Kind::Black),
pieces
({
	new Piece(Cell(3, 4), Kind::Black),
	new Piece(Cell(4, 3), Kind::Black),
	new Piece(Cell(3, 3), Kind::White),
	new Piece(Cell(4, 4), Kind::White)
})
{}

	void Board::draw()
	{
		cout << " ";
		for (int j = 0; j < length; ++j)
		{
			cout << "  " << char('A' + j) << " ";
		}
		cout << endl;
		cout << " ";
		for (int j = 0; j < length; ++j)
		{
			cout << "+---";
		}
		cout << "+" << endl;

		for (int i = 0; i < length; ++i)
		{
			cout << i + 1;
			for (int j = 0; j < length; ++j)
			{
				char f = ' ';

				Cell Pos = Cell(j, i);
				const Piece* piece = getPieceAt(Pos);

				if (piece != nullptr)
					f = piece->repr();

				cout << "| " << f << " ";
			}
			cout << "|" << endl;
			cout << " ";
			for (int j = 0; j < length; ++j)
			{
				cout << "+---";
			}
			cout << "+" << endl;
		}
	}

	Piece* Board::getPieceAt(Cell pos) const
	{
		for (int i = 0; i < int(pieces.size()); ++i)
			if (pieces[i]->getPosition() == pos)
				return pieces[i];
		return nullptr;
	}

	Board::~Board()
	{
		for (int i = 0; i < int(pieces.size()); ++i)
		{
			delete pieces[i];
			pieces[i] = nullptr;
		}
	}

	Kind Board::getCurPlayer()
	{
		return turn;
	}

	Winner Board::winner()
	{
		int white_count = 0;
		int black_count = 0;
		if (IsBoardFull(white_count, black_count))
		{
			if (white_count > black_count)
				return Winner::W;
			else if (black_count > white_count)
				return Winner::B;
			else
				return Winner::D;
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					bool CanF[8];
					Cell pos = Cell(j, i);
					if (IsPlaceValid(pos, CanF, turn, false))
					{
						return Winner::I;
					}
				}
			}

			if (white_count > black_count)
				return Winner::W;
			else if (black_count > white_count)
				return Winner::B;
			else
				return Winner::D;
		}
		return Winner::I;
	}

	bool Board::IsBoardFull(int & white, int & black)
	{
		Count(white, black);
		if (white + black == 64)
			return true;
		else
			return false;
	}

	void Board::Count(int & white, int & black)
	{
		int w = 0;
		int b = 0;

		for (int i = 0; i < int(pieces.size()); ++i)
		{
			Piece* const p = pieces[i];
			if (p->getKind() == Kind::White)
				w++;
			else if (p->getKind() == Kind::Black)
				b++;
		}
		white = w;
		black = b;
	}

	void Board::nextTurn()
	{
		if (turn == Kind::White)
			turn = Kind(Kind::White + 1);//For Learning And Fun
		else
			turn = Kind::White;
	}

	bool Board::PlacePiece(Cell pos)
	{
		bool CanF[8];
		if (IsPlaceValid(pos, CanF, turn,true))
		{
			Piece* const p = new Piece(pos, getCurPlayer());
			pieces.push_back(p);
			return true;
		}
		return false;
	}

	bool Board::PieceExsistance(Cell pos){ return (getPieceAt(pos) != nullptr); }

	bool Board::IsPlaceValid(Cell pos, bool* CanF, Kind kind, bool DoTheFlip)
	{
		if (PieceExsistance(pos)) return false;

		Cell Cells[8] =
		{
			Cell(pos.x + 1, pos.y),
			Cell(pos.x - 1, pos.y),
			Cell(pos.x, pos.y + 1),
			Cell(pos.x, pos.y - 1),
			Cell(pos.x + 1, pos.y + 1),
			Cell(pos.x - 1, pos.y - 1),
			Cell(pos.x - 1, pos.y + 1),
			Cell(pos.x + 1, pos.y - 1)
		};

		Cell Dirs[8] =
		{
			Cell(1, 0),
			Cell(-1, 0),
			Cell(0, 1),
			Cell(0, -1),
			Cell(+1, +1),
			Cell(-1, -1),
			Cell(-1, +1),
			Cell(+1, -1)
		};

		if ((PieceExsistance(Cells[0]) && CanFlip(pos, Dirs[0], kind, DoTheFlip)))
			CanF[0] = true;

		if ((PieceExsistance(Cells[1]) && CanFlip(pos, Dirs[1], kind, DoTheFlip)))
			CanF[1] = true;

		if ((PieceExsistance(Cells[2]) && CanFlip(pos, Dirs[2], kind, DoTheFlip)))
			CanF[2] = true;

		if ((PieceExsistance(Cells[3]) && CanFlip(pos, Dirs[3], kind, DoTheFlip)))
			CanF[3] = true;

		if ((PieceExsistance(Cells[4]) && CanFlip(pos, Dirs[4], kind, DoTheFlip)))
			CanF[4] = true;

		if ((PieceExsistance(Cells[5]) && CanFlip(pos, Dirs[5], kind, DoTheFlip)))
			CanF[5] = true;

		if ((PieceExsistance(Cells[6]) && CanFlip(pos, Dirs[6], kind, DoTheFlip)))
			CanF[6] = true;

		if ((PieceExsistance(Cells[7]) && CanFlip(pos, Dirs[7], kind, DoTheFlip)))
			CanF[7] = true;


		for (int i = 0; i < 8; ++i)
		{
			if (true == CanF[i])
				return true;
		}

		return false;
	}

	bool Board::CanFlip(Cell pos, Cell dir, Kind kind,bool DoTheFlip)
	{
		vector<Piece*> m_pieces = getPiecesInDir(pos, dir);
		Cell to;

		for (int i = 0; i < int(m_pieces.size()); ++i)
		{
			Cell t = m_pieces[i]->getPosition();
			Cell dis = distance(pos, t);
			if (m_pieces[i]->getKind() == kind)
			{
				if ((dis.x > 1) || (dis.y > 1))
				{
					if (DoTheFlip)
						Flip(pos, dir, t, kind);
					return true;
				}
				else
					return false;
			}
		}
		return false;
	}

	void Board::Flip(Cell from, Cell dir, Cell to, Kind kind)
	{
		Cell cur = from;
		while (cur != to)
		{
			cur = cur + dir;
			Piece* const p = getPieceAt(cur);
			p->setKind(kind);
		}
	}

	vector<Piece*> Board::getPiecesInDir(Cell from, Cell dir)
	{
		Cell cur = from;
		vector<Piece*> temp;

		while (cur.x <= 7 && cur.y <= 7 && cur.x >= 0 && cur.y >= 0)
		{
			cur = cur + dir;
			Piece* p = getPieceAt(cur);
			if (p != nullptr)
				temp.push_back(p);
			else
				break;
		}
		return temp;
	}