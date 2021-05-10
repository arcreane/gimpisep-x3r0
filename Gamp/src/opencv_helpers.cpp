#include <opencv2/objdetect.hpp>

#include "opencv_helpers.hpp"

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;

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

void cannyEdges(cv::Mat src, cv::Mat &dst, double threshold, int kernelSize)
{
  cv::Mat graySrc;
  cv::cvtColor(src, graySrc, cv::COLOR_BGR2GRAY);
  cv::Canny(graySrc, dst, threshold, threshold * 3, kernelSize);
}

void rotate(cv::Mat src, cv::Mat &dst, double angle)
{
  cv::Point2f center(src.cols / 2, src.rows / 2);
	double scale = 1;
  cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, scale);
  cv::Rect box = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect();

  rotationMatrix.at<double>(0,2) += box.width / 2  - src.cols / 2;
  rotationMatrix.at<double>(1,2) += box.height / 2  - src.rows / 2;

  cv::warpAffine(src, dst, rotationMatrix, box.size());
}

void faceRecognition(cv::Mat src, cv::Mat &dst)
{
  cv::Mat src_gray;
  std::vector<cv::Rect> faces;

  if (face_cascade.empty() && eyes_cascade.empty())
  {
    face_cascade.load("opencv_data/haarcascade_frontalface_alt.xml");
    eyes_cascade.load("opencv_data/haarcascade_eye_tree_eyeglasses.xml");
  }

  cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
  // cv::equalizeHist(src_gray, src_gray);
  face_cascade.detectMultiScale(src_gray, faces);

  for (size_t i = 0; i < faces.size(); i++)
  {
    std::vector<cv::Rect> eyes;
    cv::Mat faceROI = src_gray(faces[i]);

    cv::rectangle(dst, faces[i], cv::Scalar( 255, 0, 255 ), 2);
    eyes_cascade.detectMultiScale(faceROI, eyes);

    for (size_t j = 0; j < eyes.size(); j++)
    {
      cv::Rect eyePosition(
        faces[i].x + eyes[j].x,
        faces[i].y + eyes[j].y,
        eyes[j].width,
        eyes[j].height
      );
      cv::rectangle(dst, eyePosition, cv::Scalar( 255, 0, 0 ), 2);
    }
  }
}
