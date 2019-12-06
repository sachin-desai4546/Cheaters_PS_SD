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
    vector<int>* createHashTable(string &filename, int chunkSize, vector<string> &file);
    vector<string> chunkFile(vector<string> inVector, int chunkSize);
    void addFile(string &fileName, vector<int>* hashTable, int *counter[], int chunkSize, vector<string> &files);


private:

    int arraySize;

};

int getdir(string dir, vector<string> &files);


#endif