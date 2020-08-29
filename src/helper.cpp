#include<string>

/**
* @input str Any string 
* @output trimmed_string Returns string with last charachter trimmed
*/
std::string stripEndl(std::string str){
    str.replace(str.size()-1,1,"");
    return str;
}