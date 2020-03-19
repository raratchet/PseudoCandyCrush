#include "Board.h"
#include <iostream>

Board::Board() 
{
	gems = vector<vector<Gem>>(CELL_COUNT, vector<Gem>(CELL_COUNT));

	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetGemAt(x, y)->SetPos(x, y);

	GenerateNewLevel();
}

void Board::DrawBoard(HWND hWnd,HDC hdc,RECT* rc, Gdiplus::Graphics* graphics)
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
	DrawGemColor(rc, graphics);
}

void Board::DrawGemColor(RECT* rc, Gdiplus::Graphics* graphics)
{
	for(int x = 0; x < CELL_COUNT;x++)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			Gem* gem = GetGemAt(x, y);
			switch (gem->GetType())
			{
			case '0':
				break;
			case 'r':
			{
				Gdiplus::Bitmap bmp0(L"a.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			case 'v':
			{
				Gdiplus::Bitmap bmp0(L"b.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			case 'a':
			{
				Gdiplus::Bitmap bmp0(L"c.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			case 'b':
			{
				Gdiplus::Bitmap bmp0(L"d.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			default:
				break;
			}

			gem = 0;
			delete gem;
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
	UnSeeGems();
	return tmp;
}

//Busca todos los vecinos del mismo tipo
void Board::LookForPartners(int x , int y, list<Gem*>* partners)
{
	if(x >= 0 && y >= 0)
		if (x < CELL_COUNT && y < CELL_COUNT)
		{
			try 
			{
				Gem* gem = GetGemAt(x, y);
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
				gem = 0;
				delete gem;
			}
			catch (std::exception& e)
			{
				e.what();
			}

		}

}

//Recorre Todas Gemas un espacio hacia abajo en una columna
// param i es la cantidad de espacios que lo vamos a mover
void Board::MoveGems(int x, int y, int i)
{
	if(y < CELL_COUNT && x < CELL_COUNT)
		if (y >= 0 && x >= 0)
		{
			Gem* gem1;
			Gem* gem2;

			for (int a = 0; a < i; a++)
			{
				if ((y - a - i) >= 0)
				{
					gem1 = GetGemAt(x, y - a);
					gem2 = GetGemAt(x, y - a - i);

					*gem2 >> gem1;

					gem2->GenerateNewType();
				}else
				{
					gem1 = GetGemAt(x, y - a);
					gem1->GenerateNewType();
				}

			}
			gem1 = 0;
			gem2 = 0;

			delete gem1;
			delete gem2;
		}
}

//Cuenta la cantidad de Gems vacias hay sobre una posición
int Board::EmptyNeighboards(int x, int y)
{
	if (y >= 0 && y < CELL_COUNT)
	{
		if (GetGemAt(x, y)->GetType() == '0')
			return 1 + EmptyNeighboards(x, y - 1);
	}

	return 0;
}

void Board::GenerateNewLevel()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			GetGemAt(x, y)->GenerateNewType();
		}
}

//Lógica de un turno
void Board::PlayerMove(vector<int>* moves)
{
	int click1 = moves->at(0);
	int click2 = moves->at(1);
	moves->clear();

	if (click1 != click2)
	{
		int c1X = click1 % CELL_COUNT;
		int c1Y = click1 / CELL_COUNT;

		int c2X = click2 % CELL_COUNT;
		int c2Y = click2 / CELL_COUNT;

		Gem* gem1 = GetGemAt(c1X, c1Y);
		Gem* gem2 = GetGemAt(c2X, c2Y);

		//Si estan contiguas
		{
			DestoyGems(c1X, c1Y, gem1, gem2);
			DestoyGems(c2X, c2Y, gem1, gem2);

		}

		gem1 = 0;
		gem2 = 0;
		delete gem1;
		delete gem2;
	}


}

void Board::DestoyGems(int x, int y, Gem* gem1, Gem* gem2)
{
	//Swap;
	*gem1 >> gem2;


	list<Gem*> gemsi = GetPartnerGems(x, y);
	if (gemsi.size() >= 3)
	{
		//Las marca como gems vacias - "Las elimina"
		for (Gem* gem : gemsi)
		{
			gem->SetType('0');
		}

		for (Gem* gem : gemsi)
		{
			if (gem->GetType() == '0')
			{
				MoveGems(gem->GetX(), gem->GetY(), EmptyNeighboards(gem->GetX(), gem->GetY()));
			}
		}


	}
	else
	{
		*gem1 >> gem2;
	}
}

void Board::UnSeeGems()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetGemAt(x, y)->SetVisited(false);
}