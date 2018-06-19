#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

class Test_FCN
{
    public:
        Test_FCN();
        ~Test_FCN();
        void run_test(cv::Mat &predict, cv::Mat &groundtruth);
        double get_accuracy();
        double get_precision();
        double get_recall();
        int num_tp;
        int num_tn;
        int num_fp;
        int num_fn;
};
