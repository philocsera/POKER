#include "Base.h"
#include "CardClass.h"
#include <time.h>

TradeSwit::TradeSwit() { for (int i = 0; i < 5; i++) Swit[i] = FALSE; }

void TradeSwit::Random(){
	srand(time(NULL));
	for (int i = 0; i < 5; i++) Swit[i] = rand()%2?TRUE:FALSE;
}

bool TradeSwit::getSwit(int i) { return this->Swit[i]; }
void TradeSwit::PushSwit(int i) { this->Swit[i] = !this->Swit[i]; }

void ScoreBoard::Init(int Score, int Check[8]) {
  // 0: Pair 1: Triple 2: FourCard 3: Back
  // 4: Royal 5: Straight 6: Flush 7: Full House
	this->Score = Score;
	if (Check[0]) {
		if(Check[0] ^ 1) this->Result = "Two Pair";
		else this->Result = "One Pair";
	}
	else if(Check[1]) this->Result = "Triple";
	else if(Check[2]) this->Result = "Four Of A Kind";
	else if (Check[7]) this->Result = "Full House";
	else if (Check[5]) {
		if (Check[3]) {
			if (Check[6]) this->Result = "Back Straight Flush";
			else this->Result = "Back Straight";
		}
		else if (Check[4]) {
			if(Check[6]) this->Result = "Royal Straight Flush";
			else this->Result = "Royal Straight";
		}
		else if (Check[6]) this->Result = "Straight Flush";
		else this->Result = "Straight";
	}
	else if (Check[6]) this->Result = "Flush";
	else this->Result = "Top";
}

const char* ScoreBoard::GetResult() { return this->Result; }
int ScoreBoard::GetScore() { return this->Score; }
