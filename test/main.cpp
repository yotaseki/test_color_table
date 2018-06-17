#include "test_fcn.h"
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    Test_FCN test;
    cv::Mat predict = cv::imread(argv[1]);
    cv::Mat ground_truth = cv::imread(argv[1]);
    test.run_test(predict, ground_truth);
    std::cout << ":" << test.get_accuracy()<< std::endl;
    std::cout << ":" << test.get_precision()<< std::endl;
    std::cout << ":" << test.get_recall()<< std::endl;
    return 0;
}
