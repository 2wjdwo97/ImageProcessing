#pragma once

#include <opencv2/highgui.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>


#define RATIO 0.9

using namespace cv;
using namespace std;

// 직선 방정식 ax + by + c = 0
typedef struct line {
    int a;
    int b;
    int c;
}line;

template <typename T>
pair<int, int> getFarPoint(vector<pair<int, int>> points, T distFrom);
line calcLineEquation(pair<int, int> point1, pair<int, int> point2);
int calcDist(line lineEquation, pair<int, int> point);
int calcDist(pair<int, int> point1, pair<int, int> point2);
