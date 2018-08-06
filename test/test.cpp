#include "test.h"
#include "getFilename.h"
Test_FCN::Test_FCN():num_tp(0),num_fp(0),num_tn(0),num_fn(0){
}
Test_FCN::~Test_FCN(){
}
void Test_FCN::run_test(cv::Mat &pr, cv::Mat &gt){
    int gwidth = gt.cols;
    int pwidth = pr.cols;
    for(int y=0;y<gt.rows;y++){
        for(int x=0;x<gt.cols;x++){
            //Result(pr.data[y*pr.step + x*pr.elemSize()], gt.data[y*gt.step + x*gt.elemSize()] );
            int p = pr.data[(y * pwidth + x)*pr.channels()];
            int g = gt.data[(y * gwidth + x)*gt.channels()];
            Result(p, g);
        }
    }
}
void Test_FCN::run_test_csv(std::vector<std::vector<double> > &pr_csv, cv::Mat &gt, double thre){
    cv::Mat pr;
    CSV2Mat(pr_csv, pr, thre);
    run_test(pr, gt);
}
void Test_FCN::CSV2Mat(std::vector<std::vector<double> > &src, cv::Mat &dst, double thre){
    int cols = src[0].size();
    int rows = src.size();
    cv::Mat m = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
    int width = m.cols;
    for(int y=0; y<rows; y++){
        for(int x=0; x<cols; x++){
            int th = (src[y][x] >= thre)?1:0;
            //m.data[y*m.step + x*m.elemSize()] = th;
            m.data[(y * width + x)*m.channels()] = th;
        }
    }
    dst = m.clone();
}
void Test_FCN::Result(int p, int g){
    if((p==0) && (g==0)){
        this->num_tn++;
    }
    else if( (p>0) && (g>0) ){
        this->num_tp++;
    }
    else if( (p>0) && (g==0)){
        this->num_fp++;
    }
    else if( (p==0) && (g>0)){
        this->num_fn++;
    }
    else{
        std::cout << "Can not reach. p(" << p << "), g(" << g << ")"<< std::endl;
    }
}
double Test_FCN::get_accuracy(){
    return (double)(num_tp+num_tn)/(num_tp+num_tn+num_fp+num_fn);
}
double Test_FCN::get_precision(){
    return (double)(num_tp)/(num_tp+num_fp);
}
double Test_FCN::get_recall(){
    return (double)(num_tp)/(num_tp+num_fn);
}
double Test_FCN::get_Fvalue(){
    double P = get_precision();
    double R = get_recall();
    return (2.0*R*P)/(R+P);
}
