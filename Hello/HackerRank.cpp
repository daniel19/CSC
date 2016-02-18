#ifndef HACKERANK
#define HACKERANK

#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cctype>
#include <cassert>
#include <boost/algorithm/string/trim.hpp>
#include "ColorMod.h"

namespace HackerRank{
    static void hello(std::string word){
        std::cout << "Hello from Hacker World " << word << " " << std::endl;
    }

    template<class T>
    static void logMessage(T variable, std::string message){
        using namespace std;
        ColorMod mod(ColorCode::BG_RED);
        ColorMod close(ColorCode::BG_CLOSE);
        ColorMod vmod(ColorCode::FG_MAGENTA);
        ColorMod vClose(ColorCode::FG_CLOSE);

        auto system_time = std::chrono::system_clock::now();
        auto output_time = std::chrono::system_clock::to_time_t(system_time);
        std::string sTime(std::ctime(&output_time));
        sTime = sTime.substr(0, sTime.length() -1);
        cout << mod << sTime << close << ": " << vmod << variable << vClose << " : " << message << endl;
    }

    static void printCharArrary(char* array){
        while(*array){
            std::cout << *(array++)<< " " ;
        }
        std::cout<< std::endl;
    }

    static auto split(std::string original, char delimeter) -> std::vector<std::string>{
        std::vector<std::string> result;
        size_t length = original.length();
        std::string temp = "";

        for(size_t i = 0; i < length; i++){
            if(original[i] == delimeter){
                result.push_back(temp);
                temp = "";
            }else{
                temp = temp + original[i];
            }
        }
        result.push_back(temp);
        return result;
    }

    static auto split(std::string original, std::string delimeters) -> std::vector<std::string>{
        std::vector<std::string> result;
        for(auto character : delimeters){
            auto r = split(original, character);
            result.insert(result.end(), r.begin(), r.end());
            //remove tokens from original copy
            for(auto token : result){
                size_t position = delimeters.find_first_of(character, 0);
                auto cp = delimeters.substr(position+1, delimeters.length());

                if(token.find(cp) == std::string::npos){
                    size_t i = original.find(token);
                    if(i != std::string::npos){
                        original.erase(i, token.length());
                        logMessage(original, "bounce");
                        boost::algorithm::trim(original);
                    }
                }
            }
        }
        return result;
    }

    template<class T>
    static void printVector(std::vector<T> vector, ColorCode code, ColorCode codeClose){
        ColorMod mod(code);
        ColorMod close(codeClose);
        for(auto element : vector){
            std::cout << mod << element << " " << close ;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    static bool isSingleDigit(int number){
        if(number < 0) number*=-1;
        return number > 0 && number < 10;   
    }

    static void timeConversion(std::vector<std::string> times){
        std::vector<std::string> result;
        for(std::string time : times){
            std::cout << time << std::endl; //format HH:mm:s AM/PM
            auto tokens = split(time, ':');
            int quadrant = 0;
            std::vector<uint> numbers;
            std::string dayOrNight = "";
            for(auto token : tokens){
                std::string s;
                for(auto character : token){
                    if(std::isdigit(character)){
                        s+= character;
                    }else{
                        dayOrNight += character;
                    }
                }
                numbers.push_back(std::stoi(s));
            }

            boost::algorithm::trim(dayOrNight);//too lazy to write own trim function
            std::string r = "";
            for(auto &number : numbers){
                if(quadrant == 0){
                    assert(number <= 12);
                    if(dayOrNight == "PM")
                        number +=12;
                    else if(dayOrNight == "AM" && number ==12)
                        number = 0;

                    quadrant++;
                }
                //check if number is a single digit
                if(isSingleDigit(number)){
                    r += "0";
                }
                r += std::to_string(number);
                r += ":";
            }
            r.erase(r.length() -1, r.length());
            boost::algorithm::trim(r);
            result.push_back(r);
        }
        printVector(result, ColorCode::FG_GREEN, ColorCode::FG_CLOSE);
    }

}
#endif
