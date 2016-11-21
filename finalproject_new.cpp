/*	finalproject.cpp
 *   
 *	@author:		Emilie Sharkey, Sophia Wajdie, Parth Patel
 *	@date:			December 10, 2015
 *	@description:	A C++ program created as a final project submission for OOP-3200. 
 *					This program impliments the concepts and chapters learnt throughout
 *					OOP-3200 such as encapsulation, abstraction, polymorphism, and 
 *					inheritance. The program itself simulates the popular Western 
 *					card game called Blackjack. The game objective is to get two cards
 *					that equal 21 without exceeding 21. You and other players are
 *					attempting to beat the dealer. For more details, run the program and 
 *					and key in "y/Y" for a Blackjack overview. 
 *					
 *
 *	@see		Bronson, G. (2012). A First Book of C++ (4th ed.). Boston, MA: Course Technology.
 *  @see		OLG. "Responsible Gaming." Fallsview Casino Resort, About. Knowyourlimit.ca, n.d. Web. 09 Dec. 2015.
 *  @see		http://www.cplusplus.com/doc/tutorial/files/
 *  @see		http://stackoverflow.com/questions/23184061/reading-from-a-text-file-best-way-to-store-data-c
 *  @see		https://www.youtube.com/watch?v=EhVMtFRk27Y
 *
 */

#include <iostream>		
#include <stdexcept>
#include <iomanip>
#include "StandardPlayingCard.h"
#include "StandardDeck.h"
#include "CardHand.h"
#include "MyInputValidation14.h"
#include <time.h>
#include <fstream>
#include <map>
#include <sstream>   

using namespace std;
using namespace myValidation14;

const int DOUBLING_BET = 2 ; //Constant declaration for double down multiple
const int BET_AND_WINNINGS = 2 ; //Constant declaration for bets and winnings 
const int BLACKJACK = 21; //Constant declaration for Blackjack call
const int MAXIMUM_AGE = 125; //Constant declaration for maximum estimated age
const int MINIMUM_AGE = 0; //Constant declaration for absolute minimum age
const int MINIMUM_AGE_ONTARIO = 19; //Constant declaration for legal gambling age in Ontario
const int MINIMUM_CHIP= 0; //Constant declaration for minimum number of chips possible
const string BLACKJACK_HEADER = "////////////////////////////////////////////////////\n   WELCOME TO BLACKJACK GAME  \n////////////////////////////////////////////////////\n   "; 	
const string CHIPS_UPPERCASE = "C"; //Constant declaration for user input for chips
const string CHIPS_LOWERCASE = "c"; //Constant declaration for user input for chips
const string DOUBLE = "3"; //Constant declaration for double's menu option
const string END_CAPITALIZED = "N"; //Constant declaration for user input to end
const string END_LOWER_CASE = "n";	//Constant declaration for user input to end
const string HIT = "1"; //Constant declaration for hit's menu option
const string MANUAL_UPPERCASE = "M"; //Constant declaration for user input to manually bet
const string MANUAL_LOWERCASE = "m"; //Constant declaration for user input to manually bet
const string NO_CAPITALIZED = "N"; //Constant declaration for user input to deny
const string NO_LOWER_CASE = "n"; //Constant declaration for user input to deny
const string STAND = "2"; //Constant declaration for stand's menu option
const string START_CAPITALIZED = "Y"; //Constant declaration for user input to accept
const string START_LOWER_CASE = "y"; //Constant declaration for user input to accept
const string STATS = "stats.txt"; //Constant declaration for file stats.txt access
const string SURRENDER ="4"; //Constant declaration for surrender's menu option
const string YES_CAPITALIZED = "Y"; //Constant declaration for yes 
const string YES_LOWER_CASE = "y"; //Constant declaration for yes
const string LOG_FILE = "log.txt"; //Constant declaration for file log.txt access

int bet = 0; //Integer variable declaration for
int chipsAmount = 1000; //Integer variable declaration for
int playerAge = 0; //Integer variable declaration for
map<string, int> playerInformation; //Initializes a map and stores it into an integer
string enteredName = ""; //String variable declaration for inputted name
string pastGameInput; //String variable declaration for previous game log
string playerName = ""; //String variable declaration for the player's custom name
string player = ""; //String variable declaration for a player
string rulesCheck = ""; //String variable declaration for checking rules
string userInput = ""; //String variable declaration for user input
string problem = ""; //String variable declaration for errors

void blackJack(); //Declare and initialize the method for achieving Blackjack
void checkBust(); //Declare and initialize the method for checking who exceeds 21
void checkWhoWins(); //Declare and initialize the method for checking who wins
void Double(); //Declare and initialize the method for double down
void Hit(); //Declare and initialize the method for hitting
void playHand(); //Declare and initialize the method for playing a hand
void Stand(); //Declare and initialize the method for standing 
void Surrender(); //Declare and initialize the method for surrendering 
void Chips(); //Declare and initialize the method for set of chips
void updateLog(string message); //Declare and initialize the method for stats log updating
void displayGamingControlAct(); //Declare and initialize the method for overview of age regulations
void displayRules(); //Declare and initialize the method for displaying Blackjack rules
void displayOverview(); //Declare and initialize the method for overview of Blackjack
 
CardHand user; //Call on the class CardHand for user
CardHand dealer; //Call on the class CardHand for dealers

int main()
{ 
	system("color 02"); //Customize the colour of font in console
	
	try
	{
		//Display the predefined constant for header in console 
		cout <<  BLACKJACK_HEADER; 
		 
		//Ask user for his/her age  
		playerAge =  GetValidInt("Please enter your age: ", MINIMUM_AGE, MAXIMUM_AGE);
		
		//Validate if user's age is greater than Ontario's minimum legal gambling age
		if (playerAge >= MINIMUM_AGE_ONTARIO) 	
		{
 			//As long as user is over the minimum legal gambling age
			while(rulesCheck!= YES_CAPITALIZED && rulesCheck !=YES_LOWER_CASE  && rulesCheck != NO_LOWER_CASE && rulesCheck != NO_CAPITALIZED)
			{ 
				//Ask the user if he/she wants an overview of Blackjack and it's rules
				cout << endl << "Would you like the rules of how to play blackjack? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ")? " ;
				
				//Store user input into the variable rulesCheck
				cin >> rulesCheck;
				
				//If user inputs something that is not Y/y or N/n
				if(rulesCheck!= YES_CAPITALIZED && rulesCheck !=YES_LOWER_CASE  && rulesCheck != NO_LOWER_CASE && rulesCheck != NO_CAPITALIZED)
				{
					//Display the error in console
					cout << endl << "ERROR: Please enter Y or N! " << endl;
				}
				
				//If user accepts the rules and overviews by inputting Y/y
				else if( rulesCheck== YES_CAPITALIZED || rulesCheck==YES_LOWER_CASE)
				{	
					//Call on displayOverview method to display Blackjack Overview
					displayOverview();
					
					//Call on displayRules method to display Blackjack Rules
					displayRules();
				} 
			}		
			cout << endl ;
		
		//Request user to enter a name
		cout << "Please enter your name: ";
		
		//Store user input into the variable enteredName
		cin >> enteredName;
				
		//Store enteredName as a log entry in PlayerStats			
		ifstream PlayerStats(STATS.c_str());		
			
			//If PlayerStats file is open
			if(PlayerStats.is_open())
			{	 
				while (PlayerStats.good())  
				{	
					//Save playerName to PlayerStats
					PlayerStats >> playerName ;
					
					//Save playerInformation under the playerName in PlayerStats
					PlayerStats >> playerInformation[playerName];
					
					//Retrieve the stats for the player from PlayerStats
					getline(PlayerStats, playerName);
				}
				
				//If user has previous game history
				if (!(playerInformation.find(enteredName) == playerInformation.end()))
				{
					//Ask user if he/she wants to continue from last game stats
					cout << endl << "Would you like to continue where you last left off? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ") " ;
				 	
				 	//Store user input into variable pastGameInput
					cin >> pastGameInput;
					
					//If pastGameInput is Y/y 
					if(pastGameInput == YES_CAPITALIZED || pastGameInput == YES_LOWER_CASE)
					 {
					 	//Use chipAmounts the user had previously
					 	chipsAmount =  playerInformation[enteredName]; 
					 }
				}
				
				//Update user game history
	 	 		updateLog("//////////////////////////////////////////////////////////////////////// \n			Player Name :  " + enteredName + "\n //////////////////////////////////////////////////////////////////////// \n");
				
				//Call on the method playHand to start the round
				playHand();
				
				//Close the PlayerStats file
				PlayerStats.close();
			}
			
			else
		 	{
		 		//If there is a problem with accessing the log file, display the error
		 		cout << endl << "Log file was unable to open. Progam will now terminate."; 
		 	}
					
			}
	 	
		else 
		{
			//Call on the method displayGamingControlAct to display the age restriction law
		 	displayGamingControlAct(); 
		}
	
	}
	
	catch(const exception& ex)
	{
		//Exception in main
		cerr << endl << ex.what() << endl;
	}
	
	// END-OF-PROGRAM
	cout << endl << endl;
	
	return 0;
	 
}

//Declare and initialize the method for hitting
void Hit()
{
	//Declare the string variable choice
	string choice;
	
	//Call on the method AddToHand
	user.AddToHand(); 
	//Display the text in the console
	cout << endl << "Player's Cards: " << endl ;
	//Display the astrik divider in the console
	cout << "******************************"<< endl ; 
	//Display from the method ShowCards
	cout << user.ShowCards() <<endl <<endl ;
	
	//Check if the user busts	
	checkBust();
	
	//Display menu options in the console
	cout << "Please select an option "<<endl
		 << "==============================" << endl
		 <<" "<< HIT << " - Hit"<<endl
		 <<" "<< STAND << " - Stand"<<endl
		 <<" "<< DOUBLE << " - Double Down"<<endl
		<<" " << SURRENDER <<  " - Surrender"; 
		
		//Loop over the available menu options
		while(choice != HIT && choice != STAND && choice != DOUBLE && choice != SURRENDER)
		{	 
			//Display a prompt for choice
			cout << endl << "Choice: "; 
			
			//Store user input in variable choice
			cin >> choice;
			
			//If user chooses to hit 
			if (choice == HIT)
			{ 
				//Call on Hit method
				Hit();
			}
			
			//If user chooses to stand
			else if (choice == STAND)
			{
				//Call on Stand method
				Stand();
			}
			
			//If user chooses to double
			else if (choice == DOUBLE)
			{
				//Verify user has enough chips to double
				if (chipsAmount > (bet*DOUBLING_BET))
				{
					//Call on Double method
					Double();
				}
					
					else 
					{
						//Call on Hit method
						Hit();
						
						//Display the error message in console
						cout << endl << "ERROR: TOO LITTLE CHIPS WAS PROCESSED AS A HIT." << endl;
					}
			} 
			
			//If user chooses to surrender
			else if (choice == SURRENDER)
			{	
				//Call on Surrender method
				Surrender();
			}
			
			//If user does not choose one of the valid options 
			else
			{
				//Display error message in console
				cout  << "ERROR: Please select " << HIT <<", " << STAND << ", " << DOUBLE << ", or " << SURRENDER << "!" ;
			}
	}
}

//Declare and initialize the method for standing
void Stand()
{
	//Declare the constant DEALER_STOP
	const int DEALER_STOP = 17 ; 
	
	//Clear the console
	system("cls"); 
	
	//Display the header
	cout << BLACKJACK_HEADER;
	//Display Player's Cards message
	cout << endl << "Player's Cards: " << endl ;
	//Display astrik divider
	cout << "******************************"<< endl ; 
	//Call on method ShowCards to display drawn cards
	cout << user.ShowCards() << endl;
	
	//Display Dealer's Cards message
	cout << "Dealer's Cards: "  <<endl;
	//Display astrik divider
	cout << "******************************"<< endl;
	//Call on method ShowCards to display drawn cards 
	cout <<endl<< dealer.ShowCards() <<endl;
	
	while (dealer.GetPoints() < DEALER_STOP)
	{
		//Call on method AddToHand for the dealer
		dealer.AddToHand(); 
		//Display Dealer's hit message
		cout << "Dealer Hit: " << endl ;  
		//Display line divider
		cout << "======================" << endl; 
		//Call on method ShowCards to display drawn cards
		cout <<endl<< dealer.ShowCards() <<endl;
		//Check if dealer busts
		checkBust();
	}
	
	//Call on method checkWhoWins to check if user beats dealer
	checkWhoWins();
	
	//Call on playHand method to play a hand
	playHand();
}

//Declare and initialize the method for double down
void Double()
{
	//Declare the integer testBet store bet times 2
	int testBet = bet*DOUBLING_BET;
	//Declare the integer testchipsAmount to store chipsAmount
	int testchipsAmount = chipsAmount; 
	
	//If user does not have enough funds to double
	if (testBet > testchipsAmount )
	{	
		//Display error message in console
		cout << endl <<  "ERROR: Due to insufficent funds to double was processed as a hit.";
		//Call on Hit method to get another card
		Hit();	
	}
	
	else
	{
		chipsAmount -= bet;
		//removes inital bet
		bet += bet;
		//adds the inital bet to bet
		user.AddToHand();
		//run a hit
		cout << user.ShowCards() <<endl <<endl ;
		//calls the showcards() 
		blackJack();	
		//checks for blackjack
		checkBust();
		//checks for bust
		Stand();
		//stands 
	}
	
}

//Declare and initialize the method for surrendering
void Surrender()
{
	//Clear the console
	system("cls"); 

	//Display the header
	cout << BLACKJACK_HEADER;

	//Divide the bet by the winnings and store it in variable chipsAmount
 	chipsAmount += (bet/BET_AND_WINNINGS);

	//Divide the bet by the winnings and deduct it from variable bet
 	bet -= (bet/BET_AND_WINNINGS);

	//Display the informative message
	cout << endl << "PLAYER HAS SURRENDER. HALF YOUR BET HAS BEEN RETURNED. " << endl; 

	//Call on the playHand method
	playHand();
}

//Declare and initialize the method for set of chips
void Chips()
{	
				const int MINIMUM_BET = 1; //Constant declaration for minimum bet
				const int MINIMUM_CHIP = 0; //Constant declaration for minumum chips
				const int CHIP_ONE = 1; //Constant declaration for single bet chips
				const int CHIP_FIVE = 5; //Constant declaration for small bet chips
				const int CHIP_TWENTY_FIVE = 25; //constant integer declaration for $25 chips
				const int CHIP_ONE_HUNDRED = 100; //constant integer declaration for $100 chips
				const int NUMBER_CHIPS = 4; //constant integer declaration for number of chips
				
				int userStored [NUMBER_CHIPS]; //int array for storing user inputted chip information
				int chipArray [NUMBER_CHIPS] = {CHIP_ONE, CHIP_FIVE, CHIP_TWENTY_FIVE, CHIP_ONE_HUNDRED };
				//array storing the different type of chip values
				string chipName [NUMBER_CHIPS] = {"Number of $1 chips: ", "Number of $5 chips: ", "Number of $25 chips: ", "Number of $100 chips: " };
				//string array prompting user to input different number of each chip 
				int testChipsAmount = chipsAmount; 
				//int storing the amount 
				int calculateTotalChips = 0;
				string betCheck ;
				string typeBet = ""; 
				int maximum = 0; 
				int testBet ; 
				
				if(chipsAmount > MINIMUM_BET)
				{
			
					system("cls");
					
				cout << BLACKJACK_HEADER; 
				stringstream ss;
				ss << chipsAmount;
				string chips = ss.str();
				updateLog( enteredName + " started game with " + chips + " chips.");	
				while(betCheck != YES_CAPITALIZED && betCheck !=YES_LOWER_CASE  && betCheck  != NO_LOWER_CASE && betCheck != NO_CAPITALIZED )
				{	
					
					cout << endl << "You have $" << chipsAmount <<"." <<endl;
					cout << endl << "Would you like to bet manually or with chips? ("<< CHIPS_UPPERCASE<<"/" <<MANUAL_UPPERCASE  <<")";  
					while(typeBet  != CHIPS_UPPERCASE && typeBet  != CHIPS_LOWERCASE && typeBet !=MANUAL_UPPERCASE && typeBet !=MANUAL_LOWERCASE)
					{
						
					cin >> typeBet;
					
					if(typeBet  != CHIPS_UPPERCASE && typeBet  != CHIPS_LOWERCASE && typeBet !=MANUAL_UPPERCASE && typeBet !=MANUAL_LOWERCASE)
					{
						cout << "ERROR: PLEASE SELECT "<< CHIPS_UPPERCASE<<" OR " <<MANUAL_UPPERCASE  << ": "; 
						cin >> typeBet;	
					}
					}
					if (typeBet == CHIPS_UPPERCASE || typeBet == CHIPS_LOWERCASE  )
					{
							while(betCheck  != YES_CAPITALIZED && betCheck !=YES_LOWER_CASE && chipsAmount != 0 )
						{
							
						int testChipsAmount = chipsAmount; 
						testBet = 0; 
						
						cout << endl << "You have $" << chipsAmount <<"." <<endl;
				  	
						for(int chipsInputted= 0; chipsInputted < NUMBER_CHIPS; chipsInputted++ )
						{
							 
							maximum = testChipsAmount /  chipArray[chipsInputted]; 
							
							userStored[chipsInputted] = GetValidInt(chipName [chipsInputted], MINIMUM_CHIP , maximum); 
							
							calculateTotalChips = (userStored[chipsInputted] * chipArray[chipsInputted]); 
							
							testChipsAmount	-= calculateTotalChips ; 
							
							testBet+= calculateTotalChips; 
							
							if (testChipsAmount==MINIMUM_CHIP )
							{
								cout << endl << "Maximum amount of chips have been reached" << endl;
								chipsInputted = NUMBER_CHIPS;
							}
  
						}
			  
						cout << endl << "Your Bet Amount is : " << testBet << endl;
							
								cout << endl << "Is this correct? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ") ";
						
								cin >> betCheck; 
							
								if(betCheck  != YES_CAPITALIZED && betCheck != NO_CAPITALIZED && betCheck !=YES_LOWER_CASE && betCheck  != NO_LOWER_CASE)
								{
									cout << endl << "ERROR ! Please type " << YES_CAPITALIZED << " or "<< NO_CAPITALIZED  << endl;
									cout << endl << "Your Bet Amount is : " << bet << endl;
									cout << endl << "Is this correct? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ") ";
									cin >> betCheck; 
							}
								
						}
						bet = testBet; 
					
					}
					if (typeBet == MANUAL_UPPERCASE || typeBet == MANUAL_LOWERCASE)
					{
							while(betCheck  != YES_CAPITALIZED && betCheck !=YES_LOWER_CASE && chipsAmount != 0 )
						{
						cout << endl << "Enter your bet (You have $" << chipsAmount <<"): ";
						
						bet = GetValidInt("", MINIMUM_BET, chipsAmount);
						

						cout << endl << "Your Bet Amount is : " << bet << endl;
							
								cout << endl << "Is this correct? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ") ";
						
								cin >> betCheck; 
							
								if(betCheck  != YES_CAPITALIZED && betCheck != NO_CAPITALIZED && betCheck !=YES_LOWER_CASE && betCheck  != NO_LOWER_CASE)
								{
									cout << endl << "ERROR ! Please type " << YES_CAPITALIZED << " or "<< NO_CAPITALIZED  << endl;
									cout << endl << "Your Bet Amount is : " << bet << endl;
									cout << endl << "Is this correct? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << ") ";
									cin >> betCheck; 
								}
								
								
						}
					
					}
					}
				
				chipsAmount-=bet;
				stringstream sbet;
				sbet << bet;
				string betChips = sbet.str();
				updateLog( enteredName + "'s bet amount is  " + betChips);
					
			}
			else
					{
						//Display the error message in console
						cout << endl << "*************************************************************" << endl
					     <<"Sorry!! You ran out of chips!! Please restart the game"<<endl
					     <<"*************************************************************"<<endl<<endl<<endl;
					    exit(0);
					}
}


void blackJack()
{
	if( user.GetPoints() == BLACKJACK &&  dealer.GetPoints() == BLACKJACK)
	{
		system("cls");
		cout << BLACKJACK_HEADER;
		cout << endl << "Player's Cards: " << endl ;
		cout << "******************************"<< endl ; 
		cout << user.ShowCards() << endl;
	
		cout << "Dealer's Cards: "  <<endl;
		cout << "******************************"<< endl; 
		cout <<endl<< dealer.ShowCards() <<endl;
		
		stringstream ss;
		ss << user.ShowCards()<<endl;
		ss << dealer.ShowCards()<<endl;
		
		
		updateLog( ss.str() + " User and Dealer had Tie with blackjack! \n" );
					
		cout << "WOW! Both Player and Dealer have blackjack! Looks like its a tie! "<<endl;
		chipsAmount += bet ;
		playHand();
		
	}
	
	else if( user.GetPoints() == BLACKJACK )
	{
		system("cls");
		cout << BLACKJACK_HEADER;
		cout << endl << "Player's Cards: " << endl ;
		cout << "******************************"<< endl ; 
		cout << user.ShowCards() << endl;
	
		cout << "Dealer's Cards: "  <<endl;
		cout << "******************************"<< endl; 
		cout <<endl<< dealer.ShowCards() <<endl;
		
		
		stringstream ss;
		ss << user.ShowCards()<<endl;
		ss << dealer.ShowCards()<<endl;
		
		
		updateLog( ss.str() + enteredName + " won with Blackjack!!  \n" );
		
				
		cout << "Congratulations!! You Won with Blackjack"<<endl;
		chipsAmount += bet * BET_AND_WINNINGS;
		playHand();
		
	}
	
	else if(dealer.GetPoints() == BLACKJACK )
	{
		system("cls");
		cout << BLACKJACK_HEADER;
		cout << endl << "Player's Cards: " << endl ;
		cout << "******************************"<< endl ; 
		cout << user.ShowCards() << endl;
	
		cout << "Dealer's Cards: "  <<endl;
		cout << "******************************"<< endl; 
		cout <<endl<< dealer.ShowCards() <<endl;
		
		
			stringstream ss;
		ss << user.ShowCards()<<endl;
		ss << dealer.ShowCards()<<endl;
		
		
		updateLog( ss.str() +" Dealer won with Blackjack!!  \n" );
		
		cout <<" OOHH! Dealer won with Blackjack"<<endl;
		
		playHand();
	}
	
}

void checkBust()
{
	if( user.GetPoints() > BLACKJACK)
	{
		cout << "OOPS!! You BUSTED! "<<endl;
		stringstream ss;
		ss << user.ShowCards()<<endl;
		ss << dealer.ShowCards()<<endl;
		
		
		updateLog( ss.str() + enteredName + " busted!!  \n" );
		
		playHand();
		
	}
	
	else if (dealer.GetPoints() > BLACKJACK)
	{
		
		stringstream ss;
		ss << user.ShowCards()<<endl;
		ss << dealer.ShowCards()<<endl;
		
		
		updateLog( ss.str() + enteredName + " won as Dealer Busted!!  \n" );
		
		cout<<"Woohoo! Dealer BUSTED!! "<<endl;
		chipsAmount += bet * BET_AND_WINNINGS;
		playHand();
	}
}


void checkWhoWins()
{
	int const GREAT_THAN_BLACKJACK = 22;  
	string const WON = "Woohoo!!! You Won!!"; 
	string const LOST = "Aahh!! You lost!";
	string const TIE = "It's a tie" ; 
	
	if( user.GetPoints() < GREAT_THAN_BLACKJACK )
	{
		
		if (user.GetPoints() > dealer.GetPoints())
		{
			cout << WON << endl;
			
			stringstream ss;
			ss << user.ShowCards()<<endl;
			ss << dealer.ShowCards()<<endl;
			updateLog( ss.str() + enteredName + " won !!  \n" );
		
			chipsAmount += bet * BET_AND_WINNINGS;
			
		}
		else if(user.GetPoints() < dealer.GetPoints())
		{
			cout << LOST <<endl;
				stringstream ss;
			ss << user.ShowCards()<<endl;
			ss << dealer.ShowCards()<<endl;
			updateLog( ss.str() + enteredName + " lost !!  \n" );
		

		}
		else if(user.GetPoints() == dealer.GetPoints())
		{
			cout << TIE <<endl;
			stringstream ss;
			ss << user.ShowCards()<<endl;
			ss << dealer.ShowCards()<<endl;
			updateLog( ss.str() + " It was a tie!!  \n" );
		
			chipsAmount += bet;
		
		}
	}

}

void playHand()
{
	const int MINIMUM_BET = 1; 

	const int NO_MORE_CARDS = 1;

	string betCheck = "";
	string choice = "";
	int cardsLeft = 0;
	
	StandardDeck cards;
	
	while (userInput != END_CAPITALIZED && userInput != END_LOWER_CASE && cardsLeft != NO_MORE_CARDS )
		{
			 
			cout << endl << "Shall we play a game? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << "): ";
			
			cin >> userInput;
			
			if(userInput==START_LOWER_CASE || userInput == START_CAPITALIZED) {
			
			Chips(); 
				
			user.Initialize();
				
			dealer.Initialize(); 
					
			system("cls");
					
			cout << BLACKJACK_HEADER;	

			cout << endl << endl <<  "The cards been dealt!"<< endl << endl << endl;
	
			cout<< setfill('-') << setw(40) << "-" << endl 
				<< setfill(' ') << setw(25) << "DEALER'S CARDS: " << endl << dealer.ShowCards(false) <<endl
				<< setfill('-') << setw(40) << "-" << endl
				<< setfill(' ') << setw(25) << "PLAYER'S CARDS: " << endl << user.ShowCards() << endl
				<< setfill('-') << setw(40) << "-" <<endl;
					
				blackJack();
					
				checkBust();
					
			 	cout << endl << "==========================================" << endl
				 	 << "||	Please Select on Option:	|| " << endl
					 << "==========================================" << endl
					 <<"||	"<< HIT <<" - Hit				||"<< endl
					 <<"||	"<< STAND <<" - Stand			||"<< endl
					 <<"||	" << DOUBLE << " - Double Down			||" << endl
					 <<"|| 	" << SURRENDER <<  " - Surrender			||"<<endl
					 << "==========================================" << endl;
					
				
					while(choice != HIT && choice != STAND && choice != DOUBLE && choice != SURRENDER )
					{
						
							cout << "Please enter your Choice: " ; 				
							cin >> choice;
							cout <<	endl << "=========================================="  << endl;
					
						if(choice == HIT)
						{
							Hit();
						} 
						
						else if (choice == STAND)
						{
							Stand();
			
						}
						
						else if (choice == DOUBLE)
						{
			
							Double(); 
		
						} 
						else if (choice == SURRENDER) 
						{
							
							Surrender();
						}
						
						else
						{
							//Display the error message in console
							cout << endl << "ERROR: Please option " <<  HIT << ", "<<  STAND << ", "  << DOUBLE << " or "<< SURRENDER <<"!" << endl ;
								
						}
				
					}
							//Ask user for another round
							cout << endl << "Shall we play a game? (" << YES_CAPITALIZED << "/"<< NO_CAPITALIZED  << "): ";
							cin >> userInput;
							
				}	
			
		//If user enters e/E
		else if(userInput == END_CAPITALIZED || userInput == END_LOWER_CASE)
		{
			//Display bye message
			cout <<"Bye Bye | Adios";
			
			//Update the log file
			updateLog( enteredName + " ended the game! Bye Bye  \n" );
		
			exit(0); 
			}
		
		else
		{
			//Display the error message in console
			cout <<endl << "ERROR ! Please type " << START_CAPITALIZED << " or "<< END_CAPITALIZED << "!"<<endl;
		}
				
		}
}

//Declare and initialize the method for stats log updating
void updateLog(string message)
{
	//Save the stats log file into the ofstream variable log
	ofstream log(LOG_FILE.c_str(), ios::out | ios::app);
	
	//If the log file is open
	if(log.is_open())
	{
		//Create variable of time_t
		time_t tim; 
		//Pass variable tim to time function
		time(&tim);  
		
		// This translates what was returned from time() into a readable format		
		log << endl 
			<< "********************************************************************"<<endl <<endl
			<< ctime(&tim) <<endl <<endl
			<< message <<endl <<endl
			<< "********************************************************************";
		
		//Close the log file. 
		log.close();
	}
		
		
	else
	{
		//Display the error message in the console
		cout << endl << "ERROR! Cannot update log file";
	}

	
}

//Declare and initialize the method for overview of age regulations
void displayGamingControlAct()
{
	//Declare the string getRegulations
    string getRegulations;
    //Open and save file in variable openFile
    ifstream openFile ("GamingControlAct.txt");
    
	//If openFile is open
	if(openFile.is_open())
    {
    	//Output a blank line
    	cout << endl;
    	
    	//If the file is opened and accessed successfully
        while(openFile.good())
        {
        	//Store file contents in variable getRegulations
        	cout << getRegulations << " " ;
            openFile >> getRegulations;
        }
        
        //Close the open file
        openFile.close();
        //Output a blank line
        cout << endl; 
        //Display a "Press any key to continue..." message
        system ("PAUSE");

    }
}

//Declare and initialize the method for displaying Blackjack rules
void displayRules()
{
	//Declare the string getRules
    string getRules;
    //Open and save file in variable openFile
    ifstream openFile ("rules.txt");
    
    //If openFile is open
    if(openFile.is_open())
    {
    	//Output a blank line
    	cout << endl;
        while(openFile.good())
        {
        	//Store file contents in variable getRules
        	cout << getRules << " " ;
            openFile >> getRules;
        }
        
        //Close the open file
        openFile.close();
        //Output a blank line
        cout << endl; 
        //Display a "Press any key to continue..." message
        system ("PAUSE");

    }
}

//Declare and initialize the method for overview of Blackjack
void displayOverview()
{
	//Declare the string getOverview
    string getOverview;
    //Open and save file in variable openFile
    ifstream openFile ("overview.txt");
    //If openFile is open
    if(openFile.is_open())
    {
    	//Output a blank line
    	cout << endl;
    	
    	//If the file is opened and accessed successfully
        while(openFile.good())
        {
        	//Store file contents in variable getOverview
        	cout << getOverview << " " ;
            openFile >> getOverview;
        }
        
        //Close the open file
        openFile.close();
        //Output a blank line
        cout << endl; 
        //Display a "Press any key to continue..." message
        system ("PAUSE");

    }
}
