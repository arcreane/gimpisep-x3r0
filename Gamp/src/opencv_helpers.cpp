#include <opencv2/objdetect.hpp>

#include "opencv_helpers.hpp"

void dilate(cv::Mat src, cv::Mat &dst, int dilatationSize)
{
  cv::Mat element = cv::getStructuringElement(
      cv::MORPH_RECT,
      cv::Size(2 * dilatationSize + 1, 2 * dilatationSize + 1),
      cv::Point(dilatationSize, dilatationSize));
  cv::dilate(src, dst, element);
}

void erode(cv::Mat src, cv::Mat &dst, int erosionSize)
{
  cv::Mat element = cv::getStructuringElement(
      cv::MORPH_RECT,
      cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1),
      cv::Point(erosionSize, erosionSize));
  cv::erode(src, dst, element);
}
