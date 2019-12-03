#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

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


Doc::chunkNode * Doc::chunkHashFile(vector<string> chunkedFile){ //creates hash table size
    int chunkLength = chunkedFile.at(0).size();
    int arraySize = 0;
    string chunk = chunkedFile.at(0);
    for (int i = 0; i < chunkLength - 1; i++){
        arraySize += chunk[chunkLength - i - 1] * pow(37, i);
    }
    chunkNode hashTable[arraySize];
    return (hashTable);
}

int Doc::CheckPlagarism(string &fileName1, string &fileName2, int chunkSize){
    vector<string> file1 = chunkFile(chunkWordFile(readFile(fileName1), chunkSize), chunkSize);
    vector<string> file2 = chunkFile(chunkWordFile(readFile(fileName2), chunkSize), chunkSize);
    Doc:chunkNode *hashTable = chunkHashFile(file1);
    int chunkLength = file1.at(0).size();
    string chunk = file1.at(0);
    int key;
    int collisions = 0;
    for (int i = 0; i < file1.size(); i++) { // hashs first file
        key = 0;
        chunk = file1.at(i);
        chunkLength = file1.at(i).size();
        for (int i = 0; i < chunkLength - 1; i++) {
            key += chunk[chunkLength - i - 1] * pow(19, i);
        }
        chunkNode *temp = new chunkNode;
        temp -> fileName = fileName1;
        temp -> next = NULL;
        hashTable[key] = *temp;
    }
    for (int i = 0; i < file2.size(); i++) { // hashs first file
        key = 0;
        chunk = file2.at(i);
        chunkLength = file2.at(i).size();
        for (int i = 0; i < chunkLength - 1; i++) {
            key += chunk[chunkLength - i - 1] * pow(19, i);
        }
        if (hashTable[key].fileName == fileName1){
            chunkNode *temp = new chunkNode;
            temp -> fileName = fileName2;
            temp -> next = NULL;
            hashTable[key].next = temp;
            collisions++;
        }
    }
    return collisions;
}

int Doc::getdir(string dir, vector<string> &files){

}
void Doc::printChunkedFile(){ //milestone 1 function

}

