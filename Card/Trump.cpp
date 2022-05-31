#include "Base.h"
#include "CardClass.h"

void Trump::Change(TradeSwit Check) {
	for (int i = 0; i < 5; i++) {
		if (Check.getSwit(i)) this->Cards[i] = Dealer.CardTrade(this->Cards[i]);
	}
}

int Trump::GetCardPattern(int th) { return this->Cards[th].GetPattern(); }
char Trump::GetCardNum(int th) { return this->Cards[th].GetNum(); }

void Trump::ReceiveCard() {
	for (int i = 0; i < 5; i++) {
		Card card = Dealer.GetCard();
		this->Cards[i] = card;
	}
}