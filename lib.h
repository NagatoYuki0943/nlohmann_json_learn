// main.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <vector>

// TODO: 在此处引用程序需要的其他标头。
struct TargetState
{
    double ratio = 0.0;                       // 缩放比例
    std::vector<int> box = {};                // box 位置
    std::vector<double> standard_center = {}; // 标准靶标中心坐标
};

void parse_vector(const int indent = 4);

void parse_map(const int indent = 4);
