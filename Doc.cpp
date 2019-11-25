#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
            inString[i] = 0x0; //equals NULL if not capital or normal letter
        }
    }
    return inString;
}

vector<Doc::chunkNode> Doc::chunkFile(string inString, int chunkSize){ //chunks into n-word sequences (needs to be fixed NOT DONE!!)
    vector<Doc::chunkNode> chunkedFile;
    int strLength = inString.length();
    int wordCounter = 0;
    string inputWord = "";
    string inputChunk = "";
    int i = 0;
    while (i < strLength) {
        while (wordCounter < chunkSize) {
            if (inString[i] != 0x20) {
                inputWord += inString[i];
            } else {
                inputChunk += inputWord;
                inputWord = "";
                wordCounter++;
            }
            i++;
        }
        chunkNode temp = new chunkNode;
        temp->data = inputWord;
        temp->next = NULL;
        chunkedFile.push_back(temp);
    }
}

vector<Doc::chunkNode> Doc::chunkHashFile(string inString){ //chunks into n-word sequences and applys hash function to it

}

int Doc::getdir(string dir, vector<string> &files){

}
void Doc::printChunkedFile(){ //milestone 1 function

}

