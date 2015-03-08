/*  First whack at Program 4 */
/*  Author: David Hume.  March 31, 2011  */

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int main ()
{
   char filename[50];
   ifstream inputFile;
   char text[40000];
   int lineNumber;
   bool anotherSearch = true;
   char response;
   int lineCount ;
   int instanceCount;
   char nextChar;
   int i,j,k;
   int charCount;
   char nextLine[81];
   char target[40];  // search object/ pattern for which to search
   bool match;
	char *linePtr;
	char *charPtr;
/*
   cout << "Enter filename of text to search: "; // read file containing test
   cin.getline (filename, 50);
   inputFile.open (filename);
   i = 0;
   while (!inputFile.eof())
   {
      inputFile.get(nextChar);
      if (!inputFile.eof())
      {
         text[i] = nextChar;
         if (text[i] != '\n')
            cout << text[i];
         else
            cout << endl;
         i++;
      }
   }
   text[i] = '\0';
   inputFile.close(); inputFile.clear();
   charCount = i;

   lineNumber = 1;              // print out contents of text
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

   */

   cout << "Enter filename of text to search: ";  // read file another way
   cin.getline (filename, 50);
   inputFile.open (filename);
   i = 0;
   lineNumber = 1;
	cout << endl <<endl;
   while (!inputFile.eof())
   {
      inputFile.getline(nextLine,81);
      if (!inputFile.eof())
      {
         cout << "Length of line " << lineNumber << " = " << strlen(nextLine) << endl;
         lineNumber++;
         for (j=0; j < strlen(nextLine); j++)
         {
            text[i] = nextLine[j];
            cout << text[i];
            i++;
         }
         cout << endl<< endl;
         text[i] = '\n';
         i++;
      }
   }
   text[i] = '\0';
   inputFile.close();
   charCount = i;
   
   lineNumber = 1;      // print out text contents again (same way)
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
	   lineCount = 1;
      instanceCount = 0;
	   linePtr = &text[0];
	   
	   
	 /*for (j = 0; j<strlen(target); j++) {
		 target[j]= toupper(target[j]);
	 }*/
	   
      for (i=0; i < charCount; i++)
      {
		  if (text[i] == '\n') {
			  linePtr = &text[i+1]; 
			  lineCount++;
		  }
		  
			match = true;
            j = 1; k = i+1;
		  
		  if (toupper(target[0]) != toupper(text[i])){
			  continue;
		  }
		  else // first character of target matches 
         {
			
			 
            while (match == true && j < strlen(target))
            {
				
			
               if (k < charCount) // stay within the text
               {
                  if (target[j] != text[k])
                     match = false;
				  else
                  { 
					  if(target[strlen(target)-1]=='*')
					  {
						  target[strlen(target)-1] = '\0';
				 
						  if (i > 0 && isalpha(text[i-1])) {
							  match = false;
						  }
					  }
					  
                     j++; k++;
                  }
               }
               else
                  match = false;
            }  // end of while loop
            if (match == true) // print this instance 
            {
				
				char continueInstance;
				
			
					
				
               instanceCount++;
               cout << "Line " << setw(3) << lineCount << ": ";
				charPtr = linePtr;
				while (*charPtr != '\n') {
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
         }  //end of else first character of target matches 
		  
      }     // end of for loop to go through all characters in the text
      if (instanceCount > 0)  
         cout << endl << endl;
      if (instanceCount == 1) {
		  cout << "There is 1 instace of target : \"" << target << "\" "<< endl;
	  }
	  else {
		  cout << "There are " << instanceCount << " instances of target: \"" <<target << "\" "<<endl;
	  }
	   cout << endl << endl;
	   cout << "Another search? y/n & <enter>: ";
      cin  >> response; cin.ignore(80,'\n');
      if (response == 'n') anotherSearch = false;
   }
    
   return 0;
}
//front part of the search object
/* 
 fo(i = 0; i<charCount; i++)
 {if (i == 0)
 {dont check preceeding char}
 else(){do check preceeding chars}
 }
 
 if(toupper(text[i])==toupper(target[0]))
 
 if(i != 0)
 {look at text[i-1]}
 
 if(!isalpha(text[i-1])
 {keep checking}
 
 if(target[strlen(target)-1]=='*')
 {target[strlen(target)-1] = '\0'}
 case 1 uses an asterisk
 
 case 2 does not use an asterisk
 
 */
