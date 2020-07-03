#include "Image.h"
#include <iostream>
using namespace std;

Image::Image(){
    magicNum = "P6";
    width = 1;
    height = 1;
    maxVal = 1;
    size_t size = width*height*3;
    m_Ptr = new char[size];
}

Image::Image(int width_, int height_, int maxVal_, char* img){
    magicNum = "P6";
    width = width_;
    height = height_;
    maxVal = maxVal_;
    size_t size = width_*height_*3;
    m_Ptr = img;
}

std::ostream& operator<<(std::ostream &outputStream, Image &img){
    outputStream << "P6" << "\n" << img.width << " " << img.height << "\n" << img.maxVal << "\n";
    size_t size = img.width*img.height*3;
    outputStream.write(img.m_Ptr, size);
    return outputStream;
}
