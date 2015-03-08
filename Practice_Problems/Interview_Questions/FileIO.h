#ifndef FileIO_H
#define FileIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class FileIO{

    public:
        const static int FOR_READING = 1;
        const static int FOR_WRITING = 2;
        bool endOfFile;
        
        FileIO(string filename, int operation);
        FileIO(string filename, string delimeter);
        vector<string> getTokens();
        string readLine();
        void writeLine(string line);
        void close();
        void status();
    private:
        int setting;
        fstream fileReader;
        bool tokens;
        string delimeter;
};

#endif
