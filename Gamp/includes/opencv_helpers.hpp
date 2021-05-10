#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

void dilate(cv::Mat src, cv::Mat &dst, int dilatationSize);
void erode(cv::Mat src, cv::Mat &dst, int erosionSize);
