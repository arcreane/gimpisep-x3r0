#!/bin/bash

apt update -y
apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libcanberra-gtk-module libcanberra-gtk3-module -y
cd /tmp
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd ./opencv
mkdir build
cd ./build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_GENERATE_PKGCONFIG=ON OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j4
make install
echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf
ldconfig -v
pkg-config --cflags --libs opencv4