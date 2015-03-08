#include "FileIO.h"

FileIO::FileIO(string filename, int operation){
    if(operation == FOR_READING || operation == FOR_WRITING){
        setting = operation;
    }else{
        cerr << "Specify File operation.\n";
    }

    fileReader.open(filename);
    
    if(fileReader.fail()){
        cerr << "No File Found\n";
        endOfFile = true;
    }
    if(setting == FOR_READING){
        //For Reading    
    }else if(setting == FOR_WRITING){
        //For Writing    
    }
}

FileIO::FileIO(string filename, string delimeter){
    setting = FOR_READING;
    tokens = true;
    this->delimeter = delimeter; 
    fileReader.open(filename);

    if(fileReader.fail()){
        cerr << "No File Found\n";
        endOfFile = true;
    }
}

vector<string> FileIO::getTokens(){
    vector<string> tokenList;
    if(tokens && !endOfFile){
        string temp = FileIO::readLine();
        char* cstring = const_cast<char*>(temp.c_str());
        char *tokens = strtok(cstring, delimeter.c_str());
        while(tokens != NULL){
            tokenList.push_back(tokens);
            tokens = strtok(NULL,delimeter.c_str());
        }
    }
    return tokenList;
}

string FileIO::readLine(){
    char temp[256];
    if(setting == FOR_READING){
        if(!fileReader.eof()){
            fileReader.getline(temp, 1000);
        } else{
            endOfFile = true;
            return "";
        }
    }else{ 
        cerr << "File is for writing only.\n";
    }
    return string(temp);
}

void FileIO::writeLine(string line){
   if(setting == FOR_WRITING){
     fileReader.write(line.c_str(), line.length());
   }else{
     cerr << "File is for Reading only.\n";
   }  
}

void FileIO::close(){
    fileReader.close();
}

void FileIO::status(){
    cout << "File size: " << fileReader.peek() << endl;
    cout << "Ready to read: " << fileReader.good() << endl;
}
