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
    // arg1:label, arg2:pred
    bool ret = fs::exists( "result.csv" );
    std::ofstream ofs("result.csv",std::ios_base::app);
    std::string f1(argv[1]);
    std::string f2(argv[2]);
    for(int thre=0; thre<=100; thre++){
        double t = (double)thre/100.0;
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
                    //std::cout <<"path:" << a1 << " ," << a2 << std::endl; 
                    fs::path p2(a2);
                    if(!fs::is_directory(p2))
                    {
                        cv::Mat ground_truth = cv::imread(a1);
                        //cv::Mat predict = cv::imread(a2);
                        RCSV predict(a2.c_str());
                        cv::cvtColor(ground_truth,ground_truth,CV_BGR2GRAY);
                        //cv::cvtColor(predict,predict,CV_BGR2GRAY);
                        test.run_test_csv(predict.data, ground_truth, t);
                    }
                }
            }
        }
        std::cout << " --- threshold:" << thre << " --- "<< std::endl;
        std::cout << "accuracy:" << test.get_accuracy()<< std::endl;
        std::cout << "precision:" << test.get_precision()<< std::endl;
        std::cout << "recall:" << test.get_recall()<< std::endl;
        std::cout << "F-value:" << test.get_Fvalue() << std::endl;
        //ofs << "Filename,TP,TN,FP,FN,Accuracy,Precision,Recall"<< std::endl;
        if (!ret) {
            std::cout << "Create new file." << std::endl;
            ofs << "Path,Threshold,TP,TN,FP,FN,F-value,Precision,Recall,Accuracy"<< std::endl;
            ret = true;
        }
        ofs << argv[2] << ","<< t <<"," << test.num_tp <<"," << test.num_tn <<"," << test.num_fp <<"," << test.num_fn <<"," << test.get_Fvalue() <<"," << test.get_precision() <<"," << test.get_recall() << ","<< test.get_accuracy() << std::endl;
    }
    return 0;
}
