#include <iostream>
#include <iomanip>
#include "random.h"
#include "Deck.h"
#include "card.h"
#include "Hand.h"
#include "Game.h"




using namespace std;

/**
*Constructor to create a deck
*of 52 card objects, from (2,3,4,5,6, etc) for each suit
*/
Deck::Deck()
{

    cardDeck = new Card*[52];
    reset();

    int cardIndex = 0;
    for (int cardSuit= 0; cardSuit <= 3; cardSuit++){
        for (int cardRank = 0; cardRank <= 12; cardRank++){
            Card *card = new Card((Rank)cardRank, (Suit)cardSuit);
            cardDeck[cardIndex] = card;
            cardIndex++;
        }
    }
}

/**
*Deletes the cardDeck array
*/
Deck::~Deck()
{
    delete cardDeck;

}

/**
*Deals a card from the beginning of the deck
*/
Card* Deck::dealNextCard(){
    Card* nextCard = cardDeck[cardsDealt];
    cardsDealt++;
    return nextCard;

}

/**
*Resets the cardsDealt to 0 so that
*the deck can be dealt from the beginning
*/
void Deck::reset(){
    cardsDealt = 0;
}


/**
*Shuffles the deck in a random order
*/
void Deck::shuffle(){
    Random randomizer;
    for (int i = 0; i < 100; i++){
        randomCard = randomizer.randomInteger(26, 51);
        secondRandomCard = randomizer.randomInteger(0, 25);

        temp = cardDeck[randomCard];
        cardDeck[randomCard] = cardDeck[secondRandomCard];
        cardDeck[secondRandomCard] = temp;

    }
}


/**
*Overloads the ostream so that all the cards in the deck
*can be displayed as strings on the ostream
*/
ostream& operator<<(ostream& out,  Deck& deck){
    string stringSuit;
    string stringRank;
    string finalOutput;
    for (int i = 0; i < 52; i++){
        if ((Suit)deck.cardDeck[i]->getSuit() == CLUBS){
            stringSuit = "C";
        } else if ((Suit)deck.cardDeck[i]->getSuit() == HEARTS){
            stringSuit = "H";
        } else if ((Suit)deck.cardDeck[i]->getSuit() == DIAMONDS){
            stringSuit = "D";
        } else if ((Suit)deck.cardDeck[i]->getSuit() == SPADES){
            stringSuit = "S";
        }

        if ((Rank)deck.cardDeck[i]->getRank() == TWO){
            stringRank = "2";
        } else if ((Rank)deck.cardDeck[i]->getRank() == THREE){
            stringRank = "3";
        } else if ((Rank)deck.cardDeck[i]->getRank() == FOUR){
            stringRank = "4";
        } else if ((Rank)deck.cardDeck[i]->getRank() == FIVE){
            stringRank = "5";
        } else if ((Rank)deck.cardDeck[i]->getRank() == SIX){
            stringRank = "6";
        } else if ((Rank)deck.cardDeck[i]->getRank() == SEVEN){
            stringRank = "7";
        } else if ((Rank)deck.cardDeck[i]->getRank() == EIGHT){
            stringRank = "8";
        } else if ((Rank)deck.cardDeck[i]->getRank() == NINE){
            stringRank = "9";
        } else if ((Rank)deck.cardDeck[i]->getRank() == TEN){
            stringRank = "10";
        } else if ((Rank)deck.cardDeck[i]->getRank() == JACK){
            stringRank = "J";
        }else if ((Rank)deck.cardDeck[i]->getRank() == QUEEN){
            stringRank = "Q";
        } else if ((Rank)deck.cardDeck[i]->getRank() == KING){
            stringRank = "K";
        } else if ((Rank)deck.cardDeck[i]->getRank() == ACE){
            stringRank = "A";
        }

        finalOutput += stringRank + stringSuit + " ";
    }
        out << finalOutput;
        return out;

}


/**
*Overloads the istream so that all the cards in a deck object
*can be put onto the the istream, needed for the text files
*/
istream& operator>>(istream& in,  Deck& deck){
    string input;
    for (int i = 0; i < 52; i++){
        in >> input;
        Card *tempCard = new Card(input);
        deck.cardDeck[i] = tempCard;
    }

    return in;
}



