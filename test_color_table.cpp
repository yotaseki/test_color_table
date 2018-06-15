#include "../../detector/color_table.h"
#include "../../detector/convert_color.h"
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
    int width = src.rows;
    int height= src.cols;
    for(int y=0; y<src.cols; y++)
    {
        for(int x=0; x<src.rows; x++)
        {
            if(src.at<unsigned short>(y,x) & color)
            {
                dst.at<unsigned char>(y,x) = 255;
            }
            else{
                dst.at<unsigned char>(y,x) = 0;
            }
        }
    }
}

int main(int argc, char **argv)
{
    int margin = 8;
    int obj_type = 6; // whiteline
    ColorTable ct;
    mousePara m;
    //cv::Mat img = cv::imread(argv[1]);
    cv::Mat img = cv::imread("images/image00100.jpg");
    cv::Mat img_ycrcb;
    cv::cvtColor(img,img_ycrcb,CV_BGR2YCrCb);
    std::cout << "cols:" << img.cols << ", rows:" << img.rows << std::endl;
    cv::Mat img_label = cv::Mat(img.rows,img.cols,CV_16UC1);
    cv::Mat img_bin = cv::Mat(img.rows,img.cols,CV_8UC1); //for visualize
    std::cout << "cols:" << img_bin.cols << ", rows:" << img_bin.rows << std::endl;
    cv::imshow("color",img);
    cv::setMouseCallback("color",mouse_call_back,&m);
    while(1)
    {
        std::cout << "loop" << std::endl;
        cv::waitKey(1);
        std::cout << "wait" << std::endl;
        if(m.event == cv::EVENT_LBUTTONDOWN){
            std::cout << m.x << "," << m.y << std::endl;
            int y = img_ycrcb.at<cv::Vec3b>(m.y,m.x)[0];
            int cr = img_ycrcb.at<cv::Vec3b>(m.y,m.x)[1];
            int cb = img_ycrcb.at<cv::Vec3b>(m.y,m.x)[2];
            std::cout << "setColor" << std::endl;
            ct.setColor(y,cb,cr,obj_type,margin);
            std::cout << "apply" << std::endl;
            ct.apply(img_ycrcb, img_label );
            std::cout << "getLabelImage" << std::endl;
            getLabelImage(img_label, img_bin, obj_type);
            std::cout << "show" << std::endl;
        }
        else if(m.event == cv::EVENT_RBUTTONDOWN)
        {
            std::cout << "break" << std::endl;
            break;
        }
        std::cout << "fin" << std::endl;
    }
    cv::destroyAllWindows();
    cv::imshow("bin",img_bin);
    cv::waitKey(0);
    ct.saveColorTable("color_table.cnf");
}
