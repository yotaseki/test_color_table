#include "../../../detector/color_table.h"
#include "../../../detector/convert_color.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <bitset>
#include <fstream>
namespace fs = boost::filesystem;

// arg1:input_dir, arg2:output_dir

typedef struct ObjectColor{
    int background;
    int field;
    int whiteline;
    int human;
    int ball;
    int robot;
    int goal;
    int other_robot;
}obj_color_s;
obj_color_s obj_color = {0xFFFFFF, 0x00FFFF, 0xFF0000, 0xFFFF00, 0x00FF00, 0x0000FF, 0xFF00FF, 0x800080};

void getLabelImage(cv::Mat &src, cv::Mat &dst, int obj_type){
    unsigned short color = 1 << obj_type;
    int width = dst.cols;
    for(int y=0; y<dst.rows; y++){
        for(int x=0; x<dst.cols; x++){
            int ret = color & src.data[(y * width + x) * src.channels()];
            if(ret){
                dst.data[(y * width + x)*dst.channels()] = 255;
            }
            else{
                dst.data[(y * width + x)*dst.channels()] = 0;
            }
        }
    }
}

int main(int argc, char **argv){
    std::string filetype = "text"; //text , gray, binary, compose
    int obj_type = 6; // whiteline
    ColorTable ct;
    ct.loadColorTable("color_table.cnf");
    const fs::path path(argv[1]);
    std::vector<std::string> ext{".png",".jpg"};
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
                cv::Mat img = cv::imread(p.c_str());
                cv::Mat img_ycrcb;
                cv::cvtColor(img,img_ycrcb,CV_BGR2YCrCb);
                cv::Mat img_label = cv::Mat(img.rows,img.cols,CV_16UC1);
                cv::Mat img_bin = cv::Mat(img.rows,img.cols,CV_8UC1); //for visualize
                ct.apply(img_ycrcb, img_label);
                getLabelImage(img_label, img_bin, obj_type);
                std::string fout(argv[2]);
                if(filetype == "text"){
                    fout = fout + "/" + p.stem().string() + ".txt";
                    std::cout << fout << std::endl;
                    std::ofstream ofs(fout);
                    for(int y=0;y<img_bin.rows;y++){
                        for(int x=0;x<img_bin.cols;x++){
                            if(x){
                                ofs << ",";
                            }
                            if(img_bin.data[(y * img_bin.cols + x)*img_bin.channels()]>0){
                                ofs << "1";
                            }
                            else{
                                ofs << "0";
                            }
                        }
                        ofs << std::endl;
                    }
                    ofs.close();
                }
                else if(filetype == "binary"){
                    fout = fout + "/" + p.stem().string() + ".png";
                    std::cout << fout << std::endl;
                    imwrite(fout, img_bin);
                }
			}
		}
	}
}
