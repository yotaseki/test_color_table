#include "test.h"
#include "rcsv.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
namespace fs = boost::filesystem;

int main(int argc, char **argv)
{
    // arg1:dataset, arg2:pred
    std::string f1(argv[1]);
    std::string f2(argv[2]);
    std::string outdir(argv[3]);
    double t = 0.96;
    Test_FCN test;
    std::vector<std::string> ext{".png",".jpg"};
    BOOST_FOREACH(const fs::path& p, std::make_pair(fs::directory_iterator(argv[1]),fs::directory_iterator())){
        if (!fs::is_directory(p)){
            fs::path extension = p.extension();
            int matching = 0;
            for(int i=0; i<ext.size(); i++){
                matching |= (extension.generic_string() == ext[i]); 
            }
            if(matching){
                std::string a1 = f1 + "/" + p.filename().string();
                std::string a2 = f2 + "/" + p.stem().string() + ".txt";
                std::string out_str = outdir + "/" + p.stem().string() + ".png";
                fs::path p2(a2);
                if(!fs::is_directory(p2))
                {
                    ""cv::Mat output;
                    cv::Mat ground_truth = cv::imread(a1);
                    RCSV predict(a2.c_str());
                    cv::cvtColor(ground_truth,ground_truth,CV_BGR2GRAY);
                    ""test.DrawImage(predict.data, ground_truth, t, output);
                    ""imwrite(out_str,output);
                }
            }
        }
    }
    return 0;
}
