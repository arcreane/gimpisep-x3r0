#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#define CVUI_IMPLEMENTATION
#define CVUI_DISABLE_COMPILATION_NOTICES
#include "cvui.h"
#include "opencv_helpers.hpp"
#include "gui_helpers.hpp"
#include "toolbox_listener.hpp"

#define PREVIEW_WINDOW_NAME "Gamp Project - Preview"
#define TOOLBOX_WINDOW_NAME "Gamp Project - Toolbox"

void modifyImage();

cv::Mat originalImage;
cv::Mat frame;

ToolboxListener<bool> isDilatationActive(false, modifyImage);
ToolboxListener<int> dilatationSize(0, modifyImage);

ToolboxListener<bool> isErosionActive(false, modifyImage);
ToolboxListener<int> erosionSize(0, modifyImage);

ToolboxListener<bool> isResizeFactorActive(false, modifyImage);
ToolboxListener<double> scaleFactor(1.0, modifyImage);

ToolboxListener<bool> isResizeAbsoluteActive(false, modifyImage);
ToolboxListener<int> newWidth(0, modifyImage);
ToolboxListener<int> newHeight(0, modifyImage);

ToolboxListener<bool> isBrightnessActive(false, modifyImage);
ToolboxListener<double> brightnessFactor(0.0, modifyImage);

ToolboxListener<bool> isCannyActive(false, modifyImage);
ToolboxListener<double> cannyThreshold(0.0, modifyImage);

ToolboxListener<bool> isRotateActive(false, modifyImage);
ToolboxListener<double> rotationAngle(0.0, modifyImage);

ToolboxListener<bool> isFaceRecognition(false, modifyImage);

int main(void)
{
  auto toolboxFrame = cv::Mat(700, 400, CV_8UC3);
  originalImage = cv::imread("placeholder.jpg");

  if (originalImage.empty())
  {
    std::cout << "Error while loading placeholder!" << std::endl;
    return EXIT_FAILURE;
  }

  cv::namedWindow(PREVIEW_WINDOW_NAME, cv::WINDOW_AUTOSIZE);
  cv::namedWindow(TOOLBOX_WINDOW_NAME, cv::WINDOW_NORMAL);
  cvui::init(TOOLBOX_WINDOW_NAME);

  // cv::resizeWindow(PREVIEW_WINDOW_NAME, cv::Size(800, 600));
  cv::resizeWindow(TOOLBOX_WINDOW_NAME, cv::Size(400, 700));

  newWidth.listenedVariable = originalImage.size().width;
  newHeight.listenedVariable = originalImage.size().height;

  while (true)
  {
    toolboxFrame = cv::Scalar(49, 52, 49);

    cvui::beginRow(toolboxFrame, 5, 5, -1, -1, 20);
    if (cvui::button("Load Image"))
    {
      std::string filepath = openImageFileDialog();

      if (filepath.size() > 0) {
        cv::Mat image = cv::imread(filepath);

        if (image.empty())
        {
          std::cout << "Error while loading image!" << std::endl;
        }
        else
        {
          originalImage = image;

          newWidth.listenedVariable = originalImage.size().width;
          newHeight.listenedVariable = originalImage.size().height;
        }
      }
    }
    if (cvui::button("Save Image"))
    {
      cv::imwrite("result.jpg", frame);
    }
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 70, -1, -1, 20);
    cvui::checkbox("Use Dilatation", &(isDilatationActive.listenedVariable));
    cvui::trackbar(165, &(dilatationSize.listenedVariable), 0, 30);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 140, -1, -1, 20);
    cvui::checkbox("Use Erosion", &(isErosionActive.listenedVariable));
    cvui::trackbar(165, &(erosionSize.listenedVariable), 0, 30);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 210, -1, -1, 20);
    cvui::checkbox("Resize (factor)", &(isResizeFactorActive.listenedVariable));
    cvui::trackbar(165, &(scaleFactor.listenedVariable), 0.1, 5.0);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 280, -1, -1, 20);
    cvui::checkbox("Resize (absolute)", &(isResizeAbsoluteActive.listenedVariable));
    cvui::counter(&(newWidth.listenedVariable), 1);
    cvui::counter(&(newHeight.listenedVariable), 1);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 350, -1, -1, 20);
    cvui::checkbox("Brightness", &(isBrightnessActive.listenedVariable));
    cvui::trackbar(165, &(brightnessFactor.listenedVariable), -100.0, 100.0);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 420, -1, -1, 20);
    if (cvui::button("Panorama"))
    {
      std::vector<std::string> filepaths = openImageFilesDialog();
      std::vector<cv::Mat> images;

      if (filepaths.size() > 1) {
        for (auto &filepath : filepaths)
        {
          cv::Mat image = cv::imread(filepath);

          if (!image.empty())
          {
            images.push_back(image);
          }
        }

        // TODO: Panorama
      }
    }
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 490, -1, -1, 20);
    cvui::checkbox("Canny Edges", &(isCannyActive.listenedVariable));
    cvui::trackbar(165, &(cannyThreshold.listenedVariable), 0.0, 100.0);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 560, -1, -1, 20);
    cvui::checkbox("Rotate image", &(isRotateActive.listenedVariable));
    cvui::trackbar(165, &(rotationAngle.listenedVariable), 0.0, 360.0);
    cvui::endRow();

    cvui::beginRow(toolboxFrame, 5, 630, -1, -1, 20);
    cvui::checkbox("Face recognition", &(isFaceRecognition.listenedVariable));
    cvui::endRow();

    cvui::update();
    cv::imshow(TOOLBOX_WINDOW_NAME, toolboxFrame);

    isDilatationActive.update();
    dilatationSize.update();
    isErosionActive.update();
    erosionSize.update();
    isResizeFactorActive.update();
    scaleFactor.update();
    isResizeAbsoluteActive.update();
    newWidth.update();
    newHeight.update();
    isBrightnessActive.update();
    brightnessFactor.update();
    isCannyActive.update();
    cannyThreshold.update();
    isRotateActive.update();
    rotationAngle.update();
    isFaceRecognition.update();

    if (cv::waitKey(10) == 27)
    {
      break;
    }
  }

  cv::destroyAllWindows();

  return 0;
}

void modifyImage()
{
  originalImage.copyTo(frame);

  if (isDilatationActive.listenedVariable)
  {
    dilate(frame, frame, dilatationSize.listenedVariable);
  }
  if (isErosionActive.listenedVariable)
  {
    erode(frame, frame, erosionSize.listenedVariable);
  }
  if (isBrightnessActive.listenedVariable)
  {
    brightness(frame, frame, brightnessFactor.listenedVariable);
  }
  if (isResizeFactorActive.listenedVariable)
  {
    resize(frame, frame, scaleFactor.listenedVariable);
  }
  if (isResizeAbsoluteActive.listenedVariable)
  {
    resize(frame, frame, cv::Size(newWidth.listenedVariable, newHeight.listenedVariable));
  }

  cv::imshow(PREVIEW_WINDOW_NAME, frame);
}
