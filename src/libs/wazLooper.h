#ifndef WAZAAAAAA
#define WAZAAAAAA

#include "branchHolder.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"

using namespace std;

class wazLooper :public branchHolder {
    public:

    wazLooper(TTree *loadedTree);
    ~wazLooper();
    
    void write();
    void Loop();
    void initializeAddOns();

    TTree *out_tree;
    TFile *out_file;
    float test_branch;
};

#endif