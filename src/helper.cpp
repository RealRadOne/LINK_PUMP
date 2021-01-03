#include<string>
#include<algorithm>
/**
* capsFirst
* @param str
* @return output
*/
std::string capsFirst(std::string str){
    transform(str.begin(), ++str.begin(), str.begin(), ::toupper);
    return str;
}
