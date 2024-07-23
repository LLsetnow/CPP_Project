/*
ʹ��˵����
1. ���ص���Ϣ������imgArray�У���imgArray[i][j]�ɵ�������ֵ����ɫΪ1����ɫΪ0
2. file.txt Ϊÿ��ͼ���¼�����ݣ�����file.txt += "˵��" ������ݡ����ݽ�����Ϊ��ͼƬͬ����txt�ļ�
3. imgProcess.Array2Mat(imgArray, imgOut) �����ߺ�����鴫���һ������
4. basePath Ĭ�ϲ���Ҫ�޸ģ������޸�Ϊͼ�������ļ��У�Ҫ��basePathĿ¼����"input" �� "output" �ļ���
5. ���̸�Ŀ¼�����"input"�͡�output"�ļ��У�����������ͼ�����"input" �ļ����У�������ͼ��Ĭ��Ϊbmp��ʽ
6. ����ͼ��д�� void Patchingline() �����У�һ�㲻���޸� main() 
7. ��ɫ�� ����ImgProcess.hpp�ļ��У�
�ɽ� imgArray[i][j] ��ֵ��ֵΪ��Ӧ��ɫ��ת��Ϊmat����ʱ����ת��Ϊ��Ӧ��RGB��ɫ
enum color
{
    black,
    white,
    blue,
    green,
    red
};
*/

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 ����Ŀ�
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm> // ���� std::sort
#include <regex>     // ������ȡ����

#include "ImgProcess.hpp"

using namespace std;
using namespace cv;
using namespace filesystem;


#define image_w 186
#define image_h 70

vector<vector<int>> imgArray;       // ԭͼ����
string basePath = "..";             // ���·����Ҳ���滻Ϊͼ���ļ����ھ���·��
Mat imgOut;                         // ���ͼ��
ImgProcess imgProcess;              // ͼ������
FilePath file(basePath);            // �ļ�������

void Patchingline()
{
    // ������д���ߺ���
}


// ��ȡ�ļ����е�����
int extractNumber(const string& filename) {
    std::smatch match;
    std::regex regex("\\d+");
    if (std::regex_search(filename, match, regex)) {
        return std::stoi(match[0]); // �����ҵ��ĵ�һ������
    }
    return 0; // ���û���ҵ����֣�����0
}


int main() 
{
    if (file.CheckFolder(basePath)) return 0;                   // ����ļ�·��
    auto startZero = chrono::high_resolution_clock::now();      // ��ʼ��ʱ
    vector<path> imagePaths;                                    // ���ڴ洢ͼ��·��

    // �����ļ����е������ļ��������չ��
    for (const auto& entry : directory_iterator(file.inputPath)) {
        if (entry.path().extension() == ".jpg") {
            imagePaths.push_back(entry.path());
        }
    }

    // �����ļ����е����ֶ�ͼ��·����������
    std::sort(imagePaths.begin(), imagePaths.end(), [](const path& a, const path& b) {
        return extractNumber(a.filename().string()) < extractNumber(b.filename().string());
        });


    // ����������ͼ��·��
    for (const auto& imgPath : imagePaths)
    {
        auto start = chrono::high_resolution_clock::now();  // ��ʼ��ʱ
        file.GetName(imgPath);                              // ��ȡ��ǰͼ���ļ�
        if (file.img.channels() == 3)                       // �������ͼ ���ж�ֵ��
            imgProcess.OTSUBinary(file.img);
        imgProcess.Mat2Array(file.img, imgArray);           // Mat ת ����
        Patchingline();                                     // ���ߴ���
        imgProcess.Array2Mat(imgArray, imgOut);             // ����תMat
        imwrite(file.imgOutput, imgOut);                    // ����ͼ��
        file.WriteTxt();                                    // д���ı�
        auto end = chrono::high_resolution_clock::now();    // ��ȡʱ��
        chrono::duration<double> duration = end - start;    // �������ʱ��
        printf("��%d��ͼ��%s ��ʱ%fms\n", file.fileCount, file.imgName.c_str(), duration.count() * 1000);
    }
    file.CheckImg();                                            // ����ļ������Ƿ���ͼ��
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_all = end - startZero;
    printf("\nͼ������� ����ʱ%fms\n", duration_all.count() * 1000);
    printf("FPS: %2.f\n", file.fileCount / duration_all.count());
    return 0;
}




