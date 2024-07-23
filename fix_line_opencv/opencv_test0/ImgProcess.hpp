#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 ����Ŀ�
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
    void Mat2Array(Mat& img, vector<vector<int>>& imgArray); // ͼ��ת����
    void Array2Mat(vector<vector<int>>& imgArray, Mat& img); // ����תͼ��
    void OTSUBinary(Mat& img);                               // ��򷨶�ֵ��
 
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

    FilePath(string basePath);                                  // �����Ŀ¼
    int CheckFolder(string basePath);                           // ����ļ����Ƿ����
    void CheckImg(void);                                        // ���input�ļ������Ƿ���ͼ��
    void GetName(const std::filesystem::path& entry);           // ��ȡ�ļ���
    void WriteTxt(void);                                        // д���ı�


private:


};

