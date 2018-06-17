#include "test.h"
Test_FCN::Test_FCN():num_tp(0),num_fp(0),num_tn(0),num_fn(0){
}
Test_FCN::~Test_FCN(){
}
void Test_FCN::run_test(cv::Mat &pr, cv::Mat &gt)
{
    int width = gt.cols;
    for(int y=0;y<gt.rows;y++){
        for(int x=0;x<gt.cols;x++){
            if(pr.data[y*width + x*pr.channels()] & gt.data[y*width + x*gt.channels()]){
                this->num_tp++;
            }
            else if(pr.data[y*width + x*pr.channels()]){
                this->num_fp++;
            }
            else if(gt.data[y*width + x*gt.channels()]){
                this->num_fn++;
            }
            else{
                this->num_tn++;
            }
        }
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
