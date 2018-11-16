#ifndef ADD_ONS
#define ADD_ONS

#include <iostream>

#include "branchHolder.h"


class wazLooper; // forward declaration 

using namespace std;

class addOn {

    public:
        addOn(wazLooper *wzl ){ looper = wzl;};

        void setLooper(wazLooper *wzl){ looper = wzl; };

        void run();

        wazLooper *looper;


};

#endif
