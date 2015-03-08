/*
 *Daniel Brown 
 *Program 1, CSC 2100 - SPRING 2011
 *Februrary 14, 2011
 *
 *Create a program that will allow the user to calculate the final balance 
 *of their energy consumption bill.  The program will calculate the required 
 *user input of electric consumption and water consumption for one of three 
 *categories:Residential, Commecial, and Industrial. The program will only exit
 *until the user wishes to do so.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>
using namespace std; 

int main()
{
	//declaration of variables 
	char response;
	bool anotherCustomer = true;
	char accountName[26]; 
	char ch;
	int i;
	int customerCount = 0;
	int accountNumber;
	double kwh;
	double water;
	
	while (anotherCustomer == true)
	{
		//Step 1
		bool validAccountNumber = false;
		
		//error checking the account number 
			while (validAccountNumber == false) {
		cout << "Enter Account number: ";
		cin >> accountNumber;		
				
			if (accountNumber >= 1000 && accountNumber <= 9999) {
				validAccountNumber = true;
			}else {
				cout << "Please enter in a valid account number." <<endl;
				}

		
			}
		
		//Step 2	
		/*bool validAccountName = false;
		while (validAccountName == false) {
			cout << "Enter Account name: ";
			cin >> accountName;
			if (accountName.length() < 0 || accountName.length() > 25) {
				cout << "Please enter in a valid account name";
			}else {
				validAccountName = true;
			}

		}*/
		
		
		cin.ignore(80, '\n'); // clear input buffer from previous input
		ch = '\0';  // initialize ch to a value (null) that cannot be typed in
		cout << "Enter account name: ";
		i = 0;
		
		while (ch != '\n')// scan characters to the next newline character
		{
			cin.get(ch);
			if (i < 25 && ch != '\n')  // store next character of account name
			{
				accountName[i] = toupper(ch);
				i++;
			}
			else if (i <= 25 && ch == '\n') // end of account name reached
			{
				accountName[i] = '\0';  // make input string be null-terminated
			}
			// else string is too long, and remaining char's are scanned but ignored
		}  // end of while loop
				
		//Step 3
		bool validElectric = false; 
		
		while(validElectric==false){
		cout << endl<< "Enter in the Kwh electirc consumption. ";
		cin >> kwh;
		cout << endl;
		cin.ignore(80,'\n');
			if (kwh <0) {
				cout <<  "Please enter in a valid amount";
			}else {
				validElectric = true;
			}

		}
		
		//Step 4
		bool validWater = false;
		while (validWater==false) {
			cout << "Please enter in water consumption.";
			cin >> water;
			cin.ignore(80,'\n');
			cout << endl;
				if (water < 0) {
					cout << "Please enter in a valid amount";
					cin.ignore(80,'\n');
				}else {
					validWater = true;
				}

		}
		
		//Step 5
		bool validCategory = false;
		char serviceCatergory; 
		
		while (validCategory == false) {
			cout << "Please enter in a service category. (R,C,I)";
			cin.get(serviceCatergory);
				
			
			if (serviceCatergory =='r'||serviceCatergory == 'R') {
				validCategory = true;
			}
			if (serviceCatergory == 'c'||serviceCatergory== 'C') {
				validCategory = true;
			}
			if (serviceCatergory == 'i'||serviceCatergory == 'I')
			{
				validCategory = true;
			}			
		}
		

		
		//Step 6
		double kwhR, kwhC, kwhI;
		double waterR, waterC, waterI;
		double surchargeR, surchargeC, surchargeI;
		
			//residential kwh calculation
				if (serviceCatergory =='r'||serviceCatergory =='R') {
					if (kwh < 500) {
						kwhR = 2.00; 
					}
					if (kwh > 500) {
						kwhR = ((kwh-500.0)*0.025)+25.0; 
					}
					if (kwh>1000) {
						surchargeR = 5.0;
						
					}
				}
			//Residential water calculation
			if (serviceCatergory =='r'||serviceCatergory == 'R') {
				if (waterR < 30) {
					waterR = 2.00; 
				}
				if (water > 30) {
					waterR = ((water-30.0)*0.10)+6.0; 
				}
				
			}
			
			//Commercial kwh calculation
				if (serviceCatergory == 'c'|| serviceCatergory == 'C') {
					if (kwh < 600) {
						kwhC = 10.00;  
					}
					if (kwh > 600) {
						kwhC = ((kwh-600.0)*0.050)+48.0; 
					}
					if (kwh>1500) {
						surchargeC=10.0; 
					}
				}
		
			//Commercial water calculation
				if (serviceCatergory =='c'||serviceCatergory =='C') {
					if (waterC < 30) {
						waterC = 2.00; 
					}
					if (water > 30) {
						waterC = ((water-30.0)*0.15)+6.0; 
					}
				}	
			//Industrial kwh calculation
			if (serviceCatergory =='i'|| serviceCatergory == 'I') {
				if (kwh < 2500) {
					kwhI = 100.0; 
				}
				if (kwh > 2500) {
					kwhR = ((kwh-2500.0)*0.015)+150.0; 
				}
				if (kwh>10000) {
				surchargeI=25.0; 
				}
			}
			
			//Industrial water calculation
			if (serviceCatergory =='i'||serviceCatergory == 'I') {
				if (waterI < 5000) {
					waterI = 50.00; 
				}
				if (water > 5000) {
					waterI = ((water-5000.0)*0.02)+500; 
				}
			}
	
		
		//Step 7
		int j=0;
		int k=0;
		int l=0;
		double electricCharge, waterCharge, surcharge, total; 
		
		
		
		while (j < 80) {
			cout << "*";
			j++;
		}
		cout << endl<<endl;
		cout << setw(25)<<"                    Cumberland Utiltiy District"<<endl<<endl;
		while (k < 80) {
			cout << "*";
			k++;
		}
		cout << endl;
		
		cout << "Account Number : "<< setw(2)<<accountNumber<<endl;
		cout << "Account Name :"<< setw(2)<<accountName<<endl<<endl;
		cout << fixed<<setprecision(2)<<endl;
		
		
		
		if (serviceCatergory == 'r' || serviceCatergory == 'R') {
			
			cout << "Service Category:  Residential" <<endl<<endl;
			electricCharge = kwhR;
			waterCharge = waterR;
			surcharge = surchargeR;
		}
		if (serviceCatergory == 'i' || serviceCatergory =='I') {
			cout << "Service Category:  Industrial" << endl<<endl;
			electricCharge = kwhI;
			waterCharge = waterI;
			surcharge = surchargeI;
		}
		if (serviceCatergory == 'c' || serviceCatergory == 'C') {
			cout << "Service Category:  Commercial"<<endl<<endl;
			electricCharge = kwhC;
			waterCharge = waterC;
			surcharge = surchargeC;
			
		}
		total = electricCharge+waterCharge+surcharge;
		
		cout << "Electric Consumption: "<<setw(4)<<kwh<<setw(25)<<"Electric Charge: $"<<setw(10)<<electricCharge<<endl;
		cout << setw(55)<<"Surcharge: $"<<setw(10)<<surcharge<<endl<<endl;
		cout << "Water Consumption: "<<setw(11)<<water<<setw(24)<<"Water Charge : $"<<setw(10)<<waterCharge<<endl<<endl;
		cout << setw(55)<<"Total Charge: $"<<setw(10)<<total<<endl;
		
		
		
		while (l < 80) {
			cout << "*";
			l++;
		}
		cout << endl;
		
		
		//Step 8
		customerCount++;
		cout << "Process another customer? Enter y/n ";
		cin >> response;
		cin.ignore(80,'\n');
		cout << endl;
		if (response =='n') anotherCustomer = false;
		
	}
	cout << "There were " <<customerCount<< " bills processed.";
	return 0; 
}