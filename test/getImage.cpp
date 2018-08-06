#include "test.h"
#include "rcsv.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
namespace fs = boost::filesystem;

void ColorEdit(cv::Mat &src, int b,int g,int r)
{
    for(int y=0;y<src.rows;y++){
        cv::Vec3b* ptr = src.ptr<cv::Vec3b>(y);
        for(int x=0;x<src.cols;x++){
            cv::Vec3b bgr = ptr[x];
            if((int)bgr[0] > 0){
                //std::cout << b << g << r << std::endl;
                ptr[x] = cv::Vec3b(b,g,r);
            }
        }
    }
}

int main(int argc, char **argv)
{
    // arg1:images, arg2:predtxt, arg3:threshold
    std::string outdir = "output/";
    std::string f1(argv[1]);
    std::string f2(argv[2]);
    int thre = std::stoi(argv[3]);
    double t = (double)thre/1000.0;
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
                std::string a3 = outdir + p.filename().string();
                //std::cout <<"path:" << a1 << " ," << a2 << std::endl; 
                //std::cout <<"thre:" << t << std::endl; 
                fs::path p2(a2);
                if(!fs::is_directory(p2))
                {
                    cv::Mat img = cv::imread(a1);
                    RCSV predict(a2.c_str());
                    
                    cv::Mat img_pred;
                    test.CSV2Mat(predict.data ,img_pred ,t);
                    cv::cvtColor(img_pred,img_pred,CV_GRAY2BGR);
                    ColorEdit(img_pred,255,0,255);
                    cv::Mat res;
                    cv::addWeighted(img,1.0,img_pred,0.7,0, res);
                    cv::imwrite(a3, res);
                    //test.run_test(predict.data, ground_truth);
                }
            }
        }
    }
    return 0;
}

