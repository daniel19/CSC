#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "HackerRank.cpp"

auto runHackerRank() -> bool{
    using namespace HackerRank;
    HackerRank::hello("Bjarne");
    std::vector<std::string> times = { "02:04:42PM", "01:02:23 PM", "08:23:12 AM", "01:04:42AM"};
    HackerRank::timeConversion(times);
    auto result = HackerRank::split("The quick/smart brown fox jumped over the lazy rabbit/salamander", " /");
    HackerRank::printVector(result, ColorCode::BG_BLUE, ColorCode::BG_CLOSE);
    return true;
}

int main(){
    auto hello = "Hello World...Again";
    std::cout << hello << std::endl;
    while(1){
        if(runHackerRank())
            break;
    }
    return 0;
}
