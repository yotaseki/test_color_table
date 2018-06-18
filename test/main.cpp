#include "test_fcn.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ofstream>

int main(int argc, char **argv)
{
    // arg1:label, arg2:pred
    Test_FCN test;
    ofstream ofs("result.csv",std::ios_bace::app);
    std::string a1(argv[1]);
    std::string a2(argv[2]);
    BOOST_FOREACH(const fs::path& p, std::make_pair(fs::directory_iterator(argv[1]),fs::directory_iterator())){
        if (!fs::is_directory(p)){
            fs::path extension = p.extension();
            int matching = 0;
            for(int i=0; i<ext.size(); i++){
                matching |= (extension.generic_string() == ext[i]); 
            }
            if(matching){
                a1 = a1 + "color_table_";
                a2 = a2 + ""
                cv::Mat ground_truth = cv::imread();
                cv::Mat predict = cv::imread(;
                test.run_test(predict, ground_truth);
            }
        }
    }
    std::cout << "accuracy:" << test.get_accuracy()<< std::endl;
    std::cout << "precision:" << test.get_precision()<< std::endl;
    std::cout << "recall:" << test.get_recall()<< std::endl;
    //ofs << "Filename,TP,TN,FP,FN,Accuracy,Precision,Recall"<< std::endl;
    ofs << ""
        return 0;
}
