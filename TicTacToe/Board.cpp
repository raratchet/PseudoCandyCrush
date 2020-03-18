#include "Board.h"

Board::Board() 
{
	gems = vector<vector<Gem>>(CELL_COUNT, vector<Gem>(CELL_COUNT));
}

void Board::DrawBoard(HWND hWnd,HDC hdc,RECT* rc)
{
	if (GetGameBoardRect(hWnd, rc))
	{
		FillRect(hdc, rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		Rectangle(hdc, rc->left, rc->top, rc->right, rc->bottom);
	}

	for (unsigned short i = 0; i < CELL_COUNT + 1; i++)
	{
		//verticales
		DrawLine(hdc, rc->left + CELL_SIZE * i, rc->top, rc->left + CELL_SIZE * i, rc->bottom);

		//horizontales
		DrawLine(hdc, rc->left, rc->top + CELL_SIZE * i, rc->right, rc->top + CELL_SIZE * i);
	}
}

BOOL Board::GetGameBoardRect(HWND hWnd, RECT* pRect)
{
	RECT rc;
	if (GetClientRect(hWnd, &rc))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		pRect->left = (width - CELL_SIZE * CELL_COUNT) / 2;
		pRect->top = (height - CELL_SIZE * CELL_COUNT) / 2;

		pRect->right = pRect->left + CELL_SIZE * CELL_COUNT;
		pRect->bottom = pRect->top + CELL_SIZE * CELL_COUNT;

		return true;
	}

	SetRectEmpty(pRect);
	return false;
}

void Board::DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}

int Board::GetNumber(HWND hWnd, int x, int y)
{
	POINT p = { x,y };
	RECT rc;
	if (GetGameBoardRect(hWnd, &rc))
	{
		if (PtInRect(&rc, p))
		{
			x = p.x - rc.left;
			y = p.y - rc.top;
			int col = x / CELL_SIZE;
			int row = y / CELL_SIZE;
			return col + row * CELL_COUNT;
		}
		else
		{
			return -1;
		}
	}
	return -1;
}

BOOL Board::GetCell(HWND hWnd, int index, RECT* pRect)
{
	RECT board;
	SetRectEmpty(pRect);
	if (index < 0 || index > (CELL_COUNT * CELL_COUNT) - 1)
		return false;
	if (GetGameBoardRect(hWnd, &board))
	{
		int y = index / CELL_COUNT;
		int x = index % CELL_COUNT;
		pRect->left = board.left + x * CELL_SIZE;
		pRect->top = board.top + y * CELL_SIZE;
		pRect->right = pRect->left + CELL_SIZE;
		pRect->bottom = pRect->top + CELL_SIZE;
		return true;
	}
}

int Board::GetCellSize()
{
	return CELL_SIZE;
}

int Board::GetCellCount()
{
	return CELL_COUNT;
}

Gem* Board::GetGemAt(int x, int y)
{
	return &gems[y][x];
}

list<Gem*> Board::GetPartnerGems(int x, int y)
{
	list<Gem*> tmp;
	LookForPartners(x, y, &tmp);
	return tmp;
}

void Board::LookForPartners(int x , int y, list<Gem*>* partners)
{
	if(x >= 0 && y >= 0)
		if (x < CELL_COUNT && y < CELL_COUNT)
		{
			try 
			{
				Gem* gem = GetGemAt(x, y);
				gems;
				if (!gem->Visited())
				{
					gem->SetVisited(true);
					partners->push_back(gem);
					if (x + 1 < CELL_COUNT)
					{
						if (*gem == *GetGemAt(x + 1, y))
						{
							LookForPartners(x + 1, y, partners);
						}
					}
					if (y + 1 < CELL_COUNT)
					{
						if (*gem == *GetGemAt(x, y + 1))
						{
							LookForPartners(x, y + 1, partners);
						}
					}
					if (x - 1 >= 0)
					{
						if (*gem == *GetGemAt(x - 1, y))
						{
							LookForPartners(x - 1, y, partners);
						}
					}
					if (y - 1 >= 0)
					{
						if (*gem == *GetGemAt(x, y - 1))
						{
							LookForPartners(x, y - 1, partners);
						}
					}
				}
			}
			catch (std::exception& e)
			{
				e.what();
			}

		}

}

//Fuga de memoria por apuntadores?
void Board::MoveGems(int x, int y)
{
	if(y < CELL_COUNT)
		if (y >= 0)
		{
			Gem* gem = GetGemAt(x, y);
			if (y == 0)
			{
				Gem* gemBelow = GetGemAt(x, y + 1);
				gemBelow->SetType(gem->GetType());
				gem->SetType(0); //Generar un nuevo type;
			}
			else
			{
				MoveGems(x, y - 1);
				if (!(y + 1 >= CELL_COUNT))
				{
					Gem* gemBelow = GetGemAt(x, y + 1);
					gemBelow->SetType(gem->GetType());
				}
			}
		}
}

int Board::EmptyNeighboards(int x, int y)
{
	if (y >= 0 && y < CELL_COUNT)
	{
		if (GetGemAt(x, y)->GetType() == '0')
			return 1 + EmptyNeighboards(x, y - 1);
	}

	return 0;
}