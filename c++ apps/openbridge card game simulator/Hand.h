#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
#include "card.h"
#include <vector>
#include <set>
#include <iterator>

using namespace std;

class Hand
{
    public:
    //Constructor to set the variables needed to store card points
    //And sets up the array of sets to store cards of each suit
    Hand();

    //Deletes the array of sets
    ~Hand();

    //Adds a card to a hand object
    void addCard(Card* card);

    //clears everything in the hand and sets high and low card points to 0
    void clear();

    //Makes a bid, based on what cards are in the hand
    string makeBid();

    friend ostream& operator<<(ostream& out, Hand& hand);

    protected:
    private:
    //array of sets, ordered by the Card operator overload
    // , to store each suit's cards.
    set<Card*, Card> handArray[4];

    //Variables to store the card points
    int HIGH_CARD_POINTS;
    int LOW_CARD_POINTS;

    //Private variables for refactoring
    //Returns everything in a hand as a string
    string convertToString(int suit, string stringSuit);
    //Method to calculate the high card points
    void highCardCheck(Card*);
    //Methods to calculate the low card points
    void lowCardCheck(Suit);

};


#endif // HAND_H_INCLUDED
