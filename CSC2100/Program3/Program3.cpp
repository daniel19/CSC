/*
 **********************************************************
 *Project 3: Matrix functions							  *
 *Author: Daniel Brown									  *			
 *														  *	
 *														  *		
 *Description:											  *				
 *		This program takes in a users' created data files *
 *and runs them through a series of matrix functions. The *
 *function will display a menu through which the user will*
 *operate from. The first Option in the program calculates*
 *the border sum of the two-dimensional array. The third  *
 *option of the program calculates the diagonal sum of    *
 *the array. The fourth option of the program calculates  *
 *the matrix sum of two matrix arrays. The fifth option of*
 *the program allwos the user to zero out any columns or  *
 *rows that they wish.									  *
 *														  *					
 *														  *
 *														  * 
 *														  * 	
 *Date of completion: March 25, 2011					  *	
 **********************************************************/



#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void displayMenu ();                               // function for the Display Menu.
void readMatrix(double x[][30], int &m, int &n);
void printMatrix(double x[][30], int m, int n);
double borderSum(double x[][30], int m, int n);
void diagonalSum(double x[][30], int m, int n);
void matrixSum(double a[][30], double [][30], int m, int n);
void diagonalZero(double x[][30], int m, int n);
void zeroOut(double x[][30], int m, int n);

int main ()
{
	double a [30][30];
	double b [30][30];
	double c [30][30];
	int s, t; // size of a is sxt
	int p, q;  // size of b is pxq
	
	char response;
	bool menuActive;//variable that repeats the menu.
	char menuChoice;//variable that takes in the user's menu choice.
	bool goAgain = true;
	double totalBorder;
	int count;
	bool repeat;
	bool prevent;
	char repeatLoop;
	
	
	
	while(goAgain == true)
	{
		
		readMatrix (a, s, t); // call the readArray function.
		readMatrix (b, p, q);  // call the readArray function  
		
        cout << "Matrix A: " << endl;
		printMatrix (a, s, t);
		
		cout<< "Matrix B: " << endl;
		printMatrix (b, p, q);
		
        menuActive = true;
		while (menuActive)
		{
			displayMenu ();   // call displayMenu function.
			cin >> menuChoice;
			cout << endl;
			
			switch (menuChoice)
			{
				case '1': case 'b' : case 'B':
					totalBorder = borderSum(a, s, t);
					cout << fixed << setprecision(2) << setw(10) << "Border Sum of A = " << totalBorder << endl << endl;
					totalBorder = borderSum(b, p, q);
					cout << fixed << setprecision(2) << setw(10) << "Border Sum of B = " << totalBorder << endl << endl;
					break;
					
				case '2': case 'd': case 'D':
					if( s == s)
					{
						diagonalSum(a, s, t);
					}
					else
					{
						cout << " Matrix A is not square " << endl;
					}
					
					break;
					
				case '3': case 'M': case 'm':
					
					if( s == p && t == q)
					{
						matrixSum(a, b, s, t);
						
						
					}
					
					break;
				case '4': case'T': case 't':
					if( s==s)
					{
						diagonalZero(a, s, t);
						
					} 
					else
					{
						cout<< "Matrix A is not square. " << endl << endl;
					}
					break;
					
				case '5': case'Z': case 'z':
					
					printMatrix(a, s,t);
					zeroOut(a, s, t);
					printMatrix(a, s, t);
					repeat = true;
					while(repeat == true)
					{			
						cout << " Would you like to zero another Row or Col ? y/n: ";
						cin >> repeatLoop;
						repeat = true;
						prevent = true;
						while(prevent == true)
						{
							if( repeatLoop == 'y' || repeatLoop == 'Y')
							{
								zeroOut(a, s, t);
								printMatrix(a, s, t);
								prevent = false;
								
							}
							else if( repeatLoop == 'n' || repeatLoop == 'N')
							{
								repeat = false;
								prevent = false;
							}
							else
							{
								cout << " You did not enter yes or no, Please try again." << endl << endl;
								
							}
						}//ends prevent while
					}// ends repeat while
					break;
					
				case '6': case 'Q': case 'q':
					menuActive = false; // Finish this series of menu choices.
					break;
					
				default:
					cout << "       Invalid menu choice: try again!" << endl << endl;
			}  // end switch statement.
		}//ends menu active
		
		cout << " Do you wish to repeat the program? y/n & <enter>: ";
		cin >> response;
		if(response == 'n' || response == 'N')
			goAgain = false;
		
		
	}//end of main while
	
	return 0;
}






void readMatrix (double x[][30], int&m, int&n) 
{
	int i,j;
 	ifstream inputFile;
	char filename[51];
	cout<<"EnterFilename: ";	
	cin.getline(filename,51);
	cout << endl;
	inputFile.open(filename);
	inputFile >> m >> n; // scan in dimensions: # rows & # columns
	
	for(i=0; i < m; i++)
	{
		for(j=0; j < n; j++)
		{
			inputFile >> x[i][j];	
		}
		
	}
	
	inputFile.clear();
	inputFile.close();      
	
	
}

void printMatrix(double x[][30], int m, int n)
{
    int i, j;
    cout << endl << endl;
    for (i=0; i < m; i ++)
	{
		for(j=0; j < n; j++)
		{
			cout << fixed << setprecision(2) << setw(8) << x[i][j];
			if (j == 9 || j == 19) {
				cout << endl;
			}
		}
		cout<< endl << endl;
	}
	cout << "   Size " << m << " X " << n << endl << endl;
	
}


double borderSum(double x[][30], int m, int n)
{
	int i,j;
	double sumBorder = 0;
	
	if( m <= 2 || n <=2)
	{
		for(i=0; i<= m-1; i++)
		{
			for(j=0; j<=n-1; j++)
			{
				sumBorder= sumBorder + x[i][j];
			}
		}
		return sumBorder;
	}
	
	for(i=0; i<=m-1; i++) // takes care of all the first columns.
	{
		for(j=0; j<=0;j++)
		{
			sumBorder = sumBorder + x[i][j];
		}
		
	}
	
	for(i=0; i<=m-1; i++) // takes care of all the last columns.
	{
		for(j=n-1; j<=n-1; j++)
		{
			sumBorder = sumBorder + x[i][j];
		}
	}
	for(i=0; i<=0; i++) //takes care of first row
	{
		for(j=1; j<=n-2; j++)
		{
			sumBorder = sumBorder + x[i][j];
		}
		
	}
	
	for(i=m-1; i<=m-1; i++)//takes care of last row
	{
		for(j=1; j<=n-2; j++)
		{
			sumBorder = sumBorder + x[i][j];
		}
	}
	
	return sumBorder;
	
	
}

void diagonalSum(double x[][30], int m, int n)
{
	int i,j;
	double diagonalTotal = 0;
	double reverseTotal = 0;
	
	for(i=0; i<=m-1; i++)
    {
		diagonalTotal = diagonalTotal + x[i][i];
    }
	j=0;
	for(i=m-1; i>=0; i--)
	{
		reverseTotal = reverseTotal + x[i][j];
		j ++;
	}
	
	cout << endl << endl;
	cout << "Main diagonal sum = " << fixed << right << setprecision(2) << diagonalTotal << endl;
	cout << "Reverse diagonal sum = " << fixed << right << setprecision(2) << reverseTotal << endl;
}



void matrixSum(double a[][30], double b[][30], int m, int n)
{
	int i,j;
	double c[30][30];
	
	for(i=0; i<=m-1; i++){
		for(j=0; j<=n-1; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	cout << "Matrix sum of a and b: " << endl << endl;
	
	printMatrix(c, m, n); 
}


void diagonalZero(double x[][30], int m, int n)
{
	int i,j;
	int count = 0;
	
	for(i=0; i<=m-2; i++)
    {
		for(j=i+1; j<=n-1;j++)
		{
			if(x[i][j]>0.0 || x[i][j]<0.0)
			{
				count = 1;
				
			}
		}
    }
	for(i=m-1; i<=1; i--)
    {
		
		for(j=0; j<=i-1; j--)
		{
			
			if(x[i][j]>0.0 || x[i][j]<0.0)
			{		
				count = 1;
				
				
			}
		}
    }
	
	

	
	if(count == 0)
	{
		cout << "Matrix A is Diagonal." << endl << endl;
	}
	if(count == 1)
	{
		cout << "Matrix A is Not Diagonal." << endl << endl;
	}
	else
	{
	}
}


void zeroOut (double x[][30], int m, int n)
{
	
	int i,j;
	int number;
	char answer;
	char response;
	bool repeatAgain;	
	
	repeatAgain = true;   
	while(repeatAgain == true)	
	{
		cout << " Please enter 'r' (Row) or 'c'(col): ";
		cin >> answer;
		cout << endl << endl;
		if(answer == 'r' || answer == 'R')
		{
			cout << " Please enter the Row number to Zero out: ";
			cin >> number;
			cout << endl << endl;
			for(i=number; i<=number; i++)
			{
				for(j=0; j<=n-1; j++)
				{
					x[i][j] = 0.0;
				}
	        }
			repeatAgain = false;
		}
		if(answer == 'c' || answer == 'C')
		{
			cout << " Please enter the Column number to Zero out: ";
			cin >> number;
			cout << endl << endl;
			for(i=0; i<=m-1; i++)
			{
				for(j=number; j<=number; j++)
				{
					x[i][j] = 0.0;
				}
				
	        }
			repeatAgain = false;
		}
	    else
		{
	        cout << " You did not enter a valid choice." << endl << endl << endl;
		}
		
	}// ends while loop
	
}


void displayMenu () // function displays the menu that the users chooses from.
{
	
	cout << endl << endl << endl;
	
	cout << "   *************************************************" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *           M A I N    M E N U                  *" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *   1) (B)order Sum                             *" << endl;
	cout << "   *   2) (D)iagonal Sum for Matrix A              *" << endl;
	cout << "   *   3) (M)atrix sum                             *" << endl;
	cout << "   *   4) (T)esting Matrix A for Diagonal          *" << endl;
	cout << "   *   5) (Z)eroing out Matrix A                   *" << endl;
	cout << "   *   6) (Q)uit: Finish processing this array     *" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *************************************************" << endl;
	cout << "       Enter choice: ";
	
}  // end displayMenu function