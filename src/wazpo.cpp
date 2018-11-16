#include "yaml-cpp/yaml.h"

#include <iostream>

#include "TTree.h"
#include "TFile.h"

#include "branchHolder.h"
#include "wazLooper.h"
#include "utils.C"

using namespace std;

int main(int argc, char** argv)
{
    logo();

    TFile *f = TFile::Open("../../mock_data/processed_kryton_test_181108.root");
    TTree *p = (TTree*) f->Get("T1");

    wazLooper looper(p);

    // looper.setConfigs();

    // here is where new branches are added
    looper.initializeAddOns();
    
    // runs over all entries, reading old tree, computing add-ons, filling new tree
    looper.Loop();

    // write new file with new tree to disk
    looper.write();


    f->Close();
    delete f;


    return 0;
}
