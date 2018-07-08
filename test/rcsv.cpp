#include "rcsv.h"
using namespace std;

RCSV::RCSV(const char *filename){
    ifs.open(filename);
    readCSV();
}

RCSV::~RCSV(){
    ifs.close();
}

void RCSV::readCSV(){
    string line;
    while(getline(ifs, line)){
        if(line.empty() || line[0] == '#'){
            continue;
        }
        vector<double> vdb;
        splitLine(line, ",", vdb);
        data.push_back(vdb);
    }
}

void RCSV::splitLine(const string &str, string delimiter, vector<double> &ret){
    string item(str);
    string replacement = " ";
    string::size_type pos = 0;
    while ((pos = item.find(delimiter, pos)) != std::string::npos) {
        item.replace(pos, delimiter.length(), replacement);
        pos += replacement.length();
    }
    std::stringstream buf(item);
    while(buf >> item) {
        double d = stod(item);
        ret.push_back(d);
    }
}
