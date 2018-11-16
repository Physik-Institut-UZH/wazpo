# wazpo
Warp Zero Postprocessing (with c++)


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

