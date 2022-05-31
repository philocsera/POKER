#ifndef __CARD_CLASS__
#define __CARD_CLASS__

#include <vector>

extern HANDLE StdOutH;

class ScoreBoard {
private:
	int Score;
	const char *Result;
public:
	void Init(int, int[8]);
	const char* GetResult();
	int GetScore();
};

class TradeSwit {
private:
	bool Swit[5];
public:
	TradeSwit();
	void Random();
	bool getSwit(int i);
	void PushSwit(int i);
};

class Card {
private:
	int Num;
	int Pattern;
public:
	Card();
	Card(int N, int P);
	int GetPattern();
	char GetNum();
};

class Trump {
private:
	Card Cards[5];
public:
	void Change(TradeSwit);
	int GetCardPattern(int th);
	char GetCardNum(int th);
	void ReceiveCard();
};

class Deck {
private:
	vector<Card> cardDeck;
public:
	Deck();
	void Shuffle();
	Card GetCard();
	Card CardTrade(Card);
};

void MainMenu();
void gotoxy(int, int);
void PrintCard(Trump, int);
void PrintChangeScreen(Trump);
void PrintMainMenu();
void PrintWideScreen(bool);
void Credit();
void Init();
void PokerGame();
void Play(int);
void Pause(int);
void Stop(int);
int Calc(int, int, int, int);
void CurcorOnOff(bool Visible, int CursorSize);
bool StraightCheck(int, bool, int[13]);
ScoreBoard Marking(Trump);
TradeSwit GetChangeCard();

extern const char * Check;
extern const char * InGameArrow;
extern const char * MainArrow;
extern const char * cardShape[4];
extern const char * Number[];
extern int CardX[5];
extern int ChoiceX[5];
extern int MainY[3];

extern Deck Dealer;
#endif
