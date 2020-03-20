#pragma once
#include <Windows.h>
#include "framework.h"
#include "Gem.h"
#include <list>
#include <vector>
#include <gdiplus.h>
#include "TurnManager.h"
#include "ScoreManager.h"
#pragma comment (lib,"gdiplus.lib")

using std::list; using std::vector;

class Board
{
private:
	const int CELL_SIZE = 40;
	const int CELL_COUNT = 8;
	const int IMAGE_SIZE = 38;
	const int IMAGE_OFFSET = 1;
	vector<vector<Gem>> gems;
	bool hasDestroyed = false;
	const int scoreToMatch = 25000;
	const short turnLimit = 15;
	short level = 1;
	ScoreManager scoreM;
	TurnManager turnM;

public:
	Board();

	void DrawBoard(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics);

	void DrawScoreTurns(Gdiplus::Graphics* graphics,Gdiplus::Font* font,Gdiplus::Brush* brush);

	BOOL GetGameBoardRect(HWND hWnd, RECT* pRect);
	
	BOOL GetCell(HWND hWnd, int index, RECT* pRect);

	int GetNumber(HWND hWnd, int x, int y);

	int GetCellSize();

	int GetCellCount();

	Gem* GetGemAt(int x, int y);

	template <class CONTAINER>
	CONTAINER GetHorizontalPartnerGems(int x, int y);

	template <class CONTAINER>
	CONTAINER GetVerticalPartnerGems(int x, int y);

	template <class CONTAINER>
	void LookForHorizontalPartners(int x, int y, CONTAINER* list);

	template <class CONTAINER>
	void LookForVerticalPartners(int x, int y, CONTAINER* list);

	template <class CONTAINER>
	CONTAINER GetGemsInRadius(int x, int y, int radius);

	void MoveGems(int x, int y , int i);

	int EmptyNeighboards(int x ,int y);

	void GenerateNewLevel();

	void PlayerMove(vector<int>* moves);

	template <class CONTAINER>
	void DestoyGems(CONTAINER*);

	void CallPower(HWND hWnd,int rawX, int rawY);

	void AfterPlayCollisions();

	bool HasDestoyed();

	void SetHasDestroyed(bool);

	bool gameOver = false;

	void FullReset();

	void DrawGameOver(Gdiplus::Graphics* graphics, Gdiplus::Font* font, Gdiplus::Brush* brush);


private:
	void DrawGemColor(RECT* rc,Gdiplus::Graphics* graphics);

	void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

	void UnSeeGems();

	void GenerateNewGem(Gem* gem);

	void LevelConditions();

};

