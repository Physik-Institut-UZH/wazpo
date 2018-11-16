RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
PRPL='\033[0;35m'


conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
build_success=$?
if [ $build_success -eq 0 ]
then
	echo -e "\n\n\n${GREEN}Build successfull. ${NC}"
	waz_dir=`pwd`
	echo " ----> Generating alias: wazpo=${waz_dir}/bin/wazpo"
	alias wazpo="${waz_dir}/bin/wazpo"
	if ! grep -q "wazpo" ~/.bashrc ; then
		echo " ----> Adding alias to .bashrc ..."
		echo -e "\n\n## wazpo: " >> ~/.bashrc
		echo -e "alias wazpo='${waz_dir}/bin/wazpo' \n\n" >> ~/.bashrc
	fi
	echo -e "\n\t\t ${PRPL}DONE!${NC}\n\n"
else
	echo -e "\n\n\n\t\t${RED}Build failed :( ${NC}\n\n"

fi

