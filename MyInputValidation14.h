/** MyInputValidation14.h
 *	
 *	A re-useable library of input validation functions for CPRG 4202
 *	   
 *	@author		Thom MacDonald
 *	@version	2014.03
 *	@since		20 Sep 2014
 *	@see		Bronson, G. (2012). A First Book of C++ (4th ed.). Boston, MA: Course Technology.
 */

#ifndef _MY_INPUT_VALIDATION_14

#define _MY_INPUT_VALIDATION_14

#include <iostream> // for cin/cout/cerr
#include <cstdlib>	// for atod
#include <string>	// for string
#include <climits>  // for limits of a int INT_MIN and INT_MAX
#include <cfloat>   // for limits of a double DBL_MIN and DBL_MAX

using namespace std;

namespace myValidation14
{
	/**	GetValidDouble function
	 * Gets a valid double value from the console with range checking
	 *
	 * @param  prompt A string to display to the user to prompt input; defaults to "".
	 * @param  MIN the minimum value the user may enter; defaults to the minimum double.
	 * @param  MIN the minimum value the user may enter; defaults to the maximum double.
	 * @return A validated double input by the user.
	 */	
	 double GetValidDouble(string prompt = "", const double MIN = -DBL_MAX, const double MAX = DBL_MAX);

	/**	GetValidInteger function
	 * Gets a valid int value from the console with range checking
	 *
	 * @see GetValidDouble()
	 *
	 * @param  prompt A string to display to the user to prompt input; defaults to "".
	 * @param  MIN the minimum value the user may enter; defaults to the minimum int.
	 * @param  MIN the minimum value the user may enter; defaults to the maximum int.
	 * @return A validated integer input by the user.
	 */
	 int GetValidInt(string prompt = "", const int MIN = INT_MIN, const int MAX = INT_MAX);
	 
	 /** IsValidDouble function
	 * Checks a std::string to see if it can be converted to a numeric base 10 value
	 *
	 * @param  text - a string to check.
	 * @return true if the text string can be converted to a numeric, false if not.
	 */
	 bool IsValidNumeric(string text);

	 // GetValidDouble defintion
	 double GetValidDouble(string prompt, const double MIN, const double MAX)
	 {
	       
	       double validNumber = 0.0; // stores the user input as a numeric value
	       string userInput;         // holds the user input as typed in.
	       
	       cout << prompt; 
	       cin >> userInput;       // try to get input
	       
	       // if the user input is numeric
	       if(IsValidNumeric(userInput))
	       {
	      		// convert the user input from a string to a double
				validNumber = atof(userInput.c_str());
				
				// if value is outside range...
				if(validNumber < MIN || validNumber > MAX)
		        {
		           // report the problem to the user.
		           cerr << "\nInvalid input. Please try again and enter a value between "
		                << MIN << " and " << MAX << ".\n";
		           // Try again by call the function again (recursion)
		           validNumber = GetValidDouble(prompt, MIN, MAX);
		        }
	       }
	      
	       else // the user input was not a valid numeric
	       {
		       // report the problem to the user.
	           cerr << "\nInvalid input. Please try again and enter a numeric value.\n";
	           // Try again by calling the function again (recursion)
	           validNumber = GetValidDouble(prompt, MIN, MAX);
	       } 
	       
	       return validNumber; // returns a valid value to the calling function.
	 }

	 // GetValidInt defintion
	 int GetValidInt(string prompt, const int MIN, const int MAX)
	 {
	       double validNumber = 0.0; // holds the user input
	       validNumber = GetValidDouble(prompt, MIN, MAX); // get a number
	       if((int) validNumber < validNumber) // if the value is not a whole number...
	       {
	           cerr << "\nInvalid input. Please try again and enter a whole number.\n";
	           // Try again by calling the function again (recursion)
	           validNumber = GetValidInt(prompt, MIN, MAX); 
	       }
	       return (int) validNumber; // returns a valid value to the calling function.
	 }

	 // IsValidNumeric defintion
	 bool IsValidNumeric(string text)
  	 {
	    bool valid = true;
	    bool digitFound = false;
	    bool decimalFound = false;
	    int index = 0;
	    
	    // Prechecks
	    if(!text.length() <= 0) // not an empty string
	    {
	        if((text.at(0) == '+' || text.at(0) == '-')) // signed
	        {
	             index++; // skip to the next index
	        }
	        for(;valid && index < text.length();index++) // loop while valid and still have digits
	        {
	            if(text.at(index) == '.') // decimal
	            {
	                if(decimalFound) // already found one decimal
	                   valid = false; // not valid
	                else
	                   decimalFound = true; // first decimal found
	            }
	            else if(!isdigit(text.at(index))) // not a digit
	               valid = false; // invalid
	            else
	               digitFound = true; // found at least one digit             
	        }
	    }
	    else
	         valid = false; // empty string is invalid
	    
	    return valid && digitFound; 
  	 } 

}
#endif
