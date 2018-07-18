#include "../../../detector/color_table.h"
#include "../../../detector/convert_color.h"
#include <iostream>
#include <opencv2/opencv.hpp>
struct mousePara{
    int x,y,event,flags;
};

void mouse_call_back(int event, int x, int y, int flags, void* userdata)
{
    mousePara *ptr = static_cast<mousePara*> (userdata);
    ptr->x = x;
    ptr->y = y;
    ptr->event = event;
    ptr->flags = flags;
}

void getLabelImage(cv::Mat &src, cv::Mat &dst, int obj_type)
{
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

int main(int argc, char **argv)
{
    int obj_type = 6; // whiteline
    ColorTable ct;
    mousePara m;
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat img_ycrcb;
    cv::cvtColor(img,img_ycrcb,CV_BGR2YCrCb);
    cv::Mat img_label = cv::Mat(img.rows,img.cols,CV_16UC1);
    cv::Mat img_bin = cv::Mat(img.rows,img.cols,CV_8UC1); //for visualize
    ct.loadColorTable("color_table.cnf");
    ct.apply(img_ycrcb, img_label);
    getLabelImage(img_label, img_bin, obj_type);
    cv::imshow("bin",img_bin);
    cv::imshow("color",img);
    cv::setMouseCallback("color",mouse_call_back,&m);
    while(1){
        int k = cv::waitKey(1) & 255;
        int margin = 8;
        int width = 2;
        if(m.flags==cv::EVENT_FLAG_LBUTTON){
            for(int cy=m.y-width/2; cy<m.y+width/2; cy++){
                if( (0<=cy) && (cy<img.rows) ){
                    for(int cx=m.x-width/2; cx<m.x+width/2; cx++){
                        if( (0<=cx) && (cx<img.cols) ){
                            int y = img_ycrcb.at<cv::Vec3b>(cy,cx)[0];
                            int cr = img_ycrcb.at<cv::Vec3b>(cy,cx)[1];
                            int cb = img_ycrcb.at<cv::Vec3b>(cy,cx)[2];
                            ct.setColor(y,cb,cr,obj_type,margin);
                        }
                    }
                }
            }
            ct.apply(img_ycrcb, img_label );
            getLabelImage(img_label, img_bin, obj_type);
            cv::imshow("bin",img_bin);
        }
        else if(m.flags==cv::EVENT_FLAG_RBUTTON){
            margin = 8;
            width = 4;
            for(int cy=m.y-width/2; cy<m.y+width/2; cy++){
                if( (0<=cy) && (cy<img.rows) ){
                    for(int cx=m.x-width/2; cx<m.x+width/2; cx++){
                        if( (0<=cx) && (cx<img.cols) ){
                            int y = img_ycrcb.at<cv::Vec3b>(cy,cx)[0];
                            int cr = img_ycrcb.at<cv::Vec3b>(cy,cx)[1];
                            int cb = img_ycrcb.at<cv::Vec3b>(cy,cx)[2];
                            ct.clearColor(y,cb,cr,obj_type,margin);
                        }
                    }
                }
            }
            ct.apply(img_ycrcb, img_label);
            getLabelImage(img_label, img_bin, obj_type);
            cv::imshow("bin",img_bin);
        }
        if(k=='r'){
            ct.loadColorTable("color_table.cnf");
            ct.apply(img_ycrcb, img_label);
            getLabelImage(img_label, img_bin, obj_type);
            cv::imshow("bin",img_bin);
        }
        if(k==27)break;
    }
    cv::destroyAllWindows();
    ct.saveColorTable("color_table.cnf");
}
