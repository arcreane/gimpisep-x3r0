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

void resize(cv::Mat src, cv::Mat &dst, double scaleFactor)
{
  cv::resize(src, dst, cv::Size(), scaleFactor, scaleFactor, cv::INTER_LINEAR);
}

void resize(cv::Mat src, cv::Mat &dst, cv::Size size)
{
  cv::resize(src, dst, size, 0, 0, cv::INTER_LINEAR);
}

void brightness(cv::Mat src, cv::Mat &dst, double beta)
{
  src.convertTo(dst, -1, 1, beta);
}

bool panorama(std::vector<cv::Mat> images, cv::Mat &dst)
{
  cv::Mat panoramaImage;
  cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
  cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
  cv::Stitcher::Status status = stitcher->stitch(images, panoramaImage);
  if (status == cv::Stitcher::OK) {
      dst = panoramaImage;
      return true;
  }
  return false;
}
