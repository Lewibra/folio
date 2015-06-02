#include <iostream>
#include <iomanip>
#include "random.h"
#include "Deck.h"
#include "card.h"
#include "Hand.h"
#include "Game.h"

/** \brief
 *  Default constructor to make a card object
 * with a two of clubs
 */
Card::Card(){
    cardSuit = CLUBS;
    cardRank = TWO;
}


/** \brief
* Creates a card object based on input. Input accepts
* the format of "2C" to create two of clubs
*/
Card::Card(string input)
{
    string inputArray = input;
    if (inputArray[1] == 'C'){
        cardSuit = CLUBS;
    } else if (inputArray[1]  == 'H'){
        cardSuit = HEARTS;
    } else if (inputArray[1]  == 'D'){
        cardSuit = DIAMONDS;
    } else if (inputArray[1]  == 'S'){
        cardSuit = SPADES;
    }

    if (inputArray[0] == '2'){
        cardRank = TWO;
    } else if (inputArray[0] == '3'){
        cardRank = THREE;
    } else if (inputArray[0] == '4'){
        cardRank = FOUR;
    } else if (inputArray[0] == '5'){
        cardRank = FIVE;
    } else if (inputArray[0] == '6'){
        cardRank = SIX;
    } else if (inputArray[0] == '7'){
        cardRank = SEVEN;
    } else if (inputArray[0] == '8'){
        cardRank = EIGHT;
    } else if (inputArray[0] == '9'){
        cardRank = NINE;
    } else if (inputArray[0] == 'T'){
        cardRank = TEN;
    } else if (inputArray[0] == 'J'){
        cardRank = JACK;
    }else if (inputArray[0] == 'Q'){
        cardRank = QUEEN;
    } else if (inputArray[0] == 'K'){
        cardRank = KING;
    } else if (inputArray[0] == 'A'){
        cardRank = ACE;
    }

}

/**
*Creates a card object buy using the ranking and suit enums
*/
Card::Card(Rank ranking, Suit suit)
{
    cardRank = ranking;
    cardSuit = suit;
}

/**
*Destructs nothing
*/
Card::~Card(){

}


/**
*Returns the suit of the card
*/
Suit Card::getSuit()
{
    return cardSuit;
}

/**
*returns the rank of the card
*/
Rank Card::getRank()
{
    return cardRank;
}

/**
*Overloads the ostream so that a card object
*can be put onto the ostream as a string
*/
ostream& operator<<(ostream& out, const Card&card)
{
    string stringRank ;
    string stringSuit;


    if (card.cardSuit == CLUBS){
        stringSuit = "C";
    } else if (card.cardSuit == HEARTS){
        stringSuit = "H";
    } else if (card.cardSuit == DIAMONDS){
        stringSuit = "D";
    } else if (card.cardSuit == SPADES){
        stringSuit = "S";
    }

    if (card.cardRank == TWO){
        stringRank = "2";
    } else if (card.cardRank == THREE){
        stringRank = "3";
    } else if (card.cardRank == FOUR){
        stringRank = "4";
    } else if (card.cardRank == FIVE){
        stringRank = "5";
    } else if (card.cardRank == SIX){
        stringRank = "6";
    } else if (card.cardRank == SEVEN){
        stringRank = "7";
    } else if (card.cardRank == EIGHT){
        stringRank = "8";
    } else if (card.cardRank == NINE){
        stringRank = "9";
    } else if (card.cardRank == TEN){
        stringRank = "10";
    } else if (card.cardRank == JACK){
        stringRank = "J";
    }else if (card.cardRank == QUEEN){
        stringRank = "Q";
    } else if (card.cardRank == KING){
        stringRank = "K";
    } else if (card.cardRank == ACE){
        stringRank = "A";
    }

    out << stringRank << stringSuit << ", ";
    return out;
}


/**
*Overload to compare two cards to see which one
* is larger, used for the array of sets to order them
*Returns: true if cardOneAmount is larger than cardTwoAmount
*/
bool Card::operator()(Card* cardOne, Card* cardTwo){
    int cardOneAmount = (int)cardOne->getRank() + (int)cardOne->getSuit();
    int cardTwoAmount = (int)cardTwo->getRank() + (int)cardTwo->getSuit();
    return cardTwoAmount < cardOneAmount;

}
