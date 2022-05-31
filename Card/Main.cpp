#include "Base.h"
#include "CardClass.h"
#include "MusicList.h"

void Test();

int main() {
	Init();
	MainMenu();
}

void PokerGame() {
	Trump Trumps[4];
	TradeSwit RandomChange[3];
	int Scores[4];
	const char* Results[4];
	Dealer.Shuffle();
	for(int i=0;i<4;i++) Trumps[i].ReceiveCard();
	for (int i = 0; i < 3; i++) RandomChange[i].Random();
	PrintWideScreen(FALSE);
	PrintChangeScreen(Trumps[0]);
	PrintCard(Trumps[0], 0);
	for (int i = 1; i < 4; i++) Trumps[i].Change(RandomChange[i - 1]);
	PrintWideScreen(TRUE);
	for (int i = 0; i < 4; i++) {
		ScoreBoard TEMP = Marking(Trumps[i]);
		Scores[i] = TEMP.GetScore();
		Results[i] = TEMP.GetResult();
	}
	Sleep(5000);
}
