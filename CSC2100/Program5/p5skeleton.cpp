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
 *         Finally, as a diagnostic check, the last and     *
 *    first name fields are displayed from array elements,  *
 *    using both array subscript and pointer notation.      *
 ************************************************************/ 
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>  // string function library
using namespace std;

void displayMenu ();
void printData(struct StudentRecord s[], int n);

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

   /* Third phase of program: display binary file records in two ways 
   for (int i=0; i < n; i++)
      cout << setw(16) << left << student[i].lastName << "  " << student[i].firstName << endl;
   cout << endl<< endl;

   ptr = student;            // point to first record in student record array
   for (int i=0; i < n; i++)
   {
      cout << setw(16) << left << ptr->lastName << "  " << ptr->firstName << endl;
      ptr++;                 // point to next record in student record array
   }*/
   cout << endl;
	
	
	//displayMenu ();
	printData(student,n);
	
	
	
   return 0;
}



void displayMenu () // function displays the menu that the users chooses from.
{
	
	cout << endl << endl << endl;
	
	cout << "   *************************************************" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *           M A I N    M E N U                  *" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *   1)                                          *" << endl;
	cout << "   *   2)											*" << endl;
	cout << "   *   3)											*" << endl;
	cout << "   *   4)											*" << endl;
	cout << "   *   5)											*" << endl;
	cout << "   *   6)											*" << endl;
	cout << "   *                                               *" << endl;
	cout << "   *************************************************" << endl;
	cout << "       Enter choice: "<<endl<<endl;
	
}  // end displayMenu function

//Option 1 

void printData ( StudentRecord s[], int n)
{
	int i, count;
	
	cout << "	Student Number			Last Name			First Name			Major			Earned Hours			GPA" << endl<<endl;
	
	for (i =0; i < n; i++) {
		count = 0; 
		
			cout <<setw(18)<< s[i].studentNumber<<setw(32)<<s[i].lastName<<setw(32)<<s[i].firstName;
			cout << setw(18)<<s[i].major<<setw(32)<<s[i].earnedHours<<setw(32)<<s[i].gpa<<endl<<endl;
	}
	
	
}
