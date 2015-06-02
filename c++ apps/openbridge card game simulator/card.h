#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


enum Rank{TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
enum Suit{CLUBS, DIAMONDS, HEARTS, SPADES};
class Card
{
    public:
        //Constructor to create a 2 of Clubs
        Card();
        //Constructor to create a card from a string ("2C") will make a 2 of clubs
        Card(string input);

        //Constructor that makes a card from the given card rank and suit
        Card(Rank ranking, Suit suit);
        //Destructor
        ~Card();
        //returns the card rank or card suit
        Rank getRank();
        Suit getSuit();

        friend ostream& operator<<( ostream& outm, const Card& card);
        bool operator()(Card* , Card* );

    protected:
    private:
        //Variables to store the rank and suit of a card
        Rank cardRank;
        Suit cardSuit;

        //String used to convert the card to a string
        string stringSuit;
};

#endif // CARD_H
