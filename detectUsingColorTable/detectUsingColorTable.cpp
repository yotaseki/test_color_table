#include "../../detector/color_table.h"
#include "../../detector/convert_color.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <bitset>

#define LABEL_BACKGROUND = 0xFFFFFF;
#define LABEL_BACKGROUND = 0xFFFFFF;
#define LABEL_BACKGROUND = 0xFFFFFF;
#define LABEL_BACKGROUND = 0xFFFFFF;
#define LABEL_BACKGROUND = 0xFFFFFF;

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
    int obj_type = 6; // whiteline
    boost::filesystem::path p(argv[1]);
    ColorTable ct;
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat img_ycrcb;
    cv::cvtColor(img,img_ycrcb,CV_BGR2YCrCb);
    cv::Mat img_label = cv::Mat(img.rows,img.cols,CV_16UC1);
    cv::Mat img_bin = cv::Mat(img.rows,img.cols,CV_8UC1); //for visualize
    ct.loadColorTable("color_table.cnf");
    ct.apply(img_ycrcb, img_label);
    getLabelImage(img_label, img_bin, obj_type);
    std::string fout(argv[2]);
    fout = fout + "/ColorTable_" + p.filename().string();
    imwrite(fout, img_bin);
}
