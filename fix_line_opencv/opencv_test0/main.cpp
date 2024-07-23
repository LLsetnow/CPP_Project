/*
使用说明：
1. 像素点信息保存在imgArray中，用imgArray[i][j]可调用像素值。黑色为0，白色为1
2. file.txt 为每张图像记录的数据，可用file.txt += "说明" 添加内容。内容将保存为与图片同名的txt文件
3. imgProcess.Array2Mat(imgArray, imgOut) 将补线后的数组传入第一个参数
4. basePath 默认不需要修改，可以修改为图像所在文件夹，要求basePath目录下有"input" 和 "output" 文件夹
5. 工程根目录下添加"input"和“output"文件夹，并将待处理图像放在"input" 文件夹中，待处理图像默认为bmp格式
6. 补线图像写在 void Patchingline() 函数中，一般不用修改 main() 
7. 颜色表： （在ImgProcess.hpp文件中）
可将 imgArray[i][j] 的值赋值为对应颜色，转化为mat变量时，将转换为对应的RGB颜色
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
#include <filesystem>  // C++17 引入的库
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm> // 用于 std::sort
#include <regex>     // 用于提取数字

#include "ImgProcess.hpp"

using namespace std;
using namespace cv;
using namespace filesystem;


#define image_w 186
#define image_h 70

vector<vector<int>> imgArray;       // 原图数组
string basePath = "..";             // 相对路径，也可替换为图像文件所在绝对路径
Mat imgOut;                         // 输出图像
ImgProcess imgProcess;              // 图像处理类
FilePath file(basePath);            // 文件处理类

void Patchingline()
{
    // 在这里写补线函数
}


// 提取文件名中的数字
int extractNumber(const string& filename) {
    std::smatch match;
    std::regex regex("\\d+");
    if (std::regex_search(filename, match, regex)) {
        return std::stoi(match[0]); // 返回找到的第一个数字
    }
    return 0; // 如果没有找到数字，返回0
}


int main() 
{
    if (file.CheckFolder(basePath)) return 0;                   // 检查文件路径
    auto startZero = chrono::high_resolution_clock::now();      // 开始计时
    vector<path> imagePaths;                                    // 用于存储图像路径

    // 遍历文件夹中的所有文件并检查扩展名
    for (const auto& entry : directory_iterator(file.inputPath)) {
        if (entry.path().extension() == ".jpg") {
            imagePaths.push_back(entry.path());
        }
    }

    // 根据文件名中的数字对图像路径进行排序
    std::sort(imagePaths.begin(), imagePaths.end(), [](const path& a, const path& b) {
        return extractNumber(a.filename().string()) < extractNumber(b.filename().string());
        });


    // 遍历排序后的图像路径
    for (const auto& imgPath : imagePaths)
    {
        auto start = chrono::high_resolution_clock::now();  // 开始计时
        file.GetName(imgPath);                              // 获取当前图像文件
        if (file.img.channels() == 3)                       // 若传入彩图 进行二值化
            imgProcess.OTSUBinary(file.img);
        imgProcess.Mat2Array(file.img, imgArray);           // Mat 转 数组
        Patchingline();                                     // 补线处理
        imgProcess.Array2Mat(imgArray, imgOut);             // 数组转Mat
        imwrite(file.imgOutput, imgOut);                    // 保存图像
        file.WriteTxt();                                    // 写入文本
        auto end = chrono::high_resolution_clock::now();    // 获取时间
        chrono::duration<double> duration = end - start;    // 计算持续时间
        printf("第%d张图像%s 耗时%fms\n", file.fileCount, file.imgName.c_str(), duration.count() * 1000);
    }
    file.CheckImg();                                            // 检查文件夹内是否有图像
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_all = end - startZero;
    printf("\n图像处理完毕 共耗时%fms\n", duration_all.count() * 1000);
    printf("FPS: %2.f\n", file.fileCount / duration_all.count());
    return 0;
}




