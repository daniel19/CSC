#include <iostream>
#include <vector>
using namespace std;

/**
 *This is a singleton class that is used to demonstrate the different types
 * of sorting algortihms. The containing structure is a vector that can hold
 * any comparable data types. 
 **/

class Sorting{
    private:
        Sorting();
        static Sorting& sorter;
        Sorting(Sorting const&);
        void operator=(Sorting const&);
        template<typename T> void printVector(vector<T> array){
            for(int i=0; i < array.size(); i++){
                cout << array[i] << " ";
            }
            cout << endl;
        }
        template<typename T> int partition(vector<T>& array, int low, int high){
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
        template<typename T> void quickSort_InPlace(vector<T>& array, int low, int high){
            if((high-low) <= 0){ return;}
            
            int position = partition(array, low, high);
            quickSort_InPlace(array, low, position-1);
            quickSort_InPlace(array, position+1, high);
            //printVector(array);
        }

        template<typename T> void merge(vector<T> left, vector<T> right, vector<T>& array){
            int i=0, j=0, k=0;
            while(i < left.size() && j < right.size()){
               if(left[i] <= right[j]){
                  array[k] = left[i]; 
                  i++;
               }else{
                   array[k] = right[j];
                   j++;
               }
               k++;
            }
            while(i < left.size()){
                array[k] = left[i];
                i++;
                k++;
            }
            while(j < right.size()){
                array[k] = right[j];
                j++;
                k++;
            }
        }
    
    public:
        static Sorting& getInstance();
        template<typename T> vector<T> insertionSort(vector<T> array){
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
        template<typename T> vector<T> bubbleSort(vector<T> array){
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
        template<typename T> vector<T> quickSort(vector<T> array){
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
        template<typename T> void quickSort_InPlace(vector<T>& array){
            if(array.size() <=1){
                return;
            }
            quickSort_InPlace(array, 0, array.size()-1);
        }

        template<typename T> void mergeSort(vector<T>& array){
            if(array.size() <=1)
                return;
            int mid = array.size()/2;
            vector<T> left, right;
            left.reserve(mid);
            left.insert(left.end(), array.begin(), array.begin()+mid); 
            
            right.reserve(array.size() - mid);
            right.insert(right.end(), array.begin()+(mid), array.end()); 

            mergeSort(left);
            mergeSort(right);
            merge(left,right,array);
        }
        
};
