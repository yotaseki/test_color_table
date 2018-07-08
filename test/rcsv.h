#pragma once

#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

class RCSV{
    public:
        std::ifstream ifs;
        std::vector<std::vector<double> > data;
        RCSV(const char* filename);
        ~RCSV();
    private:
        void readCSV();
        void splitLine(const std::string &str, std::string delimiter, std::vector<double> &ret);
};
