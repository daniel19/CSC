/****************************************************************
 *                                                              *
 *     Program to draw 5 cards at random from a deck of 52,     *
 *  taking the cards "without replacement" in the deck, or by   *
 *  taking the cards "with replacement:" that is, each card     *
 *  that is drawn is put back into the deck, so that one draws  *
 *  randomly from a deck of 52 each time.                       *
 *                                                              *
 *  Author: David Hume                                          *
 *  Date of Creation: February 28, 2008                         *
 *                                                              *
 ****************************************************************/


#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;


int main ()
{
   bool    goAgain;
   char    response;

   bool    replace;

   bool    hasBeenDrawn[52];  // has given card been drawn already?
   int     suit;              // 0=clubs,1=diamonds,2=spades,3=hearts
   int     kind;              // index of kind from 0 to 12,
                              // representing 2,3,...9,10,J,Q,K,A

   string  suitDisplay[6];
   char    kindDisplay[6];

   int     num;     // randomly generated card to pick (from 0 to 51).
   int     cardCount;   // counts how many cards have been drawn;
   int     i;
   unsigned int seed;  // seed for random number generator


   goAgain = true;

   while (goAgain)
   {

      cout << "Enter 'n' to draw without replacement, else 'y' & <Ent>: ";
      cin  >> response; cin.ignore();
      if (response == 'n') replace == false;
      else                 replace = true;

      for (i=0; i < 52; i ++)
          hasBeenDrawn[i] = false;

      seed = time(0);      
      srand(seed);

      for (cardCount=1; cardCount <=5; cardCount++)  // draw 5 cards
      {
         if (replace == false)  // case of draw with no replacement
         {
            do
            {
               num = rand()%52;  // get random number between 0 & 51 inclusive
            } while (hasBeenDrawn[num] == true);
         }
         else                   // case of draw with replacement
         {
            num = rand()%52;  // get random number between 0 & 51 inclusive
         }

         hasBeenDrawn[num] = true;

         suit = num / 13;

         switch (suit)
         {
            case 0: suitDisplay[cardCount] = "  clubs";
               break;
            case 1: suitDisplay[cardCount] = " diamonds";
               break;
            case 2: suitDisplay[cardCount] = "  spades";
               break;
            case 3: suitDisplay[cardCount] = "  hearts";
               break;
         }

         kind = num % 13;

         if      (kind == 12) kindDisplay[cardCount] = 'A';
         else if (kind == 11) kindDisplay[cardCount] = 'K';
         else if (kind == 10) kindDisplay[cardCount] = 'Q';
         else if (kind ==  9) kindDisplay[cardCount] = 'J';
         else if (kind ==  8) kindDisplay[cardCount] = 'T'; // a "ten"
         else
                              kindDisplay[cardCount] =  (char)(kind + 50);
         //Note: ASCII character codes for '0','1',...,'9' are 48 through 57
      }  // end for loop (cardCount = 1 to 5) draw 5 cards

      cout << endl << endl;
      if (replace == true)  
         cout << "You have drawn this hand with replacement: "    << endl << endl;
      else
         cout << "You have drawn this hand without replacement: " << endl << endl;
      for (cardCount=1; cardCount <= 5; cardCount++)
         cout << cardCount << ". " << kindDisplay[cardCount]
                                   << suitDisplay[cardCount] << endl;

      cout << endl << endl;
       
      cout << "Go again? y/n : ";
      cin  >> response; cin.ignore();
      if (response == 'n' || response == 'N') goAgain = false;
      cout << endl << endl;
   }  // end while (goAgain) loop

   return 0;
}  // end main function
