#include <iostream>
#include <vector>
using namespace std;

class Sorting{
    private:
        Sorting(){};
        static Sorting* sorter;
        template<typename T> static void printVector(vector<T> array){
            for(int i=0; i < array.size(); i++){
                cout << array[i] << " ";
            }
            cout << endl;
        }
        
        template<typename T> static int partition(vector<T>& array, int low, int high){
            int pIndex = high;
            T pivot = array[pIndex];
            int storeIndex = low;
            for(int i=low; i< high; i++){
                if(array[i] < pivot){
                    swap(array[i], array[storeIndex]);
                    storeIndex++;
                }
            }
            swap(array[storeIndex], array[high]);
            return storeIndex;
        }
        
        template<typename T> static void quickSort_InPlace(vector<T>& array, int low, int high){
            if((high-low) <= 0){ return;}
            
            int position = partition(array, low, high);
            quickSort_InPlace(array, low, position-1);
            quickSort_InPlace(array, position+1, high);
            //printVector(array);
        }
    public:
        static Sorting *Instance(){
           if(!sorter){ 
              sorter = new Sorting;
           } 
           return sorter;
        }
 
        template<typename T> static vector<T> insertionSort(vector<T> array){
            int shifts =0;
            for(int i=1; i < array.size(); i++){
                T temp = array[i];
                int postion = i;
                while(postion >0 && temp < array[postion-1]){
                    array[postion] = array[postion-1];
                    postion--;
                    shifts++;
                }
                array[postion] = temp;
                //printVector(array); 
            }
            cout << "Number of shifts: " << shifts << endl;
            return array;
        }

        template<typename T> static vector<T> bubbleSort(vector<T> array){
            bool sorted = false;
            int j =0;
            while(!sorted){
                sorted = true;
                for(int i=0; i < array.size() -j; i++){
                   if(array[i] < array[i-1]){
                        swap(array[i], array[i-1]);//comes from vector class
                        sorted = false;
                   }
                }
                //printVector(array);
            }

            return array;
        }
       
        template<typename T> static vector<T> quickSort(vector<T> array){
            vector<T> pivoted;
            if (array.size() <=1){
                return array; //Do no work
            }else{ 
                T pivot = array[0];//takes more space
                vector<T> left, right;
                for(int i=1; i<array.size(); i++){
                    if(array[i] <= pivot)
                        left.push_back(array[i]);
                    else
                        right.push_back(array[i]);
                }
                
                left = quickSort(left); 
                right = quickSort(right);
                pivoted.reserve(left.size() + right.size());
                pivoted.insert(pivoted.end(), left.begin(), left.end());
                pivoted.push_back(pivot);
                pivoted.insert(pivoted.end(), right.begin(), right.end());
            }
                //printVector(pivoted);
                return pivoted;
        }
        
        template<typename T> static void quickSort_InPlace(vector<T>& array){
            if(array.size() <=1){
                return;
            }
            quickSort_InPlace(array, 0, array.size()-1);
        }

};

Sorting* Sorting::sorter = NULL;
