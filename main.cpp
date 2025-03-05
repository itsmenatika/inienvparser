#include "./liep.h"
#include <filesystem>
#include <iostream>
#include <string>

int main(){
    const inireader::initresult rs = inireader::initIniFile(std::filesystem::path("test.ini"));

    if(!rs.first){
        std::cout << "err";
        return 0;
    }

    const inireader::inigroups grp = rs.second;

    while(true){
        std::string groupname;
        std::cout << std::endl << "write the name of the group >> ";
        std::cin >> groupname;

        const inireader::groupvalues defaultgrp = grp.at(groupname);

        for(auto it = defaultgrp.begin(); it != defaultgrp.end(); it++){
            std::cout << it->first << " -> " << it->second << std::endl;
        }
    }


    return 0;

}