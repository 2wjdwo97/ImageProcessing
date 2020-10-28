#pragma once

#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <utility>

using namespace cv;
using namespace std;

const uchar THRESHOLD = 200;

const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

Mat detectEdge(Mat img);
vector<pair<int, int>> getEdgeList(Mat img);
void dfs(int x, int y, Mat img, vector<pair<int, int>>& edge);
