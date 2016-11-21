/** StandardDesk.h
 *	
 *	A class representing a standard deck
 *
 *   
 *	@author		Thom MacDonald
 *	@version	2014.02
 *	@since		Oct 2014
 *	@see		Bronson, G. (2012).  Chapter 10 Introduction to Classes. 
 *				  In A First Book of C++ (4th ed.). Boston, MA: Course Technology.
 *	@see		Classes.StaticMembers.Solution.cpp
*/

#ifndef _STD_CARD_DECK
#define _STD_CARD_DECK

#include <iostream>		
#include <stdexcept>
#include "StandardPlayingCard.h"
#include "MyInputValidation14.h"
#include <time.h>

using namespace std;
using namespace myValidation14;

// Container class
class StandardDeck
{
	private:
		StandardPlayingCard * myArray;  // pointer to a dynamically-allocated c-array 
		int mySize;		// the size of the c-array
		
	public:
		StandardDeck(); // constructor

		~StandardDeck() { delete [] myArray;} // destructor
		StandardDeck(const StandardDeck &source); // copy constructor
		StandardDeck& operator=(const StandardDeck &source); // assignment operator	
	
		int CardsRemaining() const {return mySize;} // mySize accessor
		virtual void Initialize(int size);
		string DebugString() const; // an accessor to show info about the state of the object
		
		void Resize(int newSize);	// re-sizing mutator
	    void Shuffle();				//shuffling the deck of cards


		StandardPlayingCard DrawNextCard();				//for removing card from front just like popfront
		StandardPlayingCard DrawRandomCard();			//for removing random card from random position
	static const int DECK_SIZE;	 						//constant value indicating total number of cards that is 52
	static const int RANDOM_LIMIT;	 					//value of random limit which is just used in loop to randomize 
}; 

const int StandardDeck::DECK_SIZE = 52;					//constant value indicating total number of cards
const int StandardDeck::RANDOM_LIMIT = 1000;			//value of random limit which is just used in loop to randomize 


//default constructor
StandardDeck::StandardDeck()
{
	//initializes to zero
	myArray = 0;
	//call the initialize function to load the cards
	Initialize(DECK_SIZE);
}

// to initialize or re-initialize the object
void StandardDeck::Initialize(int size)
{
	// if the pointer is not 0, memory has been allocated
	if(myArray != 0)
		// delete the existing memory
		delete [] myArray;
		
	// Allocate a new array dynamically on construction
	myArray = new StandardPlayingCard [size]; // may throw bad_alloc exception
	mySize = size; // set the size
	int i=0;
	// Loop to load the cards in sensible order
	for(int s = 0; s < StandardPlayingCard::MAX_SUIT+1; s++)
	{
		
		for(int r =0; r < StandardPlayingCard::MAX_RANK; r++ )
		{
			
			myArray[i].setSuit(s); 
			myArray[i].setRank(r+1); 
			i++;
		}
		
	}
	
}



// an accessor to show info about the state of the object	
string StandardDeck::DebugString() const
{
	stringstream debug;
	debug << "\n==================== DEBUG ====================" << endl
		  << "myArray: " << myArray << endl
		  << "mySize:  " << mySize << endl;
	for(int i = 0; i < mySize; i++)
	{
		debug << "[" << i << "]: " << (string) myArray[i] << endl;
	}

	debug << "\n===============================================" << endl;
	return debug.str();
}


// copy constructor
StandardDeck::StandardDeck(const StandardDeck &source)
{
	// Allocate a new array dynamically on construction
	mySize = source.mySize; // set the size
	myArray = new StandardPlayingCard [mySize]; // may throw bad_alloc exception
	// Initialize each element to the corresponding playing card in the source object
	for(int i = 0; i < mySize; i++)
		myArray[i] = source.myArray[i];
}

// assignment operator
StandardDeck& StandardDeck::operator=(const StandardDeck &source)
{
	delete [] myArray; // free up the old memory
	// Allocate a new array dynamically on construction
	mySize = source.mySize; // set the size
	myArray = new StandardPlayingCard [mySize]; // may throw bad_alloc exception
	// Initialize each element to the corresponding playing card in the source object
	for(int i = 0; i < mySize; i++)
		myArray[i] = source.myArray[i];
	
	return *this;
} 


// re-sizing mutator
void StandardDeck::Resize(int newSize)
{
	StandardPlayingCard * newArray = new StandardPlayingCard[newSize]; // throws bad_alloc on failure
	int elementsToCopy = (mySize < newSize)? mySize : newSize; // whichever is smaller
	
	// Copy each each existing playing card to the new array
	for(int i = 0; i < elementsToCopy; i++)
		newArray[i] = myArray[i];

	// Set the new size
	mySize = newSize;
	
	// Delete the old array
	delete [] myArray;
	
	// Set the myArray pointer to the new array
	myArray = newArray;
}



// for removing an element from the start
StandardPlayingCard StandardDeck::DrawNextCard()
{
	// If the container is empty, throw an error
	if(mySize <= 0)
		throw out_of_range("Cannot take out card from empty deck. ");
	// preserve the first value
	
	StandardPlayingCard card = myArray[0];
	
	// Shift all the existing element value forward by 1 spot:
	for(int moveTo = 0; moveTo < mySize - 1; moveTo++)
	{
		myArray[moveTo] = myArray[moveTo + 1];
	}
	
	// Make the container smaller by 1
	Resize(mySize - 1);
	// return the former last value
	return card;
}

//for removing random element
StandardPlayingCard StandardDeck::DrawRandomCard()
{
	// If the container is empty, throw an error
	if(mySize <= 0)
		throw out_of_range("Cannot take out card from empty deck. ");
	// preserve the random value
	srand (time(NULL));
	int i = rand() % mySize ; 
	
	StandardPlayingCard card = myArray[i];
	
	
	// Shift all the existing element value forward by 1 spot:
	for(int moveTo = i; moveTo < mySize - 1; moveTo++)
	{
		myArray[moveTo] = myArray[moveTo + 1];
	}
	
	// Make the container smaller by 1
	Resize(mySize - 1);
	// return the former last value
	return card;
}

//for shuffling the cards 
void StandardDeck::Shuffle()
{
	int i,one, two;
	//loop to swap two random cards multiple times
	for(i=0; i < RANDOM_LIMIT ;i++)
	{
		one = rand() % mySize; 
		two = rand() % mySize;
		StandardPlayingCard card = myArray[one];
		myArray[one] = myArray[two];
		myArray[two] = card;
		
	}
}

#endif
