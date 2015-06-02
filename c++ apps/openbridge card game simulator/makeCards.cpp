// File: makeCards.cpp
// Creates some cards and displays them.

#include <iostream>
#include <iomanip>

#include "card.h"
#include "random.h"
#include "Deck.h"

using namespace std;

// Constants
const int NUM_CARDS = 52;

int main() {

    Deck deck;
	Random randomizer;

	for (int i = 0; i < NUM_CARDS; i++) {
      cout << setw(3) << deck.deck;
	}
	cout << endl << endl;

	return 0;
}

