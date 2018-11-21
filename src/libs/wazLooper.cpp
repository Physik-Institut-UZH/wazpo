#include "wazLooper.h"
#include "../add_ons/add_posrec.hpp"  // this must be here, because of mixed includes
                                    // <---- add other includes for add on here ADD_ON_MODIFY_HERE

wazLooper::wazLooper(TTree *loadedTree, TString configfile, TString outpath) : branchHolder(loadedTree){

    
    out_file = new TFile(outpath,"RECREATE");
    if(out_file->IsOpen() == false ){
        cout << "ERROR: maybe out file dir does not exist." << endl;
        exit(200);
    }

    // cloning tree: important! this must be done after creating the new file above
    out_tree = fChain->CloneTree();

    config = YAML::LoadFile(configfile.Data()); 

    addons.clear();
}

wazLooper::~wazLooper(){

}

void wazLooper::initializeAddons(){
    
    // Setting up addons... This is hardcoded unfortunately
    // couldn't come up with something less verbose than this...
    if( addOnListContains("posrec")) 
        addons.push_back( new add_posrec(this,  getConfigFor("posrec")) );

        // <--- Add same syntax as above for your addon here  ADD_ON_MODIFY_HERE  

    // turning off all default branches
    out_tree->SetBranchStatus("*",0);

    // initializing addons 
    for (unsigned int k=0; k < addons.size() ; k++){
        addons[k]->init( out_tree );
    }
    

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
        for(unsigned int k =0; k< addons.size(); k++){
            addons[k]->apply();
        }

        out_tree->Fill();
        progressBar((float) jentry / (float) nentries );
        

    }
    progressBar(1.);
    cout << "\n DONE! \n\n" << endl;

}

void wazLooper::analyzeEvent(int event){

    setPlotMode(event);

    if (fChain == 0)
        return;
    Long64_t ientry = LoadTree(event);
    if (ientry < 0){
        cout << "Error: max entry is: " << fChain->GetEntries() << endl;
        return;
    }

    TRandom rambo;
    rambo.SetSeed(0);
    while(1){
    event = (int) rambo.Uniform(fChain->GetEntries());
    cout << "Running on event " << event << endl; 
    fChain->GetEntry(event);
    out_tree->GetEntry(event);

    // Here we do our magic
    for(unsigned int k =0; k< addons.size(); k++){
        addons[k]->apply();
    }
    int status = system( "gwenview test.png" );
    }
}

void wazLooper::write(){
    
    out_file->cd();
    out_tree->SetBranchStatus("*",1);
    out_tree->Write();
    out_file->Close();
    delete out_file;

}


void wazLooper::progressBar(float progress ){

        int barWidth = 70;

        cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << int(progress * 100.0) << " %\r";
        cout.flush();
 
}


YAML::Node wazLooper::getConfigFor( string addOnName ){
    
    YAML::Node tmp_config;
    
    if(config[addOnName])
         tmp_config = config[addOnName];
    else tmp_config = YAML::Load("emptyconfig : true");
     
    return tmp_config;


}

bool wazLooper::addOnListContains(TString addOnName){
    YAML::Node addOnslist = config["addons"];
    bool isThere = false;

    for (YAML::const_iterator it=addOnslist.begin();it!=addOnslist.end();++it) {
        if(it->as<std::string>() == addOnName.Data() ) isThere = true;

    }
    return isThere;

}
