#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <algorithm>
#include <sstream>

#include "gui_helpers.hpp"

#ifdef _WIN32

#include <windows.h>
#include <Commdlg.h>

std::string openImageFileDialog()
{
  OPENFILENAMEA ofn;
  char fileName[MAX_PATH] = {0};
  std::string fileNameStr;

  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL;
  ofn.lpstrFilter = "Image files\0*.JPG;*.PNG;*.BMP\0";
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = sizeof(fileName);
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrDefExt = "";

  if (GetOpenFileNameA(&ofn))
  {
    fileNameStr = fileName;
  }

  return fileNameStr;
}

std::vector<std::string> openImageFilesDialog()
{
  OPENFILENAMEA ofn;
  char fileName[MAX_PATH] = {0};
  std::vector<std::string> fileNames;
  std::string directoryPath;

  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL;
  ofn.lpstrFilter = "Image files\0*.JPG;*.PNG;*.BMP\0";
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = sizeof(fileName);
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrDefExt = "";

  if (GetOpenFileNameA(&ofn))
  {
    char *str = fileName;
    directoryPath = fileName;
    str += directoryPath.length() + 1;
    while (*str)
    {
      std::string fileNameStr = str;
      str += (fileNameStr.length() + 1);

      fileNames.push_back(directoryPath + "\\" + fileNameStr);
    }
  }

  return fileNames;
}

#else

std::string openProcessAndReadResult(std::string command, bool stripNewLine=false)
{
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
  {
    result += buffer.data();
  }
  if (stripNewLine)
  {
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
  }
  return result;
}

std::string openImageFileDialog()
{
  std::string cmd = "/usr/bin/zenity "
                    "--file-selection "
                    "--modal "
                    "--file-filter='Image files | *.jpg *.png *.bmp'";
  return openProcessAndReadResult(cmd, true);
}

std::vector<std::string> openImageFilesDialog()
{
  std::string cmd = "/usr/bin/zenity "
                    "--file-selection "
                    "--modal "
                    "--multiple "
                    "--file-filter='Image files | *.jpg *.png *.bmp'";
  std::string filePaths = openProcessAndReadResult(cmd, true);

  std::istringstream origStream(filePaths);
  std::vector<std::string> paths;
  std::string curLine;

  while (std::getline(origStream, curLine, '|'))
  {
    if (!curLine.empty())
        paths.push_back(curLine);
  }

  return paths;
}

#endif
