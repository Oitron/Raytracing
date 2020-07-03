#include<iostream>
using namespace std;

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    private:
        string magicNum;
        int width;
        int height;
        int maxVal;
        char *m_Ptr;

    public:
        Image();
        Image(int width_, int height_, int maxVal_, char* pixel);

    friend istream& operator>>(std::istream &inputStream, Image &img);
    friend ostream& operator<<(std::ostream &outputStream, Image &img);
};

#endif // IMAGE_H
