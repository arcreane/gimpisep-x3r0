/**
 * @file opencv_helpers.hpp
 * @author Yohann Martin
 * @author Mathias Géroudet
 * @author Timothee Pionnier
 * @author Oscar Mc Auliffe
 * @brief This file contains all the opencv functions that we need.
 * @version 1.0
 * @date 2021-05-10
 *
 * @copyright Copyright (c) Gamp Project 2021
 */

#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

/**
 * @brief Allows to dilate a source image into a destination image
 * according to the given kernel size.
 *
 * @param src The source image to dilate.
 * @param dst A reference to the image to put the dilated image.
 * @param dilatationSize The size of the kernel for the dilatation.
 */
void dilate(cv::Mat src, cv::Mat &dst, int dilatationSize);

/**
 * @brief Allows to erode a source image into a destination image
 * according to the given kernel size.
 *
 * @param src The source image to erode.
 * @param dst A reference to the image to put the eroded image.
 * @param erosionSize The size of the kernel for the erosion.
 */
void erode(cv::Mat src, cv::Mat &dst, int erosionSize);

/**
 * @brief Resize an image given a scale factor.
 *
 * @param src The source image to resize.
 * @param dst A reference to the image to put the resized image.
 * @param scaleFactor A scale factor, must be greater than 0.
 */
void resize(cv::Mat src, cv::Mat &dst, double scaleFactor);

/**
 * @brief Resize a image given a new size.
 *
 * @param src The source image to resize.
 * @param dst A reference to the image to put the resized image.
 * @param size The new size of the image.
 */
void resize(cv::Mat src, cv::Mat &dst, cv::Size size);

/**
 * @brief Adjust the brightness of an image.
 *
 * @param src The source image to change the brightness.
 * @param dst A reference to the image to put the new changed image.
 * @param beta The brightness factor, can be negative to darken the image.
 */
void brightness(cv::Mat src, cv::Mat &dst, double beta);

/**
 * @brief Gathers a set of images into one by automatically detecting
 * the links between them.
 *
 * @param images The differents images to be gathered together.
 * @param dst A reference to the image to put the final result.
 */
bool panorama(std::vector<cv::Mat> images, cv::Mat &dst);

/**
 * @brief Perform a canny edges detection on an image given a threshold and
 * a kernel size.
 *
 * @param src The source image to perform canny edges detection.
 * @param dst A reference to the image that will contains the result.
 * @param threshold The accuracy threshold of the canny edges detection.
 * @param kernelSize The size of the kernel.
 */
void cannyEdges(cv::Mat src, cv::Mat &dst, double threshold, int kernelSize);

/**
 * @brief Rotates an image given an angle.
 *
 * @param src The source image to perform the rotation.
 * @param dst A reference to the image to put the rotated image.
 * @param angle The angle in degree of the rotation to apply.
 */
void rotate(cv::Mat src, cv::Mat &dst, double angle);

/**
 * @brief Performs a face and eyes recognition on a given image.
 *
 * @param src The source image to perform the face and eyes detection.
 * @param dst A reference to the image that will contains the detection result.
 */
void faceRecognition(cv::Mat src, cv::Mat &dst);
