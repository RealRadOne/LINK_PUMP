#include<string>
/**
* capsFirst
* @param str
* @return output
*/
std::string capsFirst(std::string str){
    transform(str.begin(), ++str.begin(), str.begin(), ::toupper);
    return str;
}

/**
* @input str Any string 
* @output trimmed_string Returns string with last charachter trimmed
*/
std::string stripEndl(std::string str){
    //if(str[str.size()-1]==std::endl){
        str.replace(str.size()-1,1,"");
    //}
    return str;
}