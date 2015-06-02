#include "random.h"
#include "Deck.h"
#include "card.h"
#include "Hand.h"
#include "Game.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

/** \brief
 * Initialise an array of 4 sets, each one stores
 * a different type of suit for cards
 * .Sets the card point variables to 0.
 */
Hand::Hand()
{
    set<Card*, Card> handArray[4];
    HIGH_CARD_POINTS = 0;
    LOW_CARD_POINTS = 0;
}

/** \brief
 * Delete the array of sets, which is full of pointers!
 */
Hand::~Hand()
{
    delete []handArray;

}

/** \brief
 * Clears everything in the array of sets
 * Sets the card point variables to 0
 */
void Hand::clear()
{
    for (int i = 0; i < 4; i++)
    {
        handArray[i].clear();
    }

    HIGH_CARD_POINTS = 0;
    LOW_CARD_POINTS = 0;
}

/** \brief
 * Adds a card to a set in the array, relevant
 * to it's suit, aswells as calculates each cards
 * high card point and low card point.
 */
void Hand::addCard(Card* card)
{
    highCardCheck(card);
    lowCardCheck(card->getSuit());
    handArray[card->getSuit()].insert(card);
}


/**
* Private methods to calculate the high card points
*/
void Hand::highCardCheck(Card* card)
{
    //If Card* card is any of these, points will be added
    if (card->getRank() == JACK)
    {
        HIGH_CARD_POINTS++;
    }

    if (card->getRank() == QUEEN)
    {
        HIGH_CARD_POINTS +=2;
    }

    if (card->getRank() == KING)
    {
        HIGH_CARD_POINTS +=3;
    }

    if (card->getRank() == ACE)
    {
        HIGH_CARD_POINTS +=4;
    }
}

/**
*Private method to calculate the low card points of a card that
* is added to a set in the array
*/
void Hand::lowCardCheck(Suit suit)
{
    //if the suit set in the array has more than 4 cards
    //a point will be added to the low card point variable
    //every time another card is added
    int ARRAY_SIZE = (int)handArray[suit].size() + 1;
    if (ARRAY_SIZE > 4)
    {
        LOW_CARD_POINTS++;
    }

}

/** \brief
 * Algorithim to make a bid depending on
 * what is in your hand.
 * Returns the recommendation as a string.
 */
string Hand::makeBid()
{
    //set up some variables that will be needed

    //Calculate the total card points in a hand
    int TOTAL_POINTS = HIGH_CARD_POINTS + LOW_CARD_POINTS;

    //Each hand will be assumed as balanced
    //because only one suit needs to have 5 or more, or 1 and below
    //for it to be considered unbalanced
    bool balanced = true;

    //The recommendation for the bidding
    string DECISION;

    //Counter for how much suits have the same number of cards
    int SUIT_COUNT = 0;

    //Storing the amount of cards in each suit
    int AMOUNT_OF_HEARTS = handArray[HEARTS].size();
    int AMOUNT_OF_SPADES = handArray[SPADES].size();
    int AMOUNT_OF_DIAMONDS = handArray[DIAMONDS].size();
    int AMOUNT_OF_CLUBS = handArray[CLUBS].size();


    //If one of these rules are true, the hand is considered unbalanced
    if(AMOUNT_OF_HEARTS > 4 || AMOUNT_OF_HEARTS < 2)
    {
        balanced = false;
    }
    else if(AMOUNT_OF_DIAMONDS > 4 || AMOUNT_OF_DIAMONDS < 2)
    {
        balanced = false;
    }
    else if(AMOUNT_OF_CLUBS > 4 || AMOUNT_OF_CLUBS < 2)
    {
        balanced = false;
    }
    else if(AMOUNT_OF_SPADES > 4 || AMOUNT_OF_SPADES < 2)
    {
        balanced = false;
    }


    //If the hand is balanced
    if (balanced)
    {
        //Pass if the points are between 0 and 12
        if (TOTAL_POINTS >= 0 && TOTAL_POINTS <= 12)
        {
            DECISION = "PASS";
        }

        //if the total points are 13 and 14
        else if (TOTAL_POINTS >= 13 && TOTAL_POINTS <= 14)
        {
            if (AMOUNT_OF_CLUBS == AMOUNT_OF_DIAMONDS)
            {
                //Do this if the minor suits are both 4 or 3
                if(AMOUNT_OF_CLUBS==4 && AMOUNT_OF_DIAMONDS==4)
                {
                    DECISION = "1D";
                    //set the decision to 1D if there are 4 clubs and 4 diamonds
                }else if (AMOUNT_OF_CLUBS == 3 && AMOUNT_OF_DIAMONDS==3)
                {
                    DECISION = "1C";
                    //set the decision to 1C if there are 3 clubs and 3 diamonds
                }
            }
            else
            {
                //else just bid the minor suit you have most of
                if (AMOUNT_OF_CLUBS > AMOUNT_OF_DIAMONDS)
                {
                    DECISION = "1C";
                }
                else if (AMOUNT_OF_CLUBS < AMOUNT_OF_DIAMONDS)
                {
                    DECISION = "1D";
                }
            }
        }
        //No Trump if you have 15 --> 17 points
        else if(TOTAL_POINTS >=15 && TOTAL_POINTS <=17)
        {
            DECISION = "1 NT";
        }

        //18 --> 19 is the same as 13 --> 14
        else if (TOTAL_POINTS >= 18 && TOTAL_POINTS <= 19)
        {
            if (AMOUNT_OF_CLUBS == AMOUNT_OF_DIAMONDS)
            {
                if(AMOUNT_OF_CLUBS==4)
                {
                    DECISION = "1D";
                }
                else if (AMOUNT_OF_CLUBS == 3)
                {
                    DECISION = "1C";
                }

            }
            else
            {
                if (AMOUNT_OF_CLUBS > AMOUNT_OF_DIAMONDS)
                {
                    DECISION = "1C";
                }
                else if (AMOUNT_OF_CLUBS < AMOUNT_OF_DIAMONDS)
                {
                    DECISION = "1D";
                }
            }
        }

        //20 --> 21 points recommends 2 no trumps
        else if(TOTAL_POINTS >=20 && TOTAL_POINTS <=21)
        {
            DECISION = "2 NT";
        }

        //else just do 2C
        else
        {
            DECISION = "2C";
        }
    }

    //If you have an unbalanced hand
    else if (balanced == false)
    {
        //Recommend a pass if you have  0 --> 12 points
        //and none of these rules follow
        if (TOTAL_POINTS >= 0 && TOTAL_POINTS <= 12)
        {
            DECISION = "PASS";

            //Calculate if you have two suits with 6 cards
            //If you only have one suit with 6 cards, they have
            //their own recommendations
            if (AMOUNT_OF_DIAMONDS == 6)
            {
                DECISION = "2D";
                SUIT_COUNT++;

            }
            if (AMOUNT_OF_SPADES == 6)
            {
                DECISION = "2S";
                SUIT_COUNT++;
            }
            if (AMOUNT_OF_HEARTS == 6)
            {
                DECISION = "2H";
                SUIT_COUNT++;
            }
            if (AMOUNT_OF_CLUBS == 6)
            {
                DECISION = "PASS";
                SUIT_COUNT++;
            }

            //if you end up with two suits of 6,
            //this algorithm will recomment the highest value
            //of the suits you have 6 cards of
            if (SUIT_COUNT ==2)
            {
                if (AMOUNT_OF_CLUBS == 6)
                {
                    DECISION = "2C";
                }
                else if (AMOUNT_OF_DIAMONDS == 6)
                {
                    DECISION = "2D";
                }
                else if (AMOUNT_OF_HEARTS == 6)
                {
                    DECISION = "2H";
                }
                else
                {
                    DECISION = "2S";
                }
            }
            //recommendations for having 7 of a suit
            else if (AMOUNT_OF_CLUBS == 7)
            {
                DECISION = "3C";
            }
            else if (AMOUNT_OF_SPADES == 7)
            {
                DECISION = "3S";
            }
            else if (AMOUNT_OF_DIAMONDS == 7)
            {
                DECISION = "3D";
            }
            else if (AMOUNT_OF_HEARTS == 7)
            {
                DECISION = "3H";
            }

            //recommendations for having 8 of a suit
            else if (AMOUNT_OF_CLUBS == 8)
            {
                DECISION = "4C";
            }
            else if (AMOUNT_OF_SPADES == 8)
            {
                DECISION = "4S";
            }
            else if (AMOUNT_OF_DIAMONDS == 8)
            {
                DECISION = "4D";
            }
            else if (AMOUNT_OF_HEARTS == 8)
            {
                DECISION = "4H";
            }

        }


        //from 13 to 21 points, bid a 1-level suit
        else if (TOTAL_POINTS >= 13 && TOTAL_POINTS <= 21)
        {
            //Bid 1 of the longest suits
            if (AMOUNT_OF_CLUBS > AMOUNT_OF_DIAMONDS && AMOUNT_OF_CLUBS > AMOUNT_OF_HEARTS && AMOUNT_OF_CLUBS > AMOUNT_OF_SPADES)
            {
                DECISION = "1C";
            }
            else if (AMOUNT_OF_DIAMONDS > AMOUNT_OF_HEARTS && AMOUNT_OF_DIAMONDS > AMOUNT_OF_CLUBS && AMOUNT_OF_DIAMONDS > AMOUNT_OF_SPADES)
            {
                DECISION = "1D";
            }
            else if (AMOUNT_OF_HEARTS > AMOUNT_OF_CLUBS && AMOUNT_OF_HEARTS > AMOUNT_OF_DIAMONDS && AMOUNT_OF_HEARTS > AMOUNT_OF_SPADES)
            {
                DECISION = "1H";
            }
            else if (AMOUNT_OF_SPADES > AMOUNT_OF_CLUBS && AMOUNT_OF_SPADES > AMOUNT_OF_DIAMONDS && AMOUNT_OF_SPADES > AMOUNT_OF_HEARTS)
            {
                DECISION = "1S";
            }
            //if there are two suits of equal length, >= than 5, this code will bid the higher suit
            if ((AMOUNT_OF_CLUBS >= 5 && AMOUNT_OF_DIAMONDS >= 5) || (AMOUNT_OF_CLUBS >= 5 && AMOUNT_OF_HEARTS >= 5)
                    || (AMOUNT_OF_CLUBS >= 5 && AMOUNT_OF_SPADES >= 5) || (AMOUNT_OF_DIAMONDS >= 5 && AMOUNT_OF_HEARTS >= 5)
                    || (AMOUNT_OF_DIAMONDS >= 5 && AMOUNT_OF_SPADES >= 5) || (AMOUNT_OF_HEARTS >= 5 && AMOUNT_OF_SPADES >= 5))
            {

                if (AMOUNT_OF_CLUBS == AMOUNT_OF_DIAMONDS)
                {
                    DECISION = "1D";
                }
                else if (AMOUNT_OF_CLUBS == AMOUNT_OF_HEARTS)
                {
                    DECISION = "1H";
                }
                else if (AMOUNT_OF_CLUBS == AMOUNT_OF_SPADES)
                {
                    DECISION = "1S";
                }
                else if (AMOUNT_OF_DIAMONDS == AMOUNT_OF_HEARTS)
                {
                    DECISION = "1H";
                }
                else if (AMOUNT_OF_DIAMONDS == AMOUNT_OF_SPADES)
                {
                    DECISION = "1S";
                }
                else if (AMOUNT_OF_HEARTS == AMOUNT_OF_SPADES)
                {
                    DECISION = "1S";
                }
            }
            //if the longest suit has a length of 4, and it's not the only one with that length, this
            //code will bid the lowest value suit of them
            else if(AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_DIAMONDS == 4)
            {
                DECISION = "1D";
            }
            else if (AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_HEARTS == 4)
            {
                DECISION = "1J";
            }
            else if (AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION ="1S";
            }
            else if (AMOUNT_OF_DIAMONDS == 4 && AMOUNT_OF_HEARTS == 4)
            {
                DECISION = "1H";
            }
            else if (AMOUNT_OF_DIAMONDS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION = "1S";
            }
            else if (AMOUNT_OF_HEARTS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION = "1S";
            }
            else if(AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_DIAMONDS == 4 && AMOUNT_OF_HEARTS == 4)
            {
                DECISION = "1H";

            }
            else if (AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_DIAMONDS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION = "1S";
            }
            else if (AMOUNT_OF_CLUBS == 4 && AMOUNT_OF_HEARTS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION = "1S";
            }
            else if (AMOUNT_OF_DIAMONDS == 4 && AMOUNT_OF_HEARTS == 4 && AMOUNT_OF_SPADES == 4)
            {
                DECISION = "1S";
            }
        }
        //22 or more points, bid 2c
        else if (TOTAL_POINTS >= 22)
        {
            DECISION = "2C";
        }

    }
    return DECISION;
}


/** \brief
 * Overload of the ostream to output each
 * hand as a string.
 */
ostream& operator<<(ostream& out, Hand& hand)
{
    //Calling my private method for each suit in a hand
    string clubsOutput =hand.convertToString(CLUBS, "Clubs");
    string heartsOutput =hand.convertToString(HEARTS, "Hearts");
    string diamondsOutput =hand.convertToString(DIAMONDS, "Diamonds");
    string spadesOutput =hand.convertToString(SPADES, "Spades");

    //Outputs each suit in the hand
    out << spadesOutput << endl << heartsOutput << endl << diamondsOutput << endl << clubsOutput;
    //Outputs the card points
    out << endl << hand.HIGH_CARD_POINTS << " HCP, " << hand.LOW_CARD_POINTS << " LP, Total = " << (hand.HIGH_CARD_POINTS+hand.LOW_CARD_POINTS);
    return out;
}

/** \brief
 * Converts each card object in the hand
 * into one string
 *Returns: a whole suit in a hand as a string
 */
string Hand::convertToString(int suit, string stringSuit)
{
    string stringRank;
    string suitString;
    string finalOutput;
    string suitOutput = stringSuit + "   : ";

    set<Card*>::iterator it;

    for (it = handArray[suit].begin(); it != handArray[suit].end(); it++)
    {
        Card card = **it;

        if ((Suit)card.getSuit() == CLUBS)
        {
            suitString = "C";
        }
        else if ((Suit)card.getSuit() == HEARTS)
        {
            suitString = "H";
        }
        else if ((Suit)card.getSuit() == DIAMONDS)
        {
            suitString = "D";
        }
        else if ((Suit)card.getSuit() == SPADES)
        {
            suitString = "S";
        }

        if ((Rank)card.getRank() == TWO)
        {
            stringRank = "2";
        }
        else if ((Rank)card.getRank() == THREE)
        {
            stringRank = "3";
        }
        else if ((Rank)card.getRank() == FOUR)
        {
            stringRank = "4";
        }
        else if ((Rank)card.getRank() == FIVE)
        {
            stringRank = "5";
        }
        else if ((Rank)card.getRank() == SIX)
        {
            stringRank = "6";
        }
        else if ((Rank)card.getRank() == SEVEN)
        {
            stringRank = "7";
        }
        else if ((Rank)card.getRank() == EIGHT)
        {
            stringRank = "8";
        }
        else if ((Rank)card.getRank() == NINE)
        {
            stringRank = "9";
        }
        else if ((Rank)card.getRank() == TEN)
        {
            stringRank = "10";
        }
        else if ((Rank)card.getRank() == JACK)
        {
            stringRank = "J";
        }
        else if ((Rank)card.getRank() == QUEEN)
        {
            stringRank = "Q";
        }
        else if ((Rank)card.getRank() == KING)
        {
            stringRank = "K";
        }
        else if ((Rank)card.getRank() == ACE)
        {
            stringRank = "A";
        }

        finalOutput += stringRank + suitString + " ";
    }
    return suitOutput + finalOutput;
}


