/*  Program 4
 *	
 *	This program will use arrays and pointer variables
 *	to read in an input file from the user that consists
 *	of words in plain text. The program will then prompt
 *	the user to enter a target variable to search throughtout
 *	the given file. As a result the program will then show the
 *	the number of instances of that target. 
 *
/*  Author: Daniel Brown. April 25, 2011  */

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;

int main ()
{
   char filename[50];
   ifstream inputFile;
   char text[40000];
   int  lineNumber;
   bool anotherSearch = true;
   char response;
   int lineCount;
   int instanceCount;
   char nextChar;
   int i,j,k;
   int charCount;
   char nextLine[81];
   char target[40];  // search object/ pattern for which to search
   bool match;
   char *linePtr;    // points to first character of current line of text
   char *charPtr;    // points to characters in given line of text

   cout << "Enter filename of text to search: ";  // read file line-by-line
   cin.getline (filename, 50);
   inputFile.open (filename);
   lineNumber = 1;
   i = 0;
   while (!inputFile.eof())
   {
      inputFile.getline(nextLine,81);
      if (!inputFile.eof())
      {
         for (j=0; j < strlen(nextLine); j++)
         {
            text[i] = nextLine[j];
            i++;
         }
         text[i] = '\n';
         i++;
      }
   }
   text[i] = '\0';
   inputFile.close();
   charCount = i;
   
   lineNumber = 1;      // print out text contents
   cout << endl << endl;
   cout << "                       Text File Contents" << endl << endl;
   cout << setw(4) << right;
   cout << lineNumber << "  ";
   for (i=0; i < charCount-1; i++)//There are "charCount" characters to process
   {
      cout << text[i];
      if (text[i] == '\n')
      {
         lineNumber++;
         cout << setw(4) << lineNumber << "  ";
      }
   }
   cout << endl << endl << "Character count = " << charCount << endl << endl;

   while (anotherSearch == true)  // Start searching for words or phrases
   {
      cout << "Enter search object: ";
      cin.getline (target,40); cout << endl << endl;
      instanceCount = 0;
      lineCount = 1;
      linePtr = &text[0];
      
	for (i=0; i < charCount; i++)
      {
         if (text[i] == '\n')
         {
            linePtr = &text[i+1]; // point to first character of next line
            lineCount++;
         }

		  if (toupper(target[0]) != toupper(text[i])){
            continue;
		  }
		  if (target[strlen(target)-1]=='*') {
			  target[strlen(target)-1] = '\0';
			  
				
			  
			  continue;
		  }
         else /* first character of target matches */
         {
            match = true;
            j = 1; k = i+1;
            while (match == true && j < strlen(target))
            {
               if (k < charCount) // stay within the text
               {
                  if (target[j] != text[k])
                     match = false;
                  else
                  {
                     j++; k++;
                  }
               }
               else
                  match = false;
            }  // end of while loop
            if (match == true) /* print this instance */
            {
               instanceCount++;
				char continueInstance;
               cout << "Line " << setw(3) << lineCount << ": ";
               charPtr = linePtr;
               while (*charPtr != '\n')
               {
                  cout << *charPtr;
                  charPtr++;
               }
				if (instanceCount == 9) {
					cout <<endl<<endl<< "There are more than 8 instances of your target" <<endl;
					cout << "Do you wish to print out the rest of the instances? (y/n)";
					cin >> continueInstance;
					cout << endl;
					
					if (continueInstance == 'n' || continueInstance == 'N') {
						break;
					}else {
						cout << "Line " << setw(3) << lineCount << ": ";
						charPtr = linePtr;
						while (*charPtr != '\n') {
							cout << *charPtr;
							charPtr++;
						}
					}
					
				}
				
               cout << '\n';
                
            }
         }  // end of else first character of target matches
      }     // end of for loop to go through all characters in the text
      if (instanceCount > 0) cout << endl << endl;
      if (instanceCount == 1)
         cout << "There is 1 instance of target: \"" << target << "\" " << endl;
      else
         cout << "There are " << instanceCount << " instances of target: \"" <<
              target << "\" " << endl;
      cout << endl << endl;
      cout << "Another search? y/n & <enter>: ";
      cin  >> response; cin.ignore(80,'\n');
      if (response == 'n') anotherSearch = false;
   }
    
   return 0;
}
