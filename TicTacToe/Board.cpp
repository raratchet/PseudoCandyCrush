#include "Board.h"
#include <iostream>
#include "PowerUp.h"
#include <string>

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

void Board::DrawScoreTurns(Gdiplus::Graphics* graphics, Gdiplus::Font* font, Gdiplus::Brush* brush)
{
	Gdiplus::PointF scoreP(0, 0);
	Gdiplus::PointF turnsP(0, 80);
	Gdiplus::PointF levelP(0, 160);

	std::string score = "Score: " + std::to_string(scoreM.GetScore())+ " ";
	std::string turnos = "Turnos: " + std::to_string(turnM.GetTurns())+" ";
	std::string nivel = "Level: " + std::to_string(level)+" ";

	std::wstring score_w = std::wstring(score.begin(), score.end());
	std::wstring turnos_w = std::wstring(turnos.begin(), turnos.end());
	std::wstring nivel_w = std::wstring(nivel.begin(), nivel.end());

	graphics->DrawString(score_w.c_str(), 11, font, scoreP, brush);
	graphics->DrawString(turnos_w.c_str(), 11, font, turnsP, brush);
	graphics->DrawString(nivel_w.c_str(), 11, font, levelP, brush);
}

//Dibuja un sprite específico dependiendo el tipo de gema alojado en una cada casilla
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
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			case 'v':
			{
				Gdiplus::Bitmap bmp0(L"b.png");
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			case 'a':
			{
				Gdiplus::Bitmap bmp0(L"c.png");
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			case 'b':
			{
				Gdiplus::Bitmap bmp0(L"d.png");
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			case 'm':
			{
				Gdiplus::Bitmap bmp0(L"e.png");
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			case 'n':
			{
				Gdiplus::Bitmap bmp0(L"f.png");
				graphics->DrawImage(&bmp0, (int)rc->left + IMAGE_OFFSET + CELL_SIZE * x, (int)rc->top + IMAGE_OFFSET + CELL_SIZE * y, IMAGE_SIZE, IMAGE_SIZE);
			}
			break;
			default:
				break;
			}

			gem = 0;
			delete gem;
		}
}

void Board::DrawGameOver(Gdiplus::Graphics* graphics, Gdiplus::Font* font, Gdiplus::Brush* brush)
{
	Gdiplus::Bitmap bmp(L"gameover.png");
	graphics->DrawImage(&bmp, 0, 0, 800, 600);

	Gdiplus::PointF scoreP(340, 370);
	std::string score = std::to_string(scoreM.GetScore()) +"     " ;
	std::wstring score_w = std::wstring(score.begin(), score.end());
	graphics->DrawString(score_w.c_str(), 20, font, scoreP, brush);

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

//Devuelve un contenedor secuencial que incluye a todas las gemas
//iguales adyacentes a la gema en x , y ¿Se entiende?
template <class CONTAINER>
CONTAINER Board::GetHorizontalPartnerGems(int x, int y)
{
	CONTAINER tmp;
	LookForHorizontalPartners<CONTAINER>(x, y, &tmp);
	UnSeeGems();
	return tmp;
}

template <class CONTAINER>
CONTAINER Board::GetVerticalPartnerGems(int x, int y)
{
	CONTAINER tmp;
	LookForVerticalPartners<CONTAINER>(x, y, &tmp);
	UnSeeGems();
	return tmp;
}

//Busca todos los vecinos del mismo tipo y los guarda en un contenedor secuencial
template <class CONTAINER>
void Board::LookForHorizontalPartners(int x , int y, CONTAINER* partners)
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
							LookForHorizontalPartners(x + 1, y, partners);
						}
					}
					if (x - 1 >= 0)
					{
						if (*gem == *GetGemAt(x - 1, y))
						{
							LookForHorizontalPartners(x - 1, y, partners);
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

template <class CONTAINER>
void Board::LookForVerticalPartners(int x, int y, CONTAINER* partners)
{
	if (x >= 0 && y >= 0)
		if (x < CELL_COUNT && y < CELL_COUNT)
		{
			try
			{
				Gem* gem = GetGemAt(x, y);
				if (!gem->Visited())
				{
					gem->SetVisited(true);
					partners->push_back(gem);
					if (y + 1 < CELL_COUNT)
					{
						if (*gem == *GetGemAt(x, y + 1))
						{
							LookForVerticalPartners(x, y + 1, partners);
						}
					}
					if (y - 1 >= 0)
					{
						if (*gem == *GetGemAt(x, y - 1))
						{
							LookForVerticalPartners(x, y - 1, partners);
						}
					}
				}
				gem = 0;
				delete gem;
			}
			catch (std::exception & e)
			{
				e.what();
			}

		}

}

//Devuelve un contenedor secuencial con todas las gemas en un radio a partir
// de un x y
template <class CONTAINER>
CONTAINER Board::GetGemsInRadius(int x, int y, int radius)	
{
	CONTAINER tmp;

	for (int i = x - radius; i <= x + radius; i++)
	{
		for (int j = y - radius; j <= y + radius; j++)
		{
			if (i < CELL_COUNT && j < CELL_COUNT)
				if (i >= 0 && j >= 0)
					tmp.push_back(GetGemAt(i,j));
		}
	}

	return tmp;
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

					GenerateNewGem(gem2);
				}else
				{
					gem1 = GetGemAt(x, y - a);
					GenerateNewGem(gem1);
				}

			}
			gem1 = 0;
			gem2 = 0;

			delete gem1;
			delete gem2;
		}
}

//Cuenta la cantidad de Gems vacias que hay sobre una posición
int Board::EmptyNeighboards(int x, int y)
{
	if (y >= 0 && y < CELL_COUNT)
	{
		if (GetGemAt(x, y)->GetType() == '0')
			return 1 + EmptyNeighboards(x, y - 1);
	}

	return 0;
}

// Genera un nuevo nivel colocando gemas nuevas en cada casilla
void Board::GenerateNewLevel()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			GetGemAt(x,y)->GenerateNewType();
		}

	for (int x = 0; x < CELL_COUNT; x += 2)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			GenerateNewGem(GetGemAt(x, y));
		}
	for (int x = 1; x < CELL_COUNT; x += 2)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			GenerateNewGem(GetGemAt(x, y));
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

		if(gem1->Contiguous(*gem2))
		{
			*gem1 >> gem2;


			list<Gem*> gemsH = GetHorizontalPartnerGems<list<Gem*>>(c1X, c1Y);
			list<Gem*> gemsV = GetVerticalPartnerGems<list<Gem*>>(c1X, c1Y);

			list<Gem*> gemsi;



			if (gemsH.size() >= 3)
			{
				for (auto tmpgem : gemsH)
					gemsi.push_back(tmpgem);
			}

			if (gemsV.size() >= 3)
			{
				for (auto tmpgem : gemsV)
					gemsi.push_back(tmpgem);
			}

			if (gemsi.size() >= 3)
			{
				DestoyGems<list<Gem*>>(&gemsi);
				hasDestroyed = true;
			}
			else
			{
				*gem1 >> gem2;
			}

			AfterPlayCollisions();
			turnM.NextTurn();
			LevelConditions();
			//DestoyGems(c2X, c2Y, gem1, gem2);
		}

		gem1 = 0;
		gem2 = 0;
		delete gem1;
		delete gem2;


	}


}

template <class CONTAINER>
void Board::DestoyGems(CONTAINER* container)
{
	//Las marca como gems vacias - "Las elimina"
	for (auto it = container->begin(); it != container->end(); it++)
	{

		(*it)->SetType('0');
	}

	for (auto it = container->begin(); it != container->end(); it++)
	{
		if ((*it)->GetType() == '0')
		{
			MoveGems((*it)->GetX(), (*it)->GetY(), EmptyNeighboards((*it)->GetX(), (*it)->GetY()));
		}
	}

	scoreM.AddScore(container->size());

}

//Coloca a todas las gemas como "No visitadas"
void Board::UnSeeGems()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetGemAt(x, y)->SetVisited(false);
}

//Evita la generación de gemas contiguas repetidas en más de 3
//No funciona la chingadera ;-; // Edit: ya sirve :)
void Board::GenerateNewGem(Gem* gem)
{
	int tmp = 1;
	gem->GenerateNewType();

	int x = gem->GetX();
	int y = gem->GetY();

	if (x + 1 < CELL_COUNT)
	{
		if (*gem == *GetGemAt(x + 1, y))
			tmp++;
	}

	if (y + 1 < CELL_COUNT)
	{
		if (*gem == *GetGemAt(x, y + 1))
			tmp++;
	}

	if (x - 1 >= 0)
	{
		if (*gem == *GetGemAt(x - 1, y))
			tmp++;
	}

	if (y - 1 >= 0)
	{
		if (*gem == *GetGemAt(x, y - 1))
			tmp++;
	}

	if (tmp >= 3)
	{
		GenerateNewGem(gem);
	}
}

void Board::CallPower(HWND hWnd,int rawX, int rawY)
{
	int index = GetNumber(hWnd, rawX, rawY);

	int x = index % CELL_COUNT;
	int y = index / CELL_COUNT;

	PowerUp::Bomb(x, y, 1,this);
	turnM.SetTurns(turnM.GetTurns() + 4);
	LevelConditions();

}

//Revisa si hay gemas juntas después de una jugada y las elimina
void Board::AfterPlayCollisions()
{
	if (hasDestroyed)
	{
		hasDestroyed = false;
		for (int x = 0; x < CELL_COUNT; x ++)
			for (int y = 0; y < CELL_COUNT; y++)
			{
				list<Gem*> gemsH = GetHorizontalPartnerGems<list<Gem*>>(x, y);
				list<Gem*> gemsV = GetVerticalPartnerGems<list<Gem*>>(x, y);

				list<Gem*> gemsi;

				if (gemsH.size() >= 3)
				{
					for (auto tmpgem : gemsH)
						gemsi.push_back(tmpgem);
				}

				if (gemsV.size() >= 3)
				{
					for (auto tmpgem : gemsV)
						gemsi.push_back(tmpgem);
				}

				if (gemsi.size() >= 3)
				{
					DestoyGems<list<Gem*>>(&gemsi);
					hasDestroyed = true;
				}
			}
		AfterPlayCollisions();
	}

}

bool Board::HasDestoyed()
{
	return hasDestroyed;
}

void Board::SetHasDestroyed(bool value)
{
	hasDestroyed = value;
}

void Board::LevelConditions()
{
	if (scoreM.GetScore() >= scoreToMatch*level)
	{
		level += 1;
		turnM.Reset();
		GenerateNewLevel();
	}

	if (turnM.GetTurns() >= turnLimit)
	{
		gameOver = true;
	}

}

void Board::FullReset()
{
	level = 1;
	scoreM.ResetScore();
	turnM.Reset();
	GenerateNewLevel();
	gameOver = false;
}