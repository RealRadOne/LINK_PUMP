#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include<map>
#include<vector>
#include<algorithm>
#include"helper.cpp"

using namespace std;

struct Link{
    std::string date;
    std::string username;
    std::string tags[3];
    std::string link;
    std::string title;
};

std::unordered_map<std::string,vector<Link*> > tagList;
std::map<std::string,vector<Link*> > tagListOrdered;

/*
* 
* @input line Input line from CSV
* @input linecount Current line number to throw error
* @output Link* Pointer to link object | NULL incase of error 
*/
Link* parseCsvLine(std::string line, long int linecount){
    unsigned int i=0;
    bool inQuotes = false;
    
    std::string currCell = "";
    std::vector<std::string> cells;

    while(i<line.size()){
        if(line[i]==','){
            // If inQuotes, use ','
            if(inQuotes){
                currCell += ',';
            } else {
                cells.push_back(currCell);
                currCell = "";
            }
        } else if (line[i] == '\"'){
            inQuotes = !inQuotes;
        } else {
            currCell += line[i];
        }
        i++;
    }

    // Trailing data
    if(currCell!=""){
        cells.push_back(currCell);
        currCell = "";
    }

    if(cells.size()>7){
        std::cout << "Error (line "<< linecount <<"): Incorrect number of cells detected" << std::endl;
        std::cout << line << std::endl;
        return NULL;
    }

    Link* currLink = new Link;
    currLink->date = cells[0];
    currLink->username = cells[1];
    currLink->tags[0] = cells[2];
    currLink->tags[1] = cells[3];
    currLink->tags[2] = cells[4];
    currLink->link = cells[5];
    currLink->title = cells[5];
    return currLink;
}

/*
 * @input *link Link object pointer
 */
void addLink(Link* link){
    for(auto item : link->tags){
        
        //Remove Whitespaces
        item.erase(std::remove(item.begin(),item.end(),' '),item.end());
        item = capsFirst(item);

        // If tag not found, create tag
        if(item==" "){
            item = "all";
        }
        if(tagList.find(item) == tagList.end()){
            std::vector<Link*> linkList(1,link);
            tagList[item] = linkList;
        } else {
            tagList[item].push_back(link);
        }

    }
}

/*
* Outputs MDFile 
*/
void outputMD(){
    std::cout << "Writing MD file" << std::endl;
    ofstream mdFile;
    mdFile.open("website.md");
    mdFile << "# Links" << std::endl;
    for(auto it=tagListOrdered.begin(); it!= tagListOrdered.end(); ++it){
        
        auto list = it;

        // Page for each tag
        if(list->first == ""){
            continue;
        }
        mdFile << "## "<< list->first << std::endl;
        mdFile << "###  " << std::endl;

        for(auto link: list->second){
            std::string outline = "- [" + stripEndl(link->title) + "](" + stripEndl(link->link) + ")";
            //std::cout << outline << std::endl;
            mdFile << outline << std::endl;
        }
    }
    mdFile.close();
}

int main(){
    ifstream csvFile("data.csv");
    std::string line = " ";
    long int linecount = 1;
    if (csvFile.is_open()) {
        while (getline(csvFile, line)) {
            auto link = parseCsvLine(line,linecount);
            if(link == NULL){continue;}
            addLink(link);
            linecount++;
        }
    } else {
    cout << "Unable to open file" << endl;
    }
    csvFile.close();

    cout << " TAGS: " << tagList.size() << endl;
    tagListOrdered = std::map<std::string,vector<Link*> >(tagList.begin(), tagList.end());
    outputMD();
}
