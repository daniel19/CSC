#include "Sorting.h"
        
Sorting::Sorting(){};

Sorting& Sorting::getInstance(){
    static Sorting sorter;
    return sorter;
}
