#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

#ifndef _DOC_H
#define _DOC_H
using namespace std;

class Doc
{
public:

    struct chunkNode {
        string fileName;
        chunkNode *next;
    };

    string readFile(string &fileName);
    string cleanFile(string &inString); //removes punctation, and captiatlization
    vector<string> chunkWordFile(string inString, int chunkSize); //chunks into n-word sequences
    chunkNode * chunkHashFile(vector<string> chunkedFile);
    vector<string> chunkFile(vector<string> inVector, int chunkSize);
    int CheckPlagarism(string &fileName1, string &fileName2, int chunkSize);
    int getdir(string dir, vector<string> &files);
    void printChunkedFile(); //milestone 1 function


private:

};

#endif