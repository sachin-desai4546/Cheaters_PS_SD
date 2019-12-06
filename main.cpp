#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>

#include "Doc.h"

using namespace std;

int main()
{
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    getdir(dir,files);
    int chunkSize = 6;
    files.erase(files.begin());
    files.erase(files.begin());
    for (unsigned int i = 0; i < files.size(); i++) {
        cout << files[i] << endl;
    }
    int fileSize = files.size();
    int *collisions[fileSize];
    vector<int>* hashT = createHashTable(files[0], dir, chunkSize, files);
    for (int i = 0; i < fileSize; i++){
        addFile(files[i], dir, hashT, collisions, chunkSize, files);
    }

    return 0;
}