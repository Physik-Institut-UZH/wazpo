#ifndef WAZAAAAAA
#define WAZAAAAAA

#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "yaml-cpp/yaml.h"

#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
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
    void setPlotMode(int evnt) {plotmode = true; event = evnt;};
    void analyzeEvent(int event);

    TTree *out_tree;
    TFile *out_file;
    float test_branch;
    YAML::Node config;
    bool plotmode;
    int event;
    vector<addOn*> addons;
};

#endif