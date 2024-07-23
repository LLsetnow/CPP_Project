#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 ����Ŀ�
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "ImgProcess.hpp"

using namespace std;
using namespace cv;
using namespace filesystem;
namespace fs = std::filesystem;

#pragma region ImgProcess

void ImgProcess::Mat2Array(cv::Mat& img, std::vector<std::vector<int>>& imgArray) 
{
    int imgHeight = img.rows;
    int imgWidth = img.cols;

    // ��ʼ�� imgArray �Ĵ�С
    imgArray.resize(imgHeight, std::vector<int>(imgWidth, 0));

    // ����ͼ������
    for (int i = 0; i < imgHeight; i++) 
    {
        for (int j = 0; j < imgWidth; j++) 
        {
            int value = img.at<uchar>(i, j); 
            if (value)
                imgArray[i][j] = white;
            else
                imgArray[i][j] = black;
        }

    }
}

void ImgProcess::Array2Mat(vector<vector<int>>& imgArray, Mat& img) // ����תͼ��
{
    int imgHeight = imgArray.size();
    int imgWidth = imgArray[0].size();

    // ����һ����ͨ��ͼ��
    img = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            int value = imgArray[i][j];
            switch (value)
            {
            case white:
                img.at<Vec3b>(i, j) = Vec3b(255, 255, 255); 
                break;
            case black:
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 0); 
                break;
            case blue:
                img.at<Vec3b>(i, j) = Vec3b(255, 0, 0); 
                break;
            case green:
                img.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                break;
            case red:
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
                break;
            }
        }
    }
}

void ImgProcess::OTSUBinary(Mat& img)
{
    // ��ͼ��ת��Ϊ�Ҷ�ͼ��
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // ִ�д�򷨶�ֵ��
    Mat binary;
    
    int thresh = threshold(gray, binary, black, white, THRESH_OTSU);

    if (thresh > 110)
        thresh = 110;
    if (thresh < 90)
        thresh = 90;

    threshold(gray, binary, thresh, white, THRESH_BINARY); // ��򷨶�ֵ������

    // ��������ͼ��ֵ�� img
    img = binary.clone();
}

#pragma endregion

#pragma region FilePath

FilePath::FilePath(string basePath)
{
    inputPath = basePath + "\\input";
    outputPath = basePath + "\\output";
    fileCount = 0;

}

int FilePath::CheckFolder(string basePath)
{
    string inputFolder = "input";
    string outputFolder = "output";
    fs::path inputPath = basePath + "\\" + inputFolder;
    fs::path outputPath = basePath + "\\" + outputFolder;
    int err = 0;
    if (!fs::exists(inputPath))
    {
        cout << "input �ļ��в�����" << endl;
        if (fs::create_directory(inputPath))
        {
            cout << "�Ѵ����ļ���" << inputPath <<  endl;
            cout << "�뽫������ͼ�����" << inputPath << endl;
        }
        else 
        {
            cout << "�����ļ���" << inputPath << "ʧ��" << endl;
        }
        err = 1;
    }

    if (!fs::exists(outputPath))
    {
        cout << "output �ļ��в�����" << endl;
        if (fs::create_directory(outputPath))
        {
            cout << "�Ѵ����ļ���" << outputPath << endl;
        }
        else
        {
            cout << "�����ļ���" << outputPath << "ʧ��" << endl;
        }
        err = 1;
    }

    if (err)
    {
        cout << "�����Ŀ¼" << basePath << "�Ƿ���ȷ" << endl;
        return 1;
    }
    else
        return 0;
}

void FilePath::CheckImg()
{
    if (fileCount == 0)
    {
        cout << "�ļ���" << inputPath << "��û��ͼ��" << endl;
        cout << "�����ļ������Ƿ���ͼ�� �Լ� ͼ���׺�Ƿ�Ϊbmp" << endl;
    }
}

void FilePath::GetName(const std::filesystem::path& imgPath)
{
    img = imread(imgPath.string());                   // ��ȡͼ��
    imgName = imgPath.stem().string();                // ��ȡ�ļ���
    imgOutput = outputPath + "\\" + imgName + ".jpg"; // �������ͼ��·��
    txtOutput = outputPath + "\\" + imgName + ".txt"; // ��������ı�·��
    fileCount++;
    txt.clear();
    txt += "********" + to_string(fileCount) + "********\n";
}


void FilePath::WriteTxt(void)
{
    ofstream f(txtOutput);
    f << txt;
    f.close();
}

#pragma endregion
