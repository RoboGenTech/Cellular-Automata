/*****************************************************************
*  Project Name : A cellular automaton model                     *
*  Project Type : Assignment for CS2B (Submitted May 2, 2018)    * 
*  Language     : C++ Source file and output run                 *
*  By           : RG                                             *
******************************************************************/


#include <iostream>
#include <string>
using namespace std;

//global constant variable
static const char ASTERISK = '*';
static const char BLANK = ' ';
static const int CUT_IN_HALF = 2;
static const int MIN_SET_RULE = 0;
static const int MAX_SET_RULE = 255;
static const int TIME_RUNS = 100;

// --------------- main ---------------
int main()
{
   int rule;

   do
   {
      cout << "Enter a rule (" << MIN_SET_RULE << "-" 
         << MAX_SET_RULE << ") : ";
      cin >> rule;
   } while (rule < MIN_SET_RULE || rule > MAX_SET_RULE);

   // Initializing to create automaton with rule obtained as input
   Automaton
      aut(rule);
   
   cout << "start" << endl;
    
   //Iteratively displays the current generation using the method below
   for (int k = 0; k < TIME_RUNS; k++)
   {
      cout << aut.toStringCurrentGen() << endl;
      aut.propagateNewGeneration();
   }
    
   cout << " end" << endl;

   return 0;
}

//-----------------------class prototype-----------
class Automaton
{
private:
   static const int RULES_SIZE = 8;  // inputs of 0-255 will convert to upto 8-bit binary

   bool rules[RULES_SIZE];           // rule as a binary(0 1) array of size 8
   string thisGen;
   string extremeBit;          //bit, "*" or " ", implied everywhere "outside"
   unsigned int displayWidth;  //an odd number so it can be perfectly centered

public:
   static const int MAX_DISPLAY_WIDTH = 121;
   static const int DEFAULT_DISPLAY_WIDTH = 79;

   Automaton(int rule);       // Constructor Method
   
   //Setter Methods
   bool setRule(int newRule);
   void resetFirstGen();
   bool setDisplayWidth(int width);
   
   // Method to use the logic for checkRule per Cellular Automata systems of 
   // deriving nextGen based on adjascent neighbors for each cell
   void propagateNewGeneration();
   
   // Display formatting Method
   string toStringCurrentGen();
};

// ------------------- Automaton Class Definition --------------

//Invoked from Constructor- set the rule base on user's choice
bool Automaton::setRule(int newRule) {
   int result;
   const int checkRemainder = 2;
   if (newRule < MIN_SET_RULE || newRule > MAX_SET_RULE)
      return false;

   //Uses an algorithm to convert int to a binary 
   for (int i = 0; i < RULES_SIZE; i++) {
      result = newRule % checkRemainder;
      rules[i] = result;
      newRule /= CUT_IN_HALF;
   }
   return true;
}

//Invoked from constructor- set the first generation
void Automaton::resetFirstGen()
{
   thisGen = ASTERISK;
   extremeBit = BLANK;
}

//Invoked from Constructor - set the width to display the generation
bool Automaton::setDisplayWidth(int width) {
   if (width > MAX_DISPLAY_WIDTH || width % 2 == 0 || width < 0) {
      displayWidth = DEFAULT_DISPLAY_WIDTH;
      return false;
   }
   displayWidth = width;
   return true;
}

//constructor

Automaton::Automaton(int rule) {
   setRule(rule);
   resetFirstGen();
   setDisplayWidth(DEFAULT_DISPLAY_WIDTH);
}

//display method for the current generation
/*
  * Assuming the seed as a single asterisk surrounded by 
  * blanks(extremeBit) as added in the while loop, 
  * Seed generation is "...     	*    	... "
  * because initiated with thisGen as '*' 
*/

string Automaton::toStringCurrentGen()
{
   string combineString;

   combineString = thisGen;

   //if the string is less than display width, pad with extremebit
   while (combineString.length() < displayWidth) {
      combineString = extremeBit + combineString + extremeBit;
   }

   //if the string is over than display width, cut the string
   while (combineString.length() > displayWidth)
      combineString = combineString.substr(1, combineString.length() - 2);

   return combineString;
}


//method to calculate the new generation
 /*A binary ruleset rule[] was derived from algorithm (a binary string from input integer)
   A 3-bit number is read from left to right of gen (t -1) and thus derive the index as checkRule
   000 -> 0 001 -> 1 010 -> 2  011 -> 3 100 -> 4 101 -> 5 110 -> 6 111 ->7
   Next generation (gen t) is derived from the rules[checkRule] for this Automata
*/
void Automaton::propagateNewGeneration() {
   string nextGen = "";
   int checkRule; // to configure the states that comes from three cells that are adjascent neighbors
   thisGen = extremeBit + extremeBit + thisGen + extremeBit + extremeBit;

   for (unsigned int i = 0; i < (thisGen.length() - 2); i++) {
       
      checkRule = (((thisGen[i] == ASTERISK) ? 1 : 0) << 2) +
         (((thisGen[i + 1] == ASTERISK) ? 1 : 0) << 1) +
         ((thisGen[i + 2] == ASTERISK) ? 1 : 0);
       
      //nextgen based on rules set 
      if (rules[checkRule])
         nextGen += ASTERISK;
      else
         nextGen += BLANK;
   }
   thisGen = nextGen;
}

/* Program Output:

Display Width 79 is controlling the width of thisGen on console. 
Since it is text output so left blanks are shifted, but the pattern 
from the output can be seen in the output as generation progresses 
from line t to line t+1   

------------------Run 1: ------------------
Enter a rule (0-255) : 131
start
*
*
*  **
*  *
*  *  ***
*  *  * *
*  *  *    **
*  *  *  ***
*  *  *  * *  ***
*  *  *  *    * *
*  *  *  *  ***    **
*  *  *  *  * *  ***
*  *  *  *  *    * *  ***
*  *  *  *  *  ***    * *
*  *  *  *  *  * *  ***    **
*  *  *  *  *  *    * *  ***
*  *  *  *  *  *  ***    * *  ***
*  *  *  *  *  *  * *  ***    * *
*  *  *  *  *  *  *    * *  ***    **
*  *  *  *  *  *  *  ***    * *  ***
*  *  *  *  *  *  *  * *  ***    * *  ***
*  *  *  *  *  *  *  *    * *  ***    * *
*  *  *  *  *  *  *  *  ***    * *  ***    **
*  *  *  *  *  *  *  *  * *  ***    * *  ***
*  *  *  *  *  *  *  *  *    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  * *  ***    * *  ***    **
*  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    **
*  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    **
*  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    **
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
*  *  *  *  *  *  *  *  *  *  *  *  *  ***    * *  ***    * *  ***    * *  **
*  *  *  *  *  *  *  *  *  *  *  *  *  * *  ***    * *  ***    * *  ***    * *
*  *  *  *  *  *  *  *  *  *  *  *  *  *    * *  ***    * *  ***    * *  ***
end
Press any key to continue . . .
------------------Run 2: ------------------
Enter a rule (0-255) : 77
start
*
*
* * *
* * *
* * * * *
* * * * *
* * * * * * *
* * * * * * *
* * * * * * * * *
* * * * * * * * *
* * * * * * * * * * *
* * * * * * * * * * *
* * * * * * * * * * * * *
* * * * * * * * * * * * *
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
end
Press any key to continue . . .


*/
