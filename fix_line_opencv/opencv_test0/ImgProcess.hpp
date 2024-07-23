#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 引入的库
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace filesystem;


enum color
{
    black,
    white,
    blue,
    green,
    red
};

class ImgProcess
{
public:
    Mat imgOut;
    void Mat2Array(Mat& img, vector<vector<int>>& imgArray); // 图像转数组
    void Array2Mat(vector<vector<int>>& imgArray, Mat& img); // 数组转图像
    void OTSUBinary(Mat& img);                               // 大津法二值化
 
private:

};

class FilePath
{
public:
    Mat img;
    string inputPath;
    string outputPath;

    string imgName;
    string imgOutput;
    string txtOutput;

    string txt;


    int fileCount;

    FilePath(string basePath);                                  // 传入根目录
    int CheckFolder(string basePath);                           // 检查文件夹是否存在
    void CheckImg(void);                                        // 检查input文件夹内是否有图像
    void GetName(const std::filesystem::path& entry);           // 获取文件名
    void WriteTxt(void);                                        // 写入文本


private:


};

