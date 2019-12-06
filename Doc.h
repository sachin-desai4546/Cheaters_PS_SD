#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

#ifndef _DOC_H
#define _DOC_H
using namespace std;

string readFile(string &fileName, string &dir);
string cleanFile(string &inString); //removes punctation, and captiatlization
vector<string> chunkWordFile(string inString, int chunkSize); //chunks into n-word sequences
vector<int>* createHashTable(string &filename, string &dir, int chunkSize, vector<string> &file);
vector<string> chunkFile(vector<string> inVector, int chunkSize);
void addFile(string &fileName, string &dir, vector<int>* hashTable, int *counter[], int chunkSize, vector<string> &files);
int getdir(string dir, vector<string> &files);


#endif