# Seam Carving Project

## Overview
This project implements the **Seam Carving** algorithm for content-aware image resizing. Seam Carving is a technique used to resize images by removing or inserting seams (paths of least importance), which helps to preserve important features in the image while adjusting its size. It is especially useful for applications like resizing images without distorting faces, objects, or other important regions.

## Features
- **Content-Aware Resizing**: Reduces image size while preserving key features by removing low-energy pixels.
- **Energy Calculation**: Calculates the energy map of the image based on pixel intensity gradients (edges).
- **Seam Removal**: Uses dynamic programming to identify the lowest-energy seam and removes it from the image.
- **Resizes Width and Height**: You can input both the desired width and height, and the image will be resized accordingly by removing seams.

## Requirements
- **C++ Compiler**: The project is written in C++ and requires a C++ compiler (e.g., GCC or MSVC).
- **OpenCV**: The project uses OpenCV for image manipulation and visualization. Install OpenCV before building the project.

### Install OpenCV (Linux Example)
```bash
sudo apt-get install libopencv-dev
