#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

void dilate(cv::Mat src, cv::Mat &dst, int dilatationSize);
void erode(cv::Mat src, cv::Mat &dst, int erosionSize);
void resize(cv::Mat src, cv::Mat &dst, double scaleFactor);
void resize(cv::Mat src, cv::Mat &dst, cv::Size size);
void brightness(cv::Mat src, cv::Mat &dst, double beta);
