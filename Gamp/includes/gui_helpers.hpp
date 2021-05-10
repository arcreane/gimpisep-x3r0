/**
 * @file gui_helpers.hpp
 * @author Yohann Martin
 * @author Mathias Géroudet
 * @author Timothee Pionnier
 * @author Oscar Mc Auliffe
 * @brief This file contains all the non-opencv utilities
 * for the graphical interface.
 * @version 1.0
 * @date 2021-05-10
 *
 * @copyright Copyright (c) Gamp Project 2021
 */

#pragma once

#include <string>
#include <vector>

#define FILEPATH_SIZE 2048

/**
 * @brief Opens a dialog box allowing the user to select an image
 * file (jpg, png or bmp).
 *
 * @return A string containing the path of the image file.
 */
std::string openImageFileDialog();

/**
 * @brief Opens a dialog box allowing the user to select multiple image
 * files (jpg, png or bmp).
 *
 * @return A list of strings containing the paths of the image files.
 */
std::vector<std::string> openImageFilesDialog();
