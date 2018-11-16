#include "yaml-cpp/yaml.h"

#include <iostream>

#include "TTree.h"
#include "branchHolder.h"

using namespace std;

int main(int argc, char** argv)
{
    std::cout << "ciao it works! even better" << std::endl; 

    TTree *p = new TTree("pollo","bla");

    branchHolder h(p);

    return 0;
}
