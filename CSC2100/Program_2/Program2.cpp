/****************************************************************
 *                                                              *
 *                         Program 2                            *
 *  A switch statement is used to choose from a menu of options.*
 *  The program is made modular by calling separate functions.  *
 *  Values of an array are read in from a file.  The user is    *
 *  prompted to enter the filename for the file with the array. *
 *																*
 *	The program calls a number of functions that are prompted   *
 *	by the user on a chose file.								*
 *                                                              *
 *  Author: Daniel Brown                                        *
 *  Due Date: March 4, 2011                                     *
 *                                                              *
 ****************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

   /* Function prototypes allow the main function to call          */
   /* those functions without knowing their internal details.      */
   /* The prototype describes the argument list and return value.  */

void printArray (const double x[], int  n); // function prototype
void displayMenu ();                  // function prototype
void readArray (double x [], int &n); // function prototype
void arrayComparsion(double x [], int n ); 
void sumArray(double x[], int n );
void average(double x[], int n );
void list(double x[], int n);
void threshold(double x[], int n);
void clearMenu();
int main ()
{
   /* The following variables are visible in the main function.  */

   bool    processAnotherFile = true;
   char    response;
   bool    menuActive;
   char    menuChoice;

   double   x[100];  //array for up to 100 numbers
   int      n;  // counts array elts x[0],x[1],...,x[n-1]

   while (processAnotherFile)
   {
      readArray  (x, n);  // call the readArray function

      menuActive = true;
      while (menuActive)
      {
         displayMenu();   // call displayMenu function
         cin >> menuChoice; cin.ignore(80,'\n');
         cout << endl;

         switch (menuChoice)
         {
            case '1': case 'P': case 'p':
               printArray (x, n);
               break;
            case '2':
				 arrayComparsion(x, n);
				 cout << "Menu Option 2 executed" << endl << endl;
               break;
            case '3':
				 sumArray(x, n);
               cout << "Menu Option 3 executed" << endl << endl;
               break;
            case '4':
				 average(x, n); 
               cout << "Menu Option 4 executed" << endl << endl;
               break;
			case '5':
				 list(x,n);
				 cout << "Menu Option 5 executed"<<endl<<endl;
				break;
			case '6':
				 threshold(x,n);
				cout << "Menu Option 6 executed"<<endl<<endl;
				break;
	 

            case '7': case 'Q': case 'q':
               menuActive = false; // Finish this series of menu choices
               break;
            default:
               cout << "       Invalid menu choice: try again!" << endl << endl;
         }  // end switch statement
      } 
      
      cout << "Process another file? y/n : ";
      cin  >> response; cin.ignore(80,'\n');
      if (response == 'n' || response == 'N') processAnotherFile = false;
      cout << endl << endl;
   }  // end while (goAgain) loop

   return 0;
}  // end main function

/****************************************************************
 *                                                              *
 *     This function handles details of reading a 1-dimensional *
 * array of elements of type double.  After prompting for a     *
 * filename, the file is opened, and the numbers are read and   *
 * stored in an array as x[0],x[1],x[2],...,x[n-1].             *
 *                                                              *
 * First argument: the array where numbers are stored -- passed *
 *    "by reference" (as all arrays are passed).                *
 *                                                              *
 * Second argument: number of elements in the array: passed by  *
 *    reference; "&" means the address of n is sent as argument.*
 *                                                              *
 ****************************************************************/
void readArray (double x [], int &n)
{
   int      i;

   char     filename[51]; // room for 50-character path/file name
   ifstream inputFile;    // object declaration: input file stream

   cout << "Enter filename (and path, if needed): ";
   cin.getline (filename, 51);
   cout << endl << endl;
   
   inputFile.open(filename);

   i = 0;
   
   while (inputFile.eof() == false)
   {      
      inputFile >> x[i];
      if (!inputFile.eof())  // means that x[i] was successfully read
         i++;
   }
   inputFile.clear();  // clear flags associated with the file
   inputFile.close();
   n = i;  // n = number of elements in array

}  // end readArray function

/****************************************************************
 *                                                              *
 *     This function displays a 1-dimensional array of numbers  *
 * of type double in six columns of field width 10 and two      *
 * decimals to the right of the decimal point.                  *
 *                                                              *
 * First argument: the array of numbers is passed by reference, *
 *    but const array values cannot be changed in the function. *
 *                                                              *
 * Second argument: n = number of array elements; thisargument  *
 *    is passed "by value:" the value of n comes to function,   *
 *    but nothing goes back to calling function via this arg.   *
 *                                                              *
 ****************************************************************/
void printArray (const double x[], int n)
{
   int i;
   int columnCount;

   cout << endl << endl;
   cout << "Array Values from Input File:" << endl << endl;
   cout << setprecision(2) << fixed << right;
   columnCount = 0;
   for (i=0; i < n; i++)
   {
      cout << setw(12) << x[i];
      columnCount++;
      if (columnCount == 6) 
      {
         columnCount = 0;
         cout << endl << endl;
      }

   }
   cout << endl << endl;
   cout << "Number of elements in array: " << n << endl << endl;
}  // end printarray function

/****************************************************************
 *																*
 *		This function reads in the array as the first argument  *
 *	and the number of elements in the array as the second       *
 *	argument.													*
 *																*
 *		It then compares the elements of the array to find the  *
 *	maximum and minimum value among the array elements. To do	*
 *	so it automatically sets the first element to max and then	*
 *	loops through the elements and compares by replacing the 	*
 *	correct element as the max or min value.					*
 *																*
 ****************************************************************/

void arrayComparsion (double x [], int n)
{
	double max = x [0]; 
	
	for (int i = 1; i < n; i++) {
		if (x[i] > max) {   // if the current array element is greater than max, make it the new max
			max = x[i];
		}
	}
	
	double min = x [0];
	
	for (int j = 1 ; j < n; j++) {
		if (x[j] < min) {
			min = x[j];
		}
	}
	cout << setprecision(2)<< fixed<< right; 
	cout << "Max Value = " <<setw(9)<< max<<endl;
	cout << "Min Value = " <<setw(9)<< min << endl<< endl;
}

/****************************************************************
 *																*															 *
 *		This function reads in the array as the first argument  *
 *	and the number of elements in the array as the second       *
 *	argument.													*
 *																*
 *		The function then reads the elements of the array and	*
 *	adds all the elements by looping them into a variable.		*
 *	To calculate the absolute value of an array the function	*
 *	then multiplies any negative element by -1 to make it		*
 *	positive.													*
 *																*
 ****************************************************************/

void sumArray(double x [], int n)
{
	double sum = 0;
	double abSum = 0;
	for (int i = 0; i<n; i++) {
		sum+=x[i]; 
	}
	
	for (int j =0; j < n; j++) {
		
		abSum+=abs(x[j]);
	}
	cout << setprecision(2)<<fixed<<right;
	cout << "Sum of values           = " <<setw(9)<< sum << endl; 
	cout << "Sum of ablsoulte values = " <<setw(9)<< abSum<<endl<<endl;
}


/****************************************************************
 *																*															 *
 *		This function reads in the array as the first argument  *
 *	and the number of elements in the array as the second       *
 *	argument.													*
 *																*
 *		The function then calulates the average and the standard*
 *	deviation of the array elements.							*
 *****************************************************************/
void average( double x[], int n)
{
	double ave, sum, s, stdSum;
	
	
	sum = 0;
	for(int i = 0; i < n; i++){
		sum += x[i];  
	}
	ave = sum/(double)n;
	
	stdSum =0;
	for(int j = 0; j < n; j++){//loops through the summation part of the deviation equation. 
		stdSum = pow((x[j]-ave),2)+stdSum;
	}
	
	s = sqrt(stdSum/(double)n);
	
	cout << setprecision(2)<<fixed<<right;
	cout << "Average of values  = " <<setw(9)<< ave << endl; 
	cout << "Standard Deviation = " <<setw(9)<< s   << endl<<endl;
	
}


/****************************************************************
 *																*															 *
 *		This function reads in the array as the first argument  *
 *	and the number of elements in the array as the second       *
 *	argument.													*
 *																*
 *		The function then counts all of the elements that meet	*
 *	the requirements below.										*
 *																*
 ****************************************************************/

void list(double x[], int n )
{
	int positive, negative, zero, abs;
	
	positive = 0;
	negative = 0;
	zero = 0;
	abs = 0; 
	
	for(int i =0; i < n; i++){
		if(x[i] > 0){
			positive++;
		}
		if (x[i] < 0) {
			negative++;
		}
		if (x[i] == 0) {
			zero++;
		}
		if (x[i] <= 10 ) {
			abs++;
		}
	}
	
	cout << "Count of positive elements = " <<setw(9)<<positive<<endl;
	cout << "Count of negative elements = " <<setw(9)<<negative<<endl;
	cout << "Count of zero elements     = " <<setw(9)<<zero<<endl;
	cout << "Count of abs. values<= 10  = " <<setw(9)<<abs<<endl;
	
} 


/****************************************************************
 *																*															 *
 *		This function reads in the array as the first argument  *
 *	and the number of elements in the array as the second       *
 *	argument.													*
 *																*
 *		The function then prompts the user to enter in the		*
 *	requried threshold values and then compares the elements in	*
 *	array to those values.										*
 *																*
 ****************************************************************/

void threshold(double x[], int n)
{
	double thresholdL, thresholdH;
	int count = 0;
	
	cout << "Enter in your low threshold value."<<endl;
	cin >> thresholdL;
	cout << "Enter in your high threshold value."<<endl;
	cin >> thresholdH;
	cout << endl;
	
	for(int i = 0; i < n; i++){
		
		if(x[i] >= thresholdL && x[i] <=thresholdH){
			count++;
		}
	}
	
	cout << setprecision(2)<< fixed<< right;
	cout << "Number of values >="<<thresholdL;
	cout << " and <= " << thresholdH;
	cout << " is: " <<count<<endl<<endl; 
}


/****************************************************************
 *                                                              *
 *         This function displays the main menu.  There are no  *
 *   arguments, and no data is returned (return type: "void").  *
 *                                                              *
 ****************************************************************/

void displayMenu ()
{
   cout << "   *************************************************" << endl;
   cout << "   *                                               *" << endl;
   cout << "   *           M A I N    M E N U                  *" << endl;
   cout << "   *                                               *" << endl;
   cout << "   *   1) (P)rint Array                            *" << endl;
   cout << "   *   2) Option 2                                 *" << endl;
   cout << "   *   3) Option 3                                 *" << endl;
   cout << "   *   4) Option 4                                 *" << endl;
   cout << "   *   5) Option 5                                 *" << endl; 
   cout << "   *   6) Option 6                                 *" << endl;
   cout << "   *   7) (Q)uit: Finish processing this array     *" << endl;
   cout << "   *                                               *" << endl;
   cout << "   *************************************************" << endl;
   cout << "       Enter choice: ";
}  // end displayMenu function

void clearMenu(){
    for(int i =0; i < 1000;i++){
        cout << "\n" << endl;
    }
}
