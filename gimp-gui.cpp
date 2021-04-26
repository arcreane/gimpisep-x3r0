/**
 * @file gimp-gui.cpp
 * @author Bastien Marais
 * @author Yoan Belhous
 * @author Henri De Guerry
 * @author Erwan Desaint
 * @brief This file regroups the different functions related to the interface and the gimp-gui program.
 * @version 0.1
 * @date 2020-06-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/**********************************************************************
 * INCLUDES
 **********************************************************************/

#include "../include/library.hpp"

/**********************************************************************
 * GLOBAL VARIABLES
 **********************************************************************/

bool DEBUG = false; // True to display debug prints
String titleMain = "Main Window"; // Name of the main window
String titleTool = "ToolBox"; // Name of the toolbox window
String imagePath = "media/default.png"; // Path to the main image
Mat originalImage = imread(imagePath); // Reference image
Mat currentImage = imread(imagePath); // Display image
Mat toolboxImage = imread("media/toolbox.png"); // ToolBox image

int rotationAngle; // Angle for rotation
int dilateType; // Type of shape for dilatation
int dilateSize; // Size for dilatation n >= 0
int erodeType; // Type of shape for erosion
int erodeSize; // Size for erosion n >= 0
double resizeValue; // Size for resizing (1 = 100%)
int brightnessValue; // Brightness value [-255;255]
double contrastValue; // Facteur de constrast [0;255]
int cannyValue; // Threshold value n >= 0
int redValue; // Red value to be added [-255;255].
int greenValue; // Green value to be added [-255;255]
int blueValue; // Blue value to be added [-255;255]

/**********************************************************************
 * PROTOTYPES
 **********************************************************************/

void initPrint();
void reset();
void lock();
void toolboxCallBack(int event, int x, int y, int flags, void* userdata);
void toolboxAction(int rowValue, int colValue);
void updateView();
int main();

/**********************************************************************
 * FUNCTIONS
 **********************************************************************/

/**
 * @brief This function displays the welcome text of the application.
 * 
 */
void initPrint(){
    String separator = "#------------------------------------#\n";
    String title = "|    _____   _____   __  __   _____  \n" ;
    title += "|   / ____| |_   _| |  \\/  | |  __ \\ \n";
    title += "|  | |  __    | |   | \\  / | | |__) |\n";
    title += "|  | | |_ |   | |   | |\\/| | |  ___/ \n";
    title += "|  | |__| |  _| |_  | |  | | | |     \n";
    title += "|   \\_____| |_____| |_|  |_| |_|     \n";
    title += "| \n";
    title += "|    _____   _    _   _____          \n";
    title += "|   / ____| | |  | | |_   _|         \n";
    title += "|  | |  __  | |  | |   | |           \n";
    title += "|  | | |_ | | |  | |   | |           \n";
    title += "|  | |__| | | |__| |  _| |_          \n";
    title += "|   \\_____|  \\____/  |_____|         \n";
    String authors = "| Authors :\n| ├── Bastien Marais\n| ├── Yoan Belhous\n| ├── Henri De Guerry\n| └── Erwan Desaint\n";
    cout << separator << title <<  separator << authors << separator;
    cout << "| PRESS Q TO EXIT\n" << separator;

}

/**
 * @brief This function displays the text at the end of the program.
 * 
 */
void endPrint(){
    String separator = "#------------------------------------#\n";
    cout << separator << "| Thank you for using our program!\n| Good Bye :-)\n" << separator << endl;
}

/**
 * @brief This function resets all the parameters of the toolbox to the default settings.
 * 
 * @param rowValue Row of the table to be reset
 */
void reset(int rowValue){
    switch(rowValue ){
        case 0:
            rotationAngle = 0;
            dilateType = MORPH_RECT;
            dilateSize = 0;
            erodeType = MORPH_RECT;
            erodeSize = 0;
            resizeValue = 1.0;
            brightnessValue = 0;
            contrastValue = 1;
            cannyValue = 0;
            redValue = 0;
            greenValue = 0;
            blueValue = 0;
            break;
        case 2:
            dilateType = MORPH_RECT;
            dilateSize = 0;
            break;
        case 3:
            erodeType = MORPH_RECT;
            erodeSize = 0;
            break;
        case 4:
            resizeValue = 1.0;
            break;
        case 5:
            rotationAngle = 0;
            break;
        case 6:
            brightnessValue = 0;
            break;
        case 7:
            contrastValue = 1;
            break;
        case 8:
            cannyValue = 0;
            break;
        case 9:
            redValue = 0;
            break;
        case 10:
            greenValue = 0;
            break;
        case 11:
            blueValue = 0;
            break;
    }
}

/**
 * @brief This function transforms the current image into the original image.
 * 
 */
void lock(){
    originalImage = currentImage ;
}

/**
 * @brief This function manages clicks on the toolbox and determines which action to take.
 * 
 * @param event Event number
 * @param x Horizontal mouse coordinates
 * @param y Vertical mouse coordinates
 * @param flags Flags number
 * @param userdata Custom data
 */
void toolboxCallBack(int event, int x, int y, int flags, void* userdata){
    int row = 30;
    int col = 60;
    int rowValue = -1, colValue = -1;
    bool find = false;
    if(event == EVENT_LBUTTONDOWN){
        rowValue =  (y / row) + 1;
        colValue =  (x / col) + 1;
        if(DEBUG){
            cout << "| Left click - position (" << x << ", " << y << ")" << endl;
            cout << "| Left click - flags (" << flags << "), userdata (" << userdata << ")" << endl;
            cout << "| rowValue = " << rowValue << ", colValue = " << colValue << endl;
        } 
        toolboxAction(rowValue,colValue);
    }   
}

/**
 * @brief This function performs the actions in relation to the selected row and column.
 * 
 * @param rowValue Selected row number
 * @param colValue Selected column number
 */
void toolboxAction(int rowValue, int colValue){
    switch(rowValue){
        case 1:
            switch(colValue){
                case 7:
                    if(DEBUG) cout << "| Open cmd" << endl;
                    cout << "| Enter the relative or absolute path to the image to open :\n| ";
                    cin >> imagePath;
                    originalImage = imread(imagePath);
                    currentImage = imread(imagePath);
                    reset(0);
                    break;
            }
        break;
        case 2:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Dilate -" << endl;
                    if(dilateSize -1 >= 0)dilateSize -= 1;
                    currentImage = dilate(originalImage,dilateSize, dilateType);
                    break;
                case 4:
                    if(DEBUG) cout << "| Dilate +" << endl;
                    dilateSize += 1;
                    currentImage = dilate(originalImage,dilateSize, dilateType);
                    break;
                case 5:
                    if(DEBUG) cout << "| Dilate lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Dilate reset" << endl;
                    reset(rowValue);
                    currentImage = dilate(originalImage,dilateSize, dilateType);
                    break;
                case 7:
                    if(DEBUG) cout << "| Dilate cmd" << endl;
                    cout << "| Enter the value for the form of dilatation:\n| | - 1 for RECTANGLE \n| | - 2 for CROSS \n| | - 3 for ELLIPSE\n| ";
                    cin >> dilateType;
                    if(dilateType == 2)dilateType = MORPH_CROSS;
                    else if(dilateType == 3)dilateType = MORPH_ELLIPSE;
                    else dilateType = MORPH_RECT;
                    cout << "| Enter the size to take into account in px, an integer is expected :\n| ";
                    cin >> dilateSize;
                    currentImage = dilate(originalImage,dilateSize, dilateType);
                    break;
            }
        break;
        case 3:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Erode -" << endl;
                    if(erodeSize -1 >= 0)erodeSize -= 1; 
                    currentImage = erode(originalImage,erodeSize, erodeType);
                    break;
                    break;
                case 4:
                    if(DEBUG) cout << "| Erode +" << endl;
                    erodeSize += 1;
                    currentImage = erode(originalImage,erodeSize, erodeType);
                    break;
                case 5:
                    if(DEBUG) cout << "| Erode lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Erode reset" << endl;
                    reset(rowValue);
                    currentImage = erode(originalImage,erodeSize, erodeType);
                    break;
                case 7:
                    if(DEBUG) cout << "| Erode cmd" << endl;
                    cout << "| Enter the value for the form of erosion :\n| | - 1 for RECTANGLE \n| | - 2 for CROSS \n| | - 3 for ELLIPSE\n| ";
                    cin >> erodeType;
                    if(erodeType == 2)erodeType = MORPH_CROSS;
                    else if(erodeType == 3)erodeType = MORPH_ELLIPSE;
                    else erodeType = MORPH_RECT;
                    cout << "| Enter the size to take into account in px, an integer is expected :\n| ";
                    cin >> erodeSize;
                    currentImage = erode(originalImage,erodeSize, erodeType);
                    break;
            }
        break;
        case 4:
            double modifierWidth,modifierHeight;
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Resize -" << endl;
                    if(resizeValue > 0.15){
                        resizeValue -= 0.1;
                        modifierWidth = originalImage.size().width * resizeValue;
                        modifierHeight = originalImage.size().height * resizeValue;   
                        currentImage = resize(originalImage,modifierWidth,modifierHeight);
                    }
                    break;
                case 4:
                    if(DEBUG) cout << "| Resize +" << endl;
                    resizeValue += 0.1;
                    modifierWidth = originalImage.size().width * resizeValue;
                    modifierHeight = originalImage.size().height * resizeValue;
                    currentImage = resize(originalImage,modifierWidth,modifierHeight);
                    break;
                case 5:
                    if(DEBUG) cout << "| Resize lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Resize reset" << endl;
                    reset(rowValue);
                    modifierWidth = originalImage.size().width * resizeValue;
                    modifierHeight = originalImage.size().height * resizeValue;
                    currentImage = resize(originalImage,modifierWidth,modifierHeight);
                    break;
                case 7:
                    if(DEBUG) cout << "| Resize cmd" << endl;
                    cout << "| Enter the value corresponding to your choice of resizing:\n| | - 1 for pixel size\n| | - 2 for percentage size\n| ";
                    int resizeType;
                    double width, height;
                    cin >> resizeType;
                    if(resizeType == 1){
                        cout << "| Enter a pixel value for the width, decimal numbers is accepted:\n| ";
                        cin >> width;
                        cout << "| Enter a pixel value for the height, decimal numbers is accepted:\n| ";
                        cin >> height;
                        currentImage = resize(originalImage,width,height);
                    }
                    else {
                        cout << "| Enter a value for the width, a ratio is expected (between 0 and 1):\n| ";
                        cin >> width;
                        cout << "| Enter a value for the height, a ratio is expected (between 0 and 1):\n| ";
                        cin >> height;
                        modifierWidth = originalImage.size().width * width;
                        modifierHeight = originalImage.size().height * height;
                        currentImage = resize(originalImage,modifierWidth,modifierHeight);
                    }
                    break;
            }
            break;
        case 5:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Rotate -" << endl;
                    rotationAngle -= 5;
                    currentImage = rotate(originalImage,rotationAngle);
                    break;
                case 4:
                    if(DEBUG) cout << "| Rotate +" << endl;
                    rotationAngle += 5;
                    currentImage = rotate(originalImage,rotationAngle);
                    break;
                case 5:
                    if(DEBUG) cout << "| Rotate lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Rotate reset" << endl;
                    reset(rowValue);
                    currentImage = rotate(originalImage,rotationAngle);
                    break;
                case 7:
                    if(DEBUG) cout << "| Rotate cmd" << endl;
                    cout << "| Enter the angle for the rotation, an integer is expected:\n| ";
                    cin >> rotationAngle;
                    currentImage = rotate(originalImage,rotationAngle);
                    break;
            }
            break;
        case 6:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Brightness -" << endl;
                    if(brightnessValue - 5 >= -255){
                        brightnessValue -= 5;
                        currentImage = brightness(originalImage,brightnessValue);
                    }
                    break;
                case 4:
                    if(DEBUG) cout << "| Brightness +" << endl;
                    if(brightnessValue + 5 <= 255){
                        brightnessValue += 5;
                        currentImage = brightness(originalImage,brightnessValue);
                    }
                    break;
                case 5:
                    if(DEBUG) cout << "| Brightness lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Brightness reset" << endl;
                    reset(rowValue);
                    currentImage = brightness(originalImage,brightnessValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Brightness cmd" << endl;
                    cout << "| Enter a value for the brightness, an integer between -255 and 255 is expected:\n| ";
                    cin >> brightnessValue;
                    currentImage = brightness(originalImage,brightnessValue);
                    break;
            }
            break;
        case 7:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Contrast -" << endl;
                    if(contrastValue > 0 ) contrastValue -= 0.1;
                    currentImage = contrast(originalImage,contrastValue);
                    break;
                case 4:
                    if(DEBUG) cout << "| Contrast +" << endl;
                    if(contrastValue < 255) contrastValue += 0.1;
                    currentImage = contrast(originalImage,contrastValue);
                    break;
                case 5:
                    if(DEBUG) cout << "| Contrast lock" << endl;
                    lock();
                    break;
                case 6:
                    if(DEBUG) cout << "| Contrast reset" << endl;
                    reset(rowValue);
                    currentImage = contrast(originalImage,contrastValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Contrast cmd" << endl;
                    cout << "| Enter a value for the contrast, an integer between 0 and 255 is expected (1 is the default contrast):\n| ";
                    cin >> contrastValue;
                    currentImage = contrast(originalImage,contrastValue);
                    break;
            }
            break;
        case 8:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Canny Edge -" << endl;
                    if(cannyValue > -1) cannyValue -= 1;
                    if(cannyValue == -1) currentImage = originalImage;
                    else currentImage = canny(originalImage,cannyValue);
                    break;
                case 4:
                    if(DEBUG) cout << "| Canny Edge +" << endl;
                    cannyValue += 1;
                    currentImage = canny(originalImage,cannyValue);
                    break;
                case 6:
                    if(DEBUG) cout << "| Canny Edge reset" << endl;
                    reset(rowValue);
                    currentImage = canny(originalImage,cannyValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Canny Edge cmd" << endl;
                    cout << "| Enter a value for the Canny Edge, a positive integer:\n| ";
                    cin >> cannyValue;
                    currentImage = canny(originalImage,cannyValue);
                    break;
            }
            break;
        case 9:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Red -" << endl;
                    if(redValue > -255) redValue -=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 4:
                    if(DEBUG) cout << "| Red +" << endl;
                    if(redValue < 255) redValue +=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 6:
                    if(DEBUG) cout << "| Red reset" << endl;
                    reset(rowValue);
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Red cmd" << endl;
                    cout << "| Enter a value for the red presence, an integer between -255 and 255 is expected:\n| ";
                    cin >> redValue;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
            }
            break;
        case 10:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Green -" << endl;
                    if(greenValue > -255) greenValue -=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 4:
                    if(DEBUG) cout << "| Green +" << endl;
                    if(greenValue < 255) greenValue +=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 6:
                    if(DEBUG) cout << "| Green reset" << endl;
                    reset(rowValue);
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Green cmd" << endl;
                    cout << "| Enter a value for the green presence, an integer between -255 and 255 is expected:\n| ";
                    cin >> greenValue;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
            }
            break;
        case 11:
            switch(colValue){
                case 3:
                    if(DEBUG) cout << "| Blue -" << endl;
                    if(blueValue > -255) blueValue -=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 4:
                    if(DEBUG) cout << "| Blue +" << endl;
                    if(blueValue < 255) blueValue +=5;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;

                case 6:
                    if(DEBUG) cout << "| Blue reset" << endl;
                    reset(rowValue);
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
                case 7:
                    if(DEBUG) cout << "| Blue cmd" << endl;
                    cout << "| Enter a value for the blue presence, an integer between -255 and 255 is expected:\n| ";
                    cin >> blueValue;
                    currentImage = color(originalImage, redValue, greenValue, blueValue);
                    break;
            }
            break;
        case 12:
            switch(colValue){
                case 7:
                    if(DEBUG) cout << "| Panorama cmd" << endl;
                    cout << "| Enter the relative or absolute path to the folder containing every images to open:\n| ";
                    char folderPath[255];
                    cin >> folderPath;
                    currentImage = panorama(getImagesFromFolder(folderPath));
                    break;
            }
            break;
        case 13:
            switch(colValue){
                case 7:
                    if(DEBUG) cout << "| Save cmd" << endl;
                    cout << "| To save this image enter the path where it has to be stored:\n| ";
                    String path;
                    cin >> path;
                    save(currentImage,path);
                    break;
            }
            break;
    }
    updateView();
}

/**
 * @brief This function displays the current image in the main window.
 * 
 */
void updateView(){
    imshow(titleMain,currentImage);
} 

/**********************************************************************
 * MAIN
 **********************************************************************/

/**
 * @brief This function is the heart of the program that will be executed.
 * 
 * @return int Status number
 */
int main() {
    bool running = true;
    char exitKeyCode = 113; // ASCII code for 'q'
    char key;

    initPrint();
    namedWindow(titleMain);
    imshow(titleMain,currentImage);
    namedWindow(titleMain);
    reset(0);

    while(running){
        imshow(titleTool,toolboxImage);
        setMouseCallback(titleTool,toolboxCallBack, NULL);
        
        key = waitKey(25);
        if(key == exitKeyCode){
            cout << "| Exit key pressed" << endl;
            running = false;
        }
    }  
    
    destroyAllWindows();
    endPrint();
    return 0;
} 
