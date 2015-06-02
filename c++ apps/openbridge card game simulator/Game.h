#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <iomanip>
#include "Hand.h"
#include "Deck.h"


enum Position{NORTH, EAST, SOUTH, WEST};
class Game
{
    public:
    //Game constructor
    Game();
    //Destructor
    ~Game();
    //Used to set up a game, boolean is true if set up from a text file
    void setup(bool formFile);
    //deals the cards
    void deal();
    //Calls the bid method for each player
    void auction();
    //Changes dealer
    void nextDealer();

    //Overloads the ostream so that everything can be displayed as a string
    friend ostream& operator<<(ostream& out, Game& game);

    //Overloads the istream so that a deck can be put onto the istream
    friend istream& operator>>(istream& in, Game& game);

    protected:
    private:
    //Deck of cards
    Deck deck;
    //Dealer's position
    Position dealer;

    //Each player's hand
    Hand north;
    Hand south;
    Hand east;
    Hand west;
    //string to store the opening bid
    string openingBid;


};

#endif // GAME_H_INCLUDED
