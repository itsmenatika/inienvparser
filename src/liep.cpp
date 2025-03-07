#include "liep.h"

inireader::initresult inireader::mergeResults(inireader::initresult& first, inireader::initresult& second){

    first.second.insert(second.second.begin(), second.second.end());

    return inireader::initresult(
        first.first && second.first,
        first.second
    );
}

inireader::groupvalues inireader::mergeGroups(inireader::groupvalues& first, inireader::groupvalues& second){

    first.insert(second.begin(), second.end());
    
    return first;
}

bool inireader::isIniError(const inireader::initresult& res){
    return res.first;
}

std::pair<bool, inireader::groupvalues> getGroup(const inireader::initresult& res, const std::string& groupName = inireader::defaultGroup){
    try{
        return std::pair<bool, inireader::groupvalues>(true, res.second.at(groupName));
    }
    catch(const std::out_of_range&){
        return std::pair<bool, inireader::groupvalues>(false, {});
    }
}

std::pair<bool, std::string> getValue(const inireader::groupvalues& group, const std::string& key){
    try{
        return std::pair<bool, std::string>(true, group.at(key));
    }
    catch(const std::out_of_range&){
        return std::pair<bool, std::string>(false, "");
    }
}

std::pair<bool, std::string> getValueQuick(const inireader::initresult& res, const std::string& key, const std::string& groupName = inireader::defaultGroup){
    try{
        return std::pair<bool, std::string>(true, res.second.at(groupName).at(key));
    }
    catch(const std::out_of_range&){
        return std::pair<bool, std::string>(false, "");
    }
}



inireader::initresult inireader::initIniFile(const std::filesystem::path& loc){
    // create a stream from that
    std::ifstream fileReader(loc);

    // check if it can access a provided file
    if(!fileReader.good()){
        std::cout << "not good" << std::endl;
        return initresult(false, inigroups());
    }

    // declare few things
    std::string line; // current line
    inireader::inigroups newGroupsToReturn = {{defaultGroup, groupvalues()}}; // group variable that will be returned as the second one in pair
    std::string currentGroup = defaultGroup; // the name of current selected group
    
    // iterate till there is a line
    while(std::getline(fileReader, line)){
        // get size of the line as const
        const std::size_t lineSize = line.size();

        // if there are no characters in that line, then skip that
        if(lineSize == 0) continue; 
        
        // check the first character
        switch(line.at(0)){
            // comments
            case '#':
            case ';':
                continue; // skip that line

            // group handling
            case '[': {
                // at least 2 characters to define a new group in format like this [NAME]
                // [] means the default group

                // if there's no correct size, then there's no chance for it being correct and it's unsafe to check the next character
                if(lineSize < 2){
                    return initresult(false, newGroupsToReturn);
                }


                bool closedName = false; // for [groupName] to check whether ] was closed
                std::stringstream buff; // buffer for the name
                std::string::iterator it = line.begin(); // iterator
                it++; // skip first character
                const std::string::iterator end = line.end(); // the end. To be safe that we're not out of bounds

                // iterate through chars
                while(it < end){
                    // if there was a group end
                    if(*it == ']'){
                        closedName = true;
                        break;
                    }

                    buff << *it;

                    it++;
                }

                // if the name was not closed
                if(!closedName){
                    return initresult(false, newGroupsToReturn);
                }

                // change it to the string
                std::string finalName = std::move(buff.str());

                // if the're was no name, then use default Group
                if(finalName.size() == 0){
                    currentGroup = inireader::defaultGroup;
                    break; // break from the switch
                }

                // check if there was already group with that name
                if(!newGroupsToReturn.count(finalName)){
                    // if there was not then create a new map for that group
                    newGroupsToReturn.insert(std::pair<std::string, groupvalues>(finalName, {}));
                }

                // set the current group by just moving the previous string
                currentGroup = std::move(finalName);

                break;
            }

            // the default case KEY=VALUE pair or KEY or KEY=
            default: {
                // buffers for the same reasons
                std::stringstream buffKey;
                std::stringstream buffVal;


                bool where = false; // the bool that indicates where is it the value or key (false = key)

                std::string::iterator it = line.begin(); // the start of the line
                const std::string::iterator end = line.end(); // the end of the line

                // iterate through characters
                while(it < end){
                    // if there was start of value
                    if(*it == '=' && !where) where = true;
                    // if not
                    else{
                        // the start of comments
                        if(*it == '#') break;
                        if(*it == ';') break;

                        // add to buffer
                        if(where){
                            buffKey << *it;
                        }
                        else{
                            buffVal << *it;
                        }
                    }

                    // move the iterator
                    it++;
                }

                // change them to strings
                std::string value = std::move(buffKey.str());
                std::string key = std::move(buffVal.str());

                // if there's no key, then skip it
                if(key.size() == 0) continue;
                
                // get the position of the actual key
                size_t startPos = key.find_first_not_of(" ");; // startPos (used for removing spaces)
                size_t endPos = key.find_last_not_of(" "); // endPos (used for removing spaces)

                // remove spaces
                key = key.substr(startPos, (endPos - startPos) + 1);

                // only if there's a value
                if(value.size() > 0){

                    // get the position of the actual value
                    startPos = value.find_first_not_of(" ");
                    endPos = value.find_last_not_of(" ");

                    // remove spaces
                    value = value.substr(startPos, (endPos - startPos) + 1);
                }
                
                // set the key-value pair
                newGroupsToReturn[currentGroup].insert_or_assign(key, value);
            }
        }
    }

    // return the correct result
    return inireader::initresult(true, newGroupsToReturn);
}