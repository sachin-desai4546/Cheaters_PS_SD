#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <dirent.h>

#include "Doc.h"

using namespace std;

string Doc::readFile(string &fileName) {
    string outFile;
    ifstream inFile;
    inFile.open(fileName);
    string s;
    inFile >> s;
    while (inFile) {
        outFile += s + " ";
        inFile >> s;
    }
    return cleanFile(outFile);
}

string Doc::cleanFile(string &inString) { //removes punctation, and captiatlization
    int strLength = inString.length();
    for (int i = 0; i < strLength; i++) {
        if (inString[i] > 0x40 && inString[i] < 0x5B) {
            inString[i] += 0x20;
        } else if (inString[i] < 0x61 || inString[i] > 0x7A) {
            if(inString[i] != 0x20)
                inString[i] = 0x0; //equals NULL if not capital or normal letter
        }
    }
    return inString;
}

vector<string> Doc::chunkWordFile(string inString, int chunkSize){ //chunks into n-word sequences (needs to be fixed NOT DONE!!)
    vector<string> chunkWordFile;
    int strLength = inString.length();
    int wordCounter = 0;
    string inputWord = "";
    int i = 0;
    while (i < strLength) {
        if (inString[i] != 0x20) {
            inputWord += inString[i];
        } else {
            chunkWordFile.push_back(inputWord);
            inputWord = "";
        }
        i++;
    }
    return chunkWordFile;
}

vector<string> Doc::chunkFile(vector<string> inVector, int chunkSize) {
    int vectorSize = inVector.size();
    vector<string> chunkedFile;
    string inputChunk = "";
    int j = 0;
    while (j < vectorSize - chunkSize) {
        for (int i = 0; i < chunkSize; i++) {
            inputChunk += inVector.at(i);
        }
        chunkedFile.push_back(inputChunk);
        inputChunk = "";
    }
    return (chunkedFile);
}


vector<int>* Doc::createHashTable(string &fileName, int chunkSize, vector<string> &files){ //creates hash table, and hashes the first file
    int fileVal;
    vector<string> file = chunkFile(chunkWordFile(readFile(fileName), chunkSize), chunkSize);
    for(int i = 0; i < files.size(); i++){
        if(fileName == files.at(i))
            fileVal = i;

    }
    int chunkLength = file.at(0).size();
    int arraySize;
    int key;
    string chunk = file.at(0);
    for (int i = 0; i < chunkLength - 1; i++){
        arraySize += chunk[chunkLength - i - 1] * pow(37, i);
    }

    vector<int> *hashTable = new vector<int>[arraySize];

    for (int l = 0; l < arraySize; l++){
        hashTable[l].push_back(-1);
    }
    for (int j = 0; j < file.size(); j++) { // hashs file
        key = 0;
        chunk = file.at(j);
        chunkLength = file.at(j).size();
        for (int k = 0; k < chunkLength - 1; k++) {
            key += chunk[chunkLength - k - 1] * pow(19, k);
        }
        hashTable[key].push_back(fileVal);
    }
    return (hashTable);
}

void Doc::addFile(string &fileName, vector<int>* hashTable, int *counter[], int chunkSize, vector<string> &files){
    int keyLoop;
    int fileVal;
    vector<string> file = chunkFile(chunkWordFile(readFile(fileName), chunkSize), chunkSize);
    for(int i = 0; i < files.size(); i++){
        if(fileName == files.at(i))
            fileVal = i;

    }
    int chunkLength = file.at(0).size();
    int collisions;
    int key;
    string chunk = file.at(0);
    for (int i = 0; i < file.size(); i++) { // hashs first file
        key = 0;
        chunk = file.at(i);
        chunkLength = file.at(i).size();
        for (int l = 0; l < chunkLength - 1; l++) {
            key += chunk[chunkLength - l - 1] * pow(19, l);
        }
        if (hashTable[key][0] == -1){
            hashTable[key][0] = fileVal;
        } else{
            collisions++;
            keyLoop = 0;
            while(hashTable[key][keyLoop] != -1){
                keyLoop++;
            }
            hashTable[key][keyLoop] = fileVal;
        }
    }
    counter[fileVal][fileVal] = collisions;
}


int getdir(string dir, vector<string> &files){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


