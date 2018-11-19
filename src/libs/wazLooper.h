#ifndef WAZAAAAAA
#define WAZAAAAAA

#include <vector>

#include "yaml-cpp/yaml.h"

#include "TString.h"
#include "TTree.h"
#include "TFile.h"

#include "branchHolder.h"
#include "addon.h"

using namespace std;

class wazLooper :public branchHolder {
    public:

    wazLooper(TTree *loadedTree, TString configfile, TString outpath);
    ~wazLooper();
    
    void write();
    void Loop();
    void initializeAddons();
    void progressBar(float progress);
    YAML::Node getConfigFor( string addOnName );
    bool addOnListContains(TString addOnName);

    TTree *out_tree;
    TFile *out_file;
    float test_branch;
    YAML::Node config;
    vector<addOn*> addons;
};

#endif