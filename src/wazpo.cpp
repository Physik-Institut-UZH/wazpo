#include <iostream>

#include "argh.h"

#include "TTree.h"
#include "TFile.h"
#include "TString.h"

#include "branchHolder.h"
#include "wazLooper.h"
#include "utils.h"

using namespace std;

int main(int argc, char** argv)
{
    logo();

    argh::parser cmdl;
    cmdl.add_params({ "--file", "--config","-h", "-o"});
    cmdl.parse(argc, argv);

    if( cmdl[{"-h","--help"}] ) {
        cout << "Usage: \n wazpo --config <config_file_path> --file <root_file_path> --out <root_file_path>\n\n" << endl;
        return 0;
    }

    TString filepath = cmdl("file").str();
    TString configpath = cmdl("config").str();
    TString outpath = cmdl({"o","out"}).str();
    
    if(outpath == "" ) { cout << "must specify output file."<< endl; return 0; }
    
    cout << "Running on file: "<<  filepath << endl;
    cout << "Using config: "<<  configpath << endl;

    TFile *f = TFile::Open(filepath);
    if(f == NULL) { cout << "file: " << filepath << "  not found. " << endl; return 0; }

    TTree *p = (TTree*) f->Get("T1");

    wazLooper looper(p, configpath, outpath);

    // here is where the add-ons are turned on/off and new branches are added
    looper.initializeAddons();
    
    // runs over all entries, reading old tree, computing add-ons, filling new tree
    looper.Loop();

    // write new file with new tree to disk
    looper.write();


    f->Close();
    delete f;


    return 0;
}
