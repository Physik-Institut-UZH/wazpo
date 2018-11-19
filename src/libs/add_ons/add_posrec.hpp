#include "../addon.h"
#include "../wazLooper.h"  

#ifndef ADDPOSREC
#define ADDPOSREC

using namespace std;

class add_posrec : public addOn {
    public:
    
    add_posrec(wazLooper *wzl, YAML::Node conf ): addOn(wzl, conf){};
 
    void init(TTree *out_tree){
        cout << "Adding posrec with config: "<< endl;

        if (config["treshold"]) {
            cout << " ---> treshold  " << config["treshold"].as<string>() << "\n";
        }
        test_branch = 42;
        out_tree->Branch("test_branch",&test_branch,"test_branch/F");

    }
    void apply(){

       test_branch = (float)looper->Time ;
    }

    float test_branch;
};

#endif

