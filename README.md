# wazpo
Warp Zero Postprocessing (with c++)


This library takes a root file and a YAML configuration file as input and steer as output a clone of 
the input root file with additional branches. It is just an outer shell, so with a few tweak can be used for any 
input root file (not only warp-zero). 


The working philosophy is with "addons", you write and register addons classes to the "wazlooper" and they get called 
during a loop over entries. The "addons" classes must then define only two functions: an **"init"** and a **apply**.


# Requirements

 - **ROOT >=6.0.4** (for sure works with 6.14/04 )
 - **gcc >=4.8.1**  (for sure works with 8.2.0)
 - **python** and **pip**
 - **cmake>=3.9**

# Installation 

Install the c++ package manager:
```bash
pip install conan
```

Install dependencies and compile wazpo:
```bash
git clone git@github.com:Physik-Institut-UZH/wazpo.git
cd wazpo/build
source install.sh
```

From now on you can keep compile it (from the 'build' directory) via:
 - **make**: normal copile
 - **make clean**: remove only binaries
 - **source clean.sh**: hardcore clean up, removes the whole installation (you need to re-run 'source install.sh after this)


# Usage

```bash
Usage: wazpo --config <config_file_path> --file <input_root_file_path> --out <output_root_file_path>
```

There is a **Test** config file that you can run to see how it works, from the main dir do:

```bash
wazpo --config configs/test.yaml --file ../mock_data/processed_kryton_test_181108.root -o test.root
```

## How to write an addon

The add on class must inherit from the virtual prototype **addOn** class, you find an example [here](https://github.com/Physik-Institut-UZH/wazpo/blob/master/src/add_ons/add_posrec.hpp)
on how to do it, I suggest you to just copy the file completely and modify only names and the **init** and **apply** function. 
The function **init** gets call at initialization time (before the loop on events), while the function **apply** gets called once per event.
This class must contain the address of the branches that you want to add, it can retrieve all the other branches values (for that event) using the pointer to the **looper**.
You find a definition of all branches [here](https://github.com/Physik-Institut-UZH/wazpo/blob/master/src/libs/branchHolder.h).

Of course it's not enough ;), this is c++ so you need to hardcode the list of addons, 
go to the file [wazLooper.cpp](https://github.com/Physik-Institut-UZH/wazpo/blob/master/src/libs/wazLooper.cpp) and look for the keyword **ADD_ON_MODIFY_HERE**, and just do as it says in the comments there (you need to modify in two points of the code).


## How the configuration file works

Wazpo uses a common YAML configuration file syntax, [info on YAML syntax here](https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html),
the files are read with a c++ tool, of which you find the syntax [here](https://github.com/jbeder/yaml-cpp/wiki/Tutorial). You can obviously leave this feature blank.



# What if we modify/add/remove processed tree branches?

You need to rebuild the auto-generate root Tree class. For doing so you need a ROOT file with an example tree containing all the new/modified branches.
Then do this:
```bash
cd wazpo/src/libs
root -l <path_to_your_new_ROOT_file>
$> T1->MakeClass("branchHolder");   // this will re-generate the branchHolder class (assuming the tree is called T1)
$> .q 
```
Now, obviously the generation algorithm is not smart enough and this wont compile (because of the infamous vector), so open **branchHolder.h** with an editor 
and add:
```c++
#include "vector"
#include "vector"

using namespace std;  // <--- Add this line here

class branchHolder {
    .....
```

