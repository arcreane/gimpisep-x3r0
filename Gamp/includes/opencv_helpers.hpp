#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

void dilate(cv::Mat src, cv::Mat &dst, int dilatationSize);
void erode(cv::Mat src, cv::Mat &dst, int erosionSize);
void resize(cv::Mat src, cv::Mat &dst, double scaleFactor);
void resize(cv::Mat src, cv::Mat &dst, cv::Size size);
void brightness(cv::Mat src, cv::Mat &dst, double beta);
bool panorama(std::vector<cv::Mat> images, cv::Mat &dst);
void cannyEdges(cv::Mat src, cv::Mat &dst, double threshold, int kernelSize);
void rotate(cv::Mat src, cv::Mat &dst, double angle);
void faceRecognition(cv::Mat src, cv::Mat &dst);
