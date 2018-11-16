#include "wazLooper.h"


wazLooper::wazLooper(TTree *loadedTree) : branchHolder(loadedTree), a(this) {

    fChain->Print();
    
    out_file = new TFile("test.root","RECREATE");
    // cloning tree: important! this must be done after creating the new file above
    out_tree = fChain->CloneTree();

    out_tree->Print();

    //addOns.clear();
    //addOns.push_back(new addOn(this));
}

wazLooper::~wazLooper(){

}

void wazLooper::initializeAddOns(){
    out_tree->SetBranchStatus("*",0);
    test_branch = 42;
    out_tree->Branch("test_branch",&test_branch,"test_branch/F");

    

}

void wazLooper::Loop(){
    
    if (fChain == 0)
        return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0)
            break;
        nb = fChain->GetEntry(jentry);
        out_tree->GetEntry(jentry);
        nbytes += nb;

        // Here we do our magic
        a.run();
        out_tree->Fill();
        

    }

}

void wazLooper::write(){
    
    out_file->cd();
    out_tree->Write();
    out_file->Close();
    delete out_file;

}
