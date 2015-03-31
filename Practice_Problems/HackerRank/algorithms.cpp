#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <ctime>
#include <boost/multiprecision/cpp_int.hpp>
#include "../Library/FileIO.h"
#include "../Library/Sorting.h"

using namespace std;

//typedef unsigned long long int longerInt;
typedef boost::multiprecision::cpp_int  longerInt;

bool display();
int solveMeFirst(int n, int k);
string isFibo(longerInt n);
longerInt fibonacci(longerInt n);
longerInt fibIt(longerInt n);
bool isPerfectSquare(longerInt n);
template<typename T> static void printVector(vector<T> array);

int main(){
    bool running = true;
    while(running){ running = display(); }
}


bool display(){
    cout <<"1) Solve Me First\n2) IsFibo\n3)Sorting" << endl;
    cout << "Please enter in your menu option: ";
    int choice;
    cin >> choice;
    
    switch(choice){
        case 1:
        {
            int num1, num2, sum;
            cout << "Enter in two numbers: ";
            cin >> num1 >> num2;
            sum = solveMeFirst(num1, num2);
            cout << sum << endl;
            break;
        }
        case 2:
        {
            FileIO *reader = new FileIO("bin/test.txt", FileIO::FOR_READING);
            int numberOfFiles = stoi(reader->readLine(),NULL);
            int count = 0;
            while(count < numberOfFiles){
                string line = reader->readLine();
                longerInt number = atoll(line.c_str());
                cout << number << " - " << isFibo(number) << endl;
                count++;
                break;
            } 
        }
        case 3:
        {
            string filename;
            cout << "Enter in your array input file: ";
            getline(cin.ignore(), filename);
            FileIO *reader = new FileIO(filename, FileIO::FOR_READING);
            vector<int> list;
            while(!reader->endOfFile){
                string line = reader->readLine();
                if(!line.empty())
                    list.push_back(atoi(line.c_str()));
            }
            cout << "List size is: " << list.size() << endl;
           vector<int> copyList = list; 
            cout << "List size is: " << copyList.size() << endl;
            if(list.size() >0){ 
               // Sorting Sorter = Sorting::getInstance(); 
                Sorting *Sorter; 
                cout << &Sorter << endl;
                
                clock_t timer;       
                cout << "Insertion Sort\n" << endl;
                timer = clock();
                Sorter->insertionSort(list);
                cout << "\nTime spent on insertionSort: " << (float)(clock() - timer)/CLOCKS_PER_SEC << endl; 
                
                cout << "Bubble Sort\n" << endl;
                timer = clock();
                Sorter->bubbleSort(list);
                cout << "\nTime spent on bubbleSort: " << (float)(clock() - timer)/CLOCKS_PER_SEC << endl; 
                
                cout << "\nQuickSort\n" << endl;
                timer = clock();
                Sorter->quickSort(list);
                cout << "\nTime spent on quickSort: " << (float)(clock() - timer)/CLOCKS_PER_SEC << endl; 

                cout << "\nQuickSort InPlace\n" << endl;
                timer = clock();
                Sorter->quickSort_InPlace(list);
                cout << "\nTime spent on quickSort_InPlace: " << (float)(clock() - timer)/CLOCKS_PER_SEC << endl; 
                
                cout << "\nMergeSort\n" << endl;
                timer = clock();
                Sorter->mergeSort(copyList);
                cout << "\nTime spent on quickSort_InPlace: " << (float)(clock() - timer)/CLOCKS_PER_SEC << endl; 
                
                printVector(copyList);
            }
            break;
        }
    }
    cout << "Do you want to continue? (y/n) ";
    char answer;
    cin >> answer;
    if(answer == 'y' || answer == 'Y'){
        return true;
    }
    return false;
}

int solveMeFirst(int n, int k){ return n+k; }

string isFibo(longerInt n){
    return ((isPerfectSquare(5*n*n -4) || isPerfectSquare(5*n*n+4)) ? "isFibo" : "isNotFibo");
}

longerInt fibonacci(longerInt n){
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

longerInt fibIt(longerInt n){
    if(n==0) return 0;
    if(n==1) return 1;

    longerInt prevP=0, prev=1, result=0;
    for(longerInt i = 2; i<=n; i++){
        result = prev+ prevP;
        prevP = prev;
        prev = result;
    }
    return result;
}

bool isPerfectSquare(longerInt n){
    longerInt square = sqrt(n);
    return (square*square == n);
}

template<typename T> static void printVector(vector<T> array){
    for(int i=0; i < array.size(); i++){
        cout << array[i] << " ";
    }
    cout << endl;
}
