#include <opencv2/opencv.hpp>
#include <iostream>

#define CVUI_IMPLEMENTATION
#define CVUI_DISABLE_COMPILATION_NOTICES
#include "cvui.h"

#define WINDOW_NAME "Gamp Project"

int main(void)
{
  cv::Mat originalImage = cv::imread("van_gogh.jpg");
  cv::Mat frame = originalImage.clone();
  bool isDilatationActive = false;
  int dilatationSize = 0;

  if (originalImage.empty())
  {
    std::cout << "Error while loading image!" << std::endl;
    return EXIT_FAILURE;
  }

  cv::namedWindow(WINDOW_NAME);
  cvui::init(WINDOW_NAME);

  while (true)
  {
    if (isDilatationActive) {
      cv::Mat element = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size( 2*dilatationSize + 1, 2 * dilatationSize + 1),
        cv::Point(dilatationSize, dilatationSize)
      );
      cv::dilate(originalImage, frame, element);
    } else {
      originalImage.copyTo(frame);
    }

    cvui::window(frame, 10, 50, 180, 180, "Gamp Actions");
    cvui::checkbox(frame, 15, 80, "Use Dilatation", &isDilatationActive);
    cvui::trackbar(frame, 15, 110, 165, &dilatationSize, 0, 30);

    cvui::update();
    imshow(WINDOW_NAME, frame);

    if (cv::waitKey(10) == 27)
    {
      break;
    }
  }

  return 0;
}
