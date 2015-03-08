/****************************************************************
 *                                                              *
 *      Example to illustrate functions that are called from  a *
 *  a main function and from each other.  Notice the definition *
 *  of function prototypes, the passing of arguments, and the   *
 *  explicit return of values in some cases.                    *
 *      Each function should perform some specific task and not *
 *  make any assumption about what to do outside of its limited *
 *  purpose.                                                    * 
 *                                                              *
 *  Author: David Hume                                          *
 *  Date of Creation: October 2, 2008                           *
 *                                                              *
 ****************************************************************/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

void   printArray (double x[], int n);  // function prototypes
void   readArray  (double x[], int &n);
double f7 (double x[], int n);
double f8 (double x);
void   displayPhrase ();
void   displayTriangle(int n, char orientation);

int main ()
{
   bool    goAgain;
   char    response;

   double   x[100];  //array of up to 100 numbers
   int      n;  // counts array elts x[0],x[1],...,x[n-1]
   double result1, x1, y1;
   int lines;
   char upDown;

   goAgain = true;

   while (goAgain)
   {

      readArray  (x, n);
      printArray (x, n);
      result1 = f7 (x, n);

      cout << endl << endl;
      cout << fixed << setprecision(2) ;
      cout << "Value of f7 = " << result1 << endl;

      cout << "Enter value of x: ";
      cin  >> x1;
      y1 = f8(x1);
      cout << "y = f8(x) = " << y1 << endl;

      displayPhrase ();
      cout << endl << endl;

      cout << "Enter number of lines in triangle display: ";
      cin  >> lines; cin.ignore(80,'\n');
      cout << "Triangle oriented up or down? u/d & <Enter>: ";
      cin  >> upDown; cin.ignore(80,'\n');
      displayTriangle (lines, upDown);
       
      cout << "Go again? y/n : ";
      cin  >> response; cin.ignore();
      if (response == 'n' || response == 'N') goAgain = false;
      cout << endl << endl;
   }  // end while (goAgain) loop

   return 0;
}  // end main function

/****************************************************************
 *                                                              *
 *     Read array elements x[0],x[1],x[2],...,x[n-1] of type    *
 * double.  After prompting user for a filename, the file is    *
 * opened, and the numbers are read and stored in the array.    *
 *                                                              *
 * First argument: array of numbers passed by reference.        *
 * Second argument: n = number of elements in the array -- also *
 *    passed by reference.  Value of n is returned to calling   *
 *    program unit.                                             *
 *                                                              *
 ****************************************************************/
void readArray (double x [], int &n)
{
   int      i;
   bool     openFileFailed;
   char     filename[51]; // room for 50-character path/file name
   bool     moreInputData;
   ifstream inputFile;    // object declaration: input file stream

   do {
     openFileFailed = false;
     inputFile.clear();
     cout << "Enter filename (and path, if needed):" << endl;
     cin.getline (filename, 51);
     cout << endl << endl;
   
     inputFile.open(filename);
     if ( inputFile.fail() )
     {
        cout << "File could not be opened" << endl;
        cout << "Try another filename" << endl << endl;
        openFileFailed = true;
     }
   }
   while (openFileFailed);  

   i = 0;
   while ( !inputFile.eof() )
   {      
      inputFile >> x[i];
      if ( !inputFile.eof())  // means that x[i] was successfully read
         i++;
   }
   inputFile.clear();  // clear flags associated with the file
   inputFile.close();
   n = i;  // n = number of elements in array

}  // end readArray function

/****************************************************************
 *                                                              *
 *     Display array elements x[0],x[1],...,x[n-1] of type      *
 * double in four columns of field width 10, right-justified    *
 * with two decimal places.                                     *
 *                                                              *
 * First argument: array of numbers passed by reference.        *
 * Second argument: n = number of elements, passed by value.    *
 *                                                              *
 ****************************************************************/
void printArray (double x[], int n)
{
   int i;
   int columnCount;

   cout << endl << endl;
   cout << "Echo of Array Values from Input File:" << endl << endl;
   cout << setprecision(2) << fixed << right;
   columnCount = 0;
   for (i=0; i < n; i++)
   {
      cout << setw(12) << x[i];
      columnCount++;
      if (columnCount == 4) 
      {
         columnCount = 0;
         cout << endl << endl;
      }

   }
   cout << endl << endl;
   cout << "Number of elements in array: " << n << endl << endl;
}  // end printarray function

/****************************************************************
 *                                                              *
 * Purpose: calculate and return value of function f7           *
 *                                                              *
 * First argument: array of numbers passed by reference.        *
 * Second argument: n = number of elements, passed by value.    *
 * Return value: function value of f7(x,n).                     *
 *                                                              *
 ****************************************************************/
double  f7 (double x[], int n)
{
   int i;
   double num   = 0.0;
   double denom = 0.0;
   for (i=0; i <= n-1; i++)
   {
     num   = num   + x[i]*x[i];
     denom = denom + x[i];
   }
   denom = denom*denom;
   return sqrt(num/denom);
}

/****************************************************************
 *                                                              *
 * Purpose: Evaluate function f8(x)                             *
 * First argument:  domain value x.                             *
 * Returns function value of f8(x).                             *
 *                                                              *
 ****************************************************************/
double f8 (double x)
{
    return 0.05*pow(x,3) + 4*pow(x,2) - 12.0;
}


/****************************************************************
 *                                                              *
 * Purpose: accepts a first name and concatenates one of four   *
 *          randomly chosen phrases to complete and display     *
 *          a statement.                                        *
 * Assumptions: none.                                           *
 * Arguments: none.                                             *
 *                                                              *
 ****************************************************************/
void displayPhrase (void)
{
   static int count = 0;  // static local variable initialized
                          // only once and maintains its value.
   string name;
   string phrase[4] = {" is in love."," eats broccoli and oatmeal.",
                    " is my hero."," has a great future at TTU."};
   cout << endl << endl << "Enter first name: ";
   cin  >> name;
   count++;
   if (count == 1) srand(time(0));
   cout << name + phrase[rand()%4] << endl << endl; 
}
   
/****************************************************************
 *                                                              *
 * Purpose: Display a triangle of stars, oriented up or down.   *
 * First argument:  number of lines in triangle.                *
 * Second argument: triangle oriented up (='u') or down (='d')? *
 *                                                              *
 ****************************************************************/
void displayTriangle (int n, char orientation)
{
   int i,j;
   cout << endl << endl;
   if (orientation == 'u')
   {
      for (i=1; i <= n; i++)
      {
         for (j=1; j <= i; j++)
             cout << '*';
         cout << endl;
      }
   }
   else
   {
      for (i=n; i >= 1; i--)
      {
         for (j=1; j <= i; j++)
             cout << '*';
         cout << endl;
      }
   }
   cout << endl << endl;
}
