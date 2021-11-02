#include<opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("./1.jpg");
    cv::imshow("test the opencv",img);
    cv::waitKey(0);
    return 0;
}