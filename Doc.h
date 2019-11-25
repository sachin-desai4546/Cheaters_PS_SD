#include <iostream>
#include <vector>
#include <string>

#ifndef _DOC_H
#define _DOC_H
using namespace std;

class Doc
{
public:

    struct chunkNode {
        string data;
        chunkNode *next;
    };

    string readFile(string &fileName);
    string cleanFile(string &inString); //removes punctation, and captiatlization
    vector<chunkNode> chunkFile(string inString, int chunkSize); //chunks into n-word sequences
    vector<chunkNode> chunkHashFile(string inString);
    int getdir(string dir, vector<string> &files);
    void printChunkedFile(); //milestone 1 function


private:

};

#endif