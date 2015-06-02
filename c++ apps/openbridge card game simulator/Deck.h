#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <iomanip>
#include "card.h"



class Deck
{
    public:
        //Constructs an array of 52 cards (a deck)
        Deck();
        //Deletes the array of cards
        ~Deck();
        //Sets cards dealt to 0
        void reset();
        //Deals a card
        Card* dealNextCard();
        //Shuffles the deck
        void shuffle();

        //Overloads to output a deck and read input from a text file
        friend ostream& operator<<(ostream&, Deck&);
        friend istream& operator>>(istream&, Deck&);

    protected:
    private:
        //card of pointers to a pointer, this will be turned into an array
        Card **cardDeck;
        //Tally of cards dealt
        int cardsDealt;
        //Temporary Card pointer to shuffle the deck
        Card* temp;

        //temporary variables for random ints
        int randomCard;
        int secondRandomCard;

};

#endif // DECK_H
