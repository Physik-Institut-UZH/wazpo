#ifndef WAZAAAAAA
#define WAZAAAAAA

#include <vector>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"

#include "branchHolder.h"
#include "addOn.h"


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
    addOn a;
};

#endif