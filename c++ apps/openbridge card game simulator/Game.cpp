#include "random.h"
#include "Deck.h"
#include "card.h"
#include "Hand.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
*Constructor for Game.cpp
*sets the dealer to north
*/
Game::Game()
{
    dealer = NORTH;
}

Game::~Game()
{
    //storing my hands in an array changed
    //some of the results, so I left it out
}

/** \brief
 * Sets up a game by resetting the deck and clearing
 * each hand. Shuffles the deck if there is no file input.
 * Doesn't do it if the game is based on a file.
 * \param fromFile, true if the input is
 * to be from a file. False, otherwise.
 *
 */
void Game::setup(bool fromFile)
{
    deck.reset();
    north.clear();
    south.clear();
    east.clear();
    west.clear();
    if (!fromFile)
    {
        deck.shuffle();
    }
}


/** \brief
 * Deals the cards starting from the dealer's
 * left.
 */
void Game::deal()
{
    //Cases to deal cards, depending on who is the dealer
    if (dealer == NORTH)
    {
        for(int i = 0; i < 52; i+=4)
        {
            east.addCard(deck.dealNextCard());
            south.addCard(deck.dealNextCard());
            west.addCard(deck.dealNextCard());
            north.addCard(deck.dealNextCard());
        }
    }
    else if (dealer == EAST)
    {
        for(int i = 0; i < 52; i+=4)
        {
            south.addCard(deck.dealNextCard());
            west.addCard(deck.dealNextCard());
            north.addCard(deck.dealNextCard());
            east.addCard(deck.dealNextCard());
        }
    }
    else if (dealer == SOUTH)
    {
        for(int i = 0; i < 52; i+=4)
        {
            west.addCard(deck.dealNextCard());
            north.addCard(deck.dealNextCard());
            east.addCard(deck.dealNextCard());
            south.addCard(deck.dealNextCard());
        }
    }
    else if (dealer == WEST)
    {
        for(int i = 0; i < 52; i+=4)
        {
            north.addCard(deck.dealNextCard());
            east.addCard(deck.dealNextCard());
            south.addCard(deck.dealNextCard());
            west.addCard(deck.dealNextCard());
        }
    }
}

/** \brief
 * Starts the bidding from the dealer,
 * then to their left. Stops until anything
 * but a pass is made. The opening bid is
 * recorded here.
 *
 */
void Game::auction(){
    //Cases for making bids, depending on who's dealing
    if(dealer == NORTH)
    {
    openingBid = "";
            if (north.makeBid() != "PASS"){
                    openingBid +="North with " + north.makeBid();
            }else if (east.makeBid() != "PASS"){
                    openingBid +="East with " + east.makeBid();
            }else if (south.makeBid() != "PASS"){
                    openingBid +="South with " + south.makeBid();
            }else if (west.makeBid() != "PASS"){
                    openingBid +="West with " + west.makeBid();
            } else {
                    openingBid = "nobody, everyone passed.";
            }
    }
    else if(dealer == EAST)
    {
            openingBid = "";
            if (east.makeBid() != "PASS"){
                    openingBid +="East with " + east.makeBid();
            }else if (south.makeBid() != "PASS"){
                    openingBid +="South with " + south.makeBid();
            }else if (west.makeBid() != "PASS"){
                    openingBid +="West with " + west.makeBid();
            }else if (north.makeBid() != "PASS"){
                    openingBid +="North with " + north.makeBid();
            } else {
                    openingBid = "nobody, everyone passed";
            }
    }
    else if(dealer == SOUTH)
    {
            openingBid = "";
            if (south.makeBid() != "PASS"){
                    openingBid += "South with " + south.makeBid();
            }else if (west.makeBid() != "PASS"){
                    openingBid += "West with " + west.makeBid();
            }else if (north.makeBid() != "PASS"){
                    openingBid += "North with " + north.makeBid();
            }else if (east.makeBid() != "PASS"){
                    openingBid += "East with " + east.makeBid();
            }else {
                    openingBid = "nobody, everyone passed";
            }
    }
    else if(dealer == WEST)
    {
            openingBid = "";
            if (west.makeBid() != "PASS"){
                    openingBid += "West with " + west.makeBid();
            }else if (north.makeBid() != "PASS"){
                    openingBid += "North with " + north.makeBid();
            }else if (east.makeBid() != "PASS"){
                    openingBid += "East with " + east.makeBid();
            }else if (south.makeBid() != "PASS"){
                    openingBid += "South with " + south.makeBid();
            }else {
                    openingBid = "nobody, everyone passed";
            }
    }
}


/** \brief
 * Changes dealer, to the current dealer's left
 */
void Game::nextDealer()
{
    if(dealer == NORTH)
    {
        dealer = EAST;
    }
    else if(dealer == EAST)
    {
        dealer = SOUTH;
    }
    else if(dealer == SOUTH)
    {
        dealer = WEST;
    }
    else if(dealer == WEST)
    {
        dealer = NORTH;
    }
}

/** \brief
 * Overloading ostream so that it can output a
 * game object onto the stream. The game object
 * displays all four hands, starting with the dealer, plus
 * their card count score and the opening bid.
 */
ostream& operator<<(ostream &out, Game &game)
{
    //variables, prevention of magic numbers!
    string northString = "NORTH";
    string eastString = "EAST";
    string southString = "SOUTH";
    string westString = "WEST";

    if(game.dealer == NORTH)
    {
        out << northString << endl << game.north << endl << endl;
        out << eastString << endl << game.east << endl << endl;
        out << southString << endl << game.south << endl << endl;
        out << westString << endl << game.west << endl << endl << endl;
        out << "Opening bid is " << game.openingBid;
    }
    else if(game.dealer == EAST)
    {
        out << eastString << endl << game.east << endl << endl;
        out << southString << endl << game.south << endl << endl;
        out << westString << endl << game.west << endl << endl;
        out << northString << endl << game.north << endl << endl;
        out << endl << "Opening bid is " << game.openingBid;
    }
    else if(game.dealer == SOUTH)
    {
        out << southString << endl << game.south << endl << endl;
        out << westString << endl << game.west << endl << endl;
        out << northString << endl << game.north << endl << endl;
        out << eastString << endl << game.east << endl << endl;
        out << endl << "Opening bid is " << game.openingBid;
    }
    else if(game.dealer == WEST)
    {
        out << westString << endl << game.west << endl << endl;
        out << northString << endl << game.north << endl << endl;
        out << eastString << endl << game.east << endl << endl;
        out << southString << endl << game.south << endl << endl;
        out << endl << "Opening bid is " << game.openingBid;
    }
    return out;

}




/** \brief
 * Pass the input stream onto the deck
 * so the cards can be read from a text file
 */
istream& operator>>(istream &in, Game &game){
    in >> game.deck;
    return in;
}
