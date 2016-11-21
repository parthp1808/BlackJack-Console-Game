/** StandardPlayingCard.h
 *	
 *	A class representing a standard playing card.   
 *
 *   
 *	@author		Emilie Sharkey, Sophia Wajdie, Parth Patel
 *	@date		2015-12-10
 *	@info		Used for building the card hands. 		
*			
*/


#ifndef _STD_CARD_HAND
#define _STD_CARD_HAND

#include <iostream>		
#include <stdexcept>
#include <sstream>
#include <string>
#include "StandardPlayingCard.h"
#include "MyInputValidation14.h"
#include "StandardDeck.h"

using namespace std;
using namespace myValidation14;

// Container class
class CardHand
{
	private:
		vector<StandardPlayingCard> myHand; 
		int myPoints = 0;		// the size of the c-array
		StandardDeck cards;
	public:
		CardHand(); // constructor

		~CardHand() 
		{ 
			myHand.clear(); 
			myHand.shrink_to_fit();
			
			} // destructor
		
	
		int GetPoints() const; // mySize accessor
		
		void Initialize();
		void AddToHand();
		void Clear();
		void CalculatePoints();
		string ShowCards() const;
		string ShowCards(bool) const;
	
		static const int DEFAULT_HAND_SIZE;	
}; 

const int CardHand::DEFAULT_HAND_SIZE = 2;

CardHand::CardHand()
{
	Initialize();
}

int CardHand::GetPoints() const
{
	
	//this->CalculatePoints();
	return myPoints;
}



// to initialize or re-initialize the object
void CardHand::Initialize()
{
	const int EMPTY = 0 ; 
	
	if(myHand.size() != EMPTY)
		myHand.clear();
		
	
	
	for(int counter = 0; counter < DEFAULT_HAND_SIZE; counter++)
	{
		myHand.push_back(cards.DrawRandomCard());
		
	}
	this->CalculatePoints();
	
	
}


void CardHand::AddToHand()
{
	myHand.push_back(cards.DrawRandomCard());
	this->CalculatePoints();
}

void CardHand::Clear()
{
	
	myHand.clear();
	
	
}

void CardHand::CalculatePoints()
{
	
	int temp = 0;	
	
	for(int i = 0; i < myHand.size();i++)
	{
		
		string hold = myHand[i].getRankString();
		if (hold == "Two")
		{
			temp+=2;	
		}
		
		else if( hold == "Three")
		{
			temp+=3;
		}
		
		else if( hold == "Four")
		{
			temp+=4;
		}
		else if( hold == "Five")
		{
			temp+=5;
		}
		else if( hold == "Six")
		{
			temp+=6;
		}
		
		else if( hold == "Seven")
		{
			temp+=7;
		}
		else if( hold == "Eight")
		{
			temp+=8;
		}
		else if( hold == "Nine")
		{
			temp+=9;
		}
		
		else if( hold == "Ten" || hold == "Jack" || hold == "Queen" || hold == "King")
		{
			temp+=10;
		}
		
		
		else if( hold == "Ace")
		{
			if (temp <= 10){
					temp+=11;
			} else {
				temp+=1;
			}
		
		}
		
	}
	
	myPoints = temp;
	
	
	
}

string CardHand::ShowCards() const
{
	
	stringstream output;

	output; 
	for(int counter = 0; counter < myHand.size();counter++)
	{
		output<<(string)myHand[counter] <<endl;
			
	}
	
	int point = GetPoints();
    output<<"Points: "<<point<<endl;
	return output.str();
	
}

string CardHand::ShowCards(bool flag) const
{
	stringstream output;
	int counter;
	output <<endl<<endl;
	if (flag == false)
	{
		counter = 1;
		output << "****** "<< endl;
	}
	else
	{
		counter = 0;
	}
	for(; counter < myHand.size();counter++)
	{
		output<< (string)myHand[counter] <<endl;
			
	}
	
	if(flag == true)
	{
	int point = GetPoints();
    output<<"Points: "<<point<<endl;
	}
	return output.str();
	
} 

#endif
