#pragma once
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <iomanip>

class getFilename
{
    public:
    void addNumber(std::string &fn, std::string &ext, int num, std::string &dst);
    void addDate(std::string &fn, std::string &ext, std::string &dst);
    void addTime(std::string &fn, std::string &ext, std::string &dst);
    int file_count(char *dir_path, std::vector<std::string> &ext);
};
