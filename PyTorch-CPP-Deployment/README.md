<div align="center">
  <h1>PyTorch-CPP-Deploy</h1>
</div>

<p align="center">
    <a href="https://www.python.org">
        <img alt="Build" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54">
    </a>
    <a href="https://isocpp.org">
        <img alt="C++" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white">
    </a>
    <a href="https://pytorch.org">
        <img alt="PyTorch" src="https://img.shields.io/badge/PyTorch-%23EE4C2C.svg?style=for-the-badge&logo=PyTorch&logoColor=white">
    </a>
    <a href="https://opencv.org">
        <img alt="Open-CV" src="https://img.shields.io/badge/opencv-%23white.svg?style=for-the-badge&logo=opencv&logoColor=white">
    </a>
    <a href="https://www.google.com/search?client=safari&rls=en&q=cmake&ie=UTF-8&oe=UTF-8">
        <img alt="CMake" src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white">
    </a>
    <a href="https://git-scm.com">
        <img alt="Build" src="https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white">
    </a>
</p>

### Basic Overview

This repository contains a sample example for deploying a PyTorch powered C++ application on a Linux machine. A detailed explanation of how to build this application can be found [here]().

### Installation

Clone the repository in your ```/usr/local/``` directory, and download the LibTorch library.
```bash
git clone https://github.com/lens-corp/LENS-deploy.git
cd LENS-deploy/PyTorch-CPP-Deployment
mkdir src && cd src
wget -O libtorch.zip https://download.pytorch.org/libtorch/cu111/libtorch-cxx11-abi-shared-with-deps-1.9.1%2Bcu111.zip
unzip libtorch.zip
rm libtorch.zip
```
Next step is to install OpenCV in your directory, this can be done using:
```bash
sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev libv4l-dev libatlas-base-dev libfaac-dev libmp3lame-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev libopencore-amrwb-dev x264 v4l-utils libsm6 libxext6
sudo apt install -y libgtk2.0-dev
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
unzip opencv.zip
rm opencv.zip
mkdir -p opencv && cd opencv
cmake -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_opencv_apps=OFF ../opencv-master
cmake --build . -j12
cd ..
```
This installs all the static libraries required for Opencv and OpenCV itself as well. The next step now is to build the application. This can be done using:
```bash
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local/LENS-DEPLOY/PyTorch-CPP-Deployment/src/libtorch .. && make -j32
```
This would add an application by name of infer-app in your build directory. The application can be run using:
```bash
./infer-app PATH_TO_IMAGE_FOLDER
```

### Converting PyTorch Model to JIT
A sample code has been added in this [file](model-to-jit..py) to convert a PyTorch model to JIT Traced model which can be used in C++.

### License
Copyright © 2020, LENS Inc.