/**
 * @file library.hpp
 * @author Bastien Marais
 * @author Yoan Belhous
 * @author Henri De Guerry
 * @author Erwan Desaint
 * @brief This file regroups the different function declarations related to library.cpp
 * @version 0.1
 * @date 2020-06-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __LIBRARY__
    #define __LIBRARY__

    #include <opencv2/core.hpp>
    #include <opencv2/highgui.hpp>
    #include <opencv2/imgcodecs.hpp> 
    #include <opencv2/stitching.hpp>
    #include <stdio.h>
    #include <sys/types.h>
    #include <dirent.h>    
    #include <iostream>
    #include <fstream> 

    using namespace cv;
    using namespace std;

    Mat resize(Mat image, double width, double height);
    Mat contrast(Mat image, double contrast);
    void save(Mat image, String path);
    Mat color(Mat image, int red, int green, int blue);
    Mat erode(Mat image, int erosion_size, int type);
    Mat canny(Mat image, int threshold);
    Mat brightness(Mat image, int brightness);
    Mat dilate(Mat image, int dilatation_size, int type);
    Mat rotate(Mat image, int rotation_angle);
    Mat panorama(vector<Mat> imgs);
    vector<Mat> getImagesFromFolder(const char *directoryName);

#endif
