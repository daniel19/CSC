/************************************************************
 *    Program 5												*
 *    Author:  Daniel Brown                                 *
 *    Date Modified: 4/7/2011                               *
 *    Source code filename: Program5.cpp.					*
 *    Sample source ASCII text data file: p4Student.dat     *
 *                                                          *
 *         The program reads text data from an ASCII text   *
 *    file, uses this data to define records of type        *
 *    StudentRecord, and writes these records to a binary   *
 *    file, which is created.                               *
 *         Next, records the of binary file are read, and   *
 *    their contents stored in an array of student records. *
 *         Finally the program will give the user options	*
 *	  to manipulate the data.								*
 ************************************************************/ 
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring> 
#include <cctype>  // string function library
using namespace std;

void displayMenu ();
void printData(struct StudentRecord s[], int n);
void sortA(struct StudentRecord s[], int n);
void sortD(struct StudentRecord s[], int n);
void threshold(StudentRecord s[], int n);
void threshold2(StudentRecord s[], int n);



struct StudentRecord
{
   char     lastName [16];  // field definitions of the structure
   char     firstName[16];
   char     hometown [16];
   char     major[5];
   int      studentNumber;
   double   balance;
   int      earnedHours;
   double   gpa;
	char temp1; 
	char temp2; 
};





int main ()
{
   char textFilename[50];
   char binaryFilename[50];
   StudentRecord nextStudent;  // one instance of Studentrecord
   StudentRecord student[100]; // arrayof 100 StudentRecords
   StudentRecord *ptr;  //pointer to a struct of type "StudentRecord"
   int   n;             // counts number of elements in student array
   fstream  studentFile;  // an object in fstream can be read or written
   ifstream textFile;     // an object in istream can be read only
   char     lastIn [16];  // Places to read data from the text file
   char     firstIn[16];  // These correspond to the fields of StudentRecord
   char     townIn [16];
   char     majorIn[5];
   int      numberIn;
   double   balanceIn;
   int      hoursIn;
   double   gpaIn;
   bool menuActive; 
   char menuChoice;

   /* First phase: read text file data and create binary file records */
   cout << "Enter filename of source text file: ";
   cin >> textFilename;
   cout << endl;
   textFile.open (textFilename);

   cout << "Enter filename of binary file of student records: ";
   cin >> binaryFilename;
   cout << endl;
   studentFile.open (binaryFilename, ios:: out | ios:: binary);
   n = 0;

   while (!textFile.eof())
   {
      textFile >> lastIn >> firstIn >> townIn    >> majorIn >> numberIn
                                    >> balanceIn >> hoursIn >> gpaIn;
      if (!textFile.eof())  // 
      {
         strcpy (nextStudent.lastName, lastIn);  // string copy function
         strcpy (nextStudent.firstName, firstIn);
         strcpy (nextStudent.hometown, townIn);
         strcpy (nextStudent.major, majorIn);
         nextStudent.studentNumber = numberIn;
         nextStudent.balance = balanceIn;
         nextStudent.earnedHours = hoursIn;
         nextStudent.gpa = gpaIn;
         studentFile.write (reinterpret_cast<char *>(&nextStudent), sizeof(nextStudent));
      n++;
      }
   }  // end while loop
   cout << "Records created in binary student file = " << n << endl;
   cout << endl;

   textFile.close();
   studentFile.close();
   studentFile.clear();

   /* Second phase: read binary file records into an array */
	
   studentFile.open (binaryFilename, ios:: in | ios:: binary);
   ptr = student;  // point to beginning of array.
   n = 0;  // count for number of students

	
   while (!studentFile.eof())
   {
      studentFile.read (reinterpret_cast<char *>(ptr), sizeof(nextStudent));
      if (!studentFile.eof())
      {
         ptr++;  //
         n++;    //count of number of students read from student file.
      }
   }  // end while loop
   studentFile.close();

   cout << "Records read from  binary student file = " << n << endl;
   cout << endl<< endl;

   cout << endl;
	
	menuActive = true; 
	while (menuActive)
	{
		displayMenu ();   // call displayMenu function.
		cin >> menuChoice;
		cout << endl;
		
		switch (menuChoice){
		
			case '1':
				printData(student, n);
				break;
			case '2':
				sortA(student, n);
				break;
				
			case'3':
				sortD(student, n);
				break;
			case'4':
				threshold(student, n);
				break;
			case'5':
				threshold2(student, n);
				break;
				
			case '6': case 'Q': case 'q':
				menuActive = false; // Finish this series of menu choices.
				break;
				
			default:
				cout << "       Invalid menu choice: try again!" << endl << endl;
		}
	}
	
	
   return 0;
}



void displayMenu () // function displays the menu that the users chooses from.
{
	
	cout << endl << endl << endl;
	
	cout << "   *************************************************" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *           M A I N    M E N U                  *" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *   1)Print Data                                *" << endl;
	cout << "   *   2)Sort Data by last name					*" << endl;
	cout << "   *   3)Sort GPA Data								*" << endl;
	cout << "   *   4)Find the Student balance					*" << endl;
	cout << "   *   5)Find the Student major					*" << endl;
	cout << "   *   6)Quit Program								*" << endl;
	cout << "   *												*" << endl;
	cout << "   *************************************************" << endl;
	cout << "       Enter choice: ";
	
}  // end displayMenu function

//Option 1 

void printData (StudentRecord s[], int n)
{
	int i, count;
	
	cout << "	Student Number			Last Name			First Name			Major			Earned Hours			GPA" << endl<<endl;
	count = 1; 
	
cin.ignore();
	
	for (i =0; i < n; i++) {
		
		if (count == 11 || count == 21 ||count == 31 ||count == 41||count == 51|| count == 61 || count == 71 || count == 81 || count ==91) {
			cout << "<Enter>";
			cin.ignore();
			cout << endl;
			
			
		}
		
			cout << count<<".	";
			cout <<setw(32)<<left<< s[i].studentNumber<<setw(32)<<left<<s[i].lastName<<setw(32)<<s[i].firstName;
			cout << setw(26)<<s[i].major<<setw(24)<<s[i].earnedHours<<"      "<<setw(32)<<s[i].gpa<<endl<<endl;
		
		
		count ++;
	}
	
	
}

//Option 2

void sortA(StudentRecord s[], int n)
{
	int last, j, pass;
	bool haveSwap;
	StudentRecord temp1,temp2;
	
	last = 1;
	for (pass = 1 ; pass < n; pass++) {
		haveSwap =false;
		
		for (j = n-1; j >= last; j--) {
			if (strcmp(s[j].lastName, s[j-1].lastName) < 0) {
				haveSwap = true;
				
				
				temp1 = s[j];
				temp2 = s[j-1]; 
				s[j] = temp2;
				s[j-1] = temp1;
				
				
				
			}
		}
	if (haveSwap == false) {
		pass = n;
		}
		last++;
	 }
}

//Option 3
void sortD(StudentRecord s[], int n)
{
	int last, j, pass;
	bool haveSwap;
	StudentRecord temp1, temp2; 
	
	last = 1;
	for (pass = 1 ; pass < n; pass++) {
		haveSwap =false;
		
		for (j = n-1; j >= last; j--) {
			if (s[j].gpa < s[j-1].gpa) {
				haveSwap = true;
				
				
				temp1 = s[j];
				temp2 = s[j-1]; 
				s[j] = temp2;
				s[j-1] = temp1;
				
			}
		}
		if (haveSwap == false) {
			pass = n;
		}
		last++;
	}
}

//Option 4

void threshold(StudentRecord s[], int n)
{
	double balanceT;
	int i, count;
 
	
	cout << endl<<endl;
	cout << "Please enter in a threshold value for student's balance.";
	cin >> balanceT;
	
	
	
	
	cout << "	Last Name		First Name			Student Number			Balance" << endl<<endl;
	count = 1; 
	
	cin.ignore();
	
	for (i =0; i < n; i++) {
		
		if (count == 11 || count == 21 ||count == 31 ||count == 41||count == 51|| count == 61 || count == 71 || count == 81 || count ==91) {
			cout << "<Enter>";
			cin.ignore();
			cout << endl;
			
			
		}
		
		if(balanceT <= s[i].balance){
		cout << count<<".	";
		cout <<setw(25)<<left<<s[i].lastName<<setw(32)<<left<<s[i].firstName<<left<<setw(2)<< s[i].studentNumber;
		cout <<fixed<<setprecision(2)<<setw(32)<< right<<s[i].balance<<endl;
			count ++;
		}
		
		
		
	}
	
	
	
}

//Option 5
void threshold2(StudentRecord s[], int n)
{
	double gpaT;
	char majorT[3];
	int i,count;
	
	
	cout << endl<<endl;
	cout << "Enter in the students major.   ";
	cin >> majorT;
	cout << endl<<" Please enter in a threshold value for GPA. ";
	cin >> gpaT; 
	
	for (i = 0; i <=3; i++) {
		majorT[i] = toupper(majorT[i]); 
		
	}
	
	
	cout<<endl;
	cout << "	Last Name		    First Name			Hometown			Major		  		  GPA" << endl<<endl;
	count = 1; 

	cin.ignore();
	
	for (i =0; i < n; i++) {
		
		if (count == 11 || count == 21 ||count == 31 ||count == 41||count == 51|| count == 61 || count == 71 || count == 81 || count ==91) {
			cout << "<Enter>";
			cin.ignore();
			cout << endl;
			
			
		}
		
		
		if(strcmp(majorT, s[i].major) == 0  && gpaT <= s[i].gpa){
			cout << count<<".	";
			cout <<setw(28)<<left<<s[i].lastName<<setw(28)<<left<<s[i].firstName<<left<<setw(32)<< s[i].hometown;
			cout <<setw(32)<< left<<s[i].major<<setw(32)<<left<<s[i].gpa<<endl;
			count ++;
		}
		
		
		
	}
	
}