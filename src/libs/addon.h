
#ifndef ADD_ONS
#define ADD_ONS

#include <iostream>

#include "yaml-cpp/yaml.h"

#include "TTree.h"
#include "TString.h"

class wazLooper; // forward declaration needed 

using namespace std;

/* class addOn
 * virtual class for writing addons branches. 
 * It must implement the methods:
 * init() to configure the branches in new tree
 * apply() to compute the new branches values, this function is called at each loop.
 *  
*/
class addOn {

    public:
        addOn(wazLooper *wzl, YAML::Node conf ){ looper = wzl; config = conf;  };

        void setLooper(wazLooper *wzl){looper = wzl; };

        virtual void init( TTree *newTree ) = 0;
        
        virtual void apply() = 0;

        wazLooper *looper;
        YAML::Node config;
        TString name;

};

#endif
