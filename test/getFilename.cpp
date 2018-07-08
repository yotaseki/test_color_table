#include "getFilename.h"
namespace fs = boost::filesystem;

void getFilename::addNumber(std::string &fn ,std::string &ext ,int num ,std::string &dst){
    std::stringstream f;
    f << fn << std::setw(5) << std::setfill('0') << num << ext;
    dst = f.str();
}
void getFilename::addDate(std::string &fn ,std::string &ext ,std::string &dst){
    std::stringstream f;
    //f << fn << ext;
}
void getFilename::addTime(std::string &fn ,std::string &ext ,std::string &dst){
    std::stringstream f;
    //f << fn << ext;
}
int file_count(char *dir_path, std::vector<std::string> &ext){
    int count=0;
    const fs::path path(dir_path);
	BOOST_FOREACH(const fs::path& p, std::make_pair(fs::directory_iterator(path),
				fs::directory_iterator())) {
		if (!fs::is_directory(p))
		{
			fs::path extension = p.extension();
            int matching = 0;
            for(int i=0; i<ext.size(); i++)
            {
                matching |= (extension.generic_string() == ext[i]); 
            }
			if(matching)
			{
                count++;
			}
		}
	}
    return count;
}

