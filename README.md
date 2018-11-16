# wazpo
Warp Zero Postprocessing (with c++)


# Requirements

 - **gcc >=8.2** 
 - **python** and **pip**
 - **cmake>=3.9**

# installation 

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

