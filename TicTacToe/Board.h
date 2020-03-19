#pragma once
#include <Windows.h>
#include "framework.h"
#include "Gem.h"
#include <list>
#include <vector>
#include <gdiplus.h>
#pragma comment (lib,"gdiplus.lib")

using std::list; using std::vector;

class Board
{
private:
	const int CELL_SIZE = 40;
	const int CELL_COUNT = 8;
	vector<vector<Gem>> gems;

public:
	Board();

	void DrawBoard(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics);

	BOOL GetGameBoardRect(HWND hWnd, RECT* pRect);

	void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);
	
	BOOL GetCell(HWND hWnd, int index, RECT* pRect);

	int GetNumber(HWND hWnd, int x, int y);

	int GetCellSize();

	int GetCellCount();

	Gem* GetGemAt(int x, int y);

	list<Gem*> GetPartnerGems(int x, int y);

	void LookForPartners(int x, int y, list<Gem*>* list);

	void MoveGems(int x, int y , int i);

	int EmptyNeighboards(int x ,int y);

	void GenerateNewLevel();

	void PlayerMove(vector<int>* moves);

private:
	void DrawGemColor(RECT* rc,Gdiplus::Graphics* graphics);

	void DestoyGems(int,int,Gem*,Gem*);

	void UnSeeGems();
};

