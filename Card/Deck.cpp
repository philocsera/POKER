#include "Base.h"
#include "CardClass.h"
#include <time.h>

Deck::Deck() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card card(j, i);
			this->cardDeck.push_back(card);
		}
	}
}

void Deck::Shuffle() { 
	srand(time(NULL));
	int HowMany = int(rand() * 100) % 10, CardN = this->cardDeck.size();
	for (int i = 0; i <= HowMany; i++) {
		for (int j = 0; j < CardN; j++) {
			int to = int(rand() * 100) % CardN;
			Card TEMP = this->cardDeck[j];
			this->cardDeck[j] = cardDeck[to];
			cardDeck[to] = TEMP;
		}
	}
}

Card Deck::GetCard() {
	Card TEMP = this->cardDeck.back();
	this->cardDeck.pop_back();
	return TEMP;
}

Card Deck::CardTrade(Card RCard) {
	this->cardDeck.insert(this->cardDeck.begin(), RCard);
	return this->GetCard();
}