#include "vertexDetect.h"


// shape 결정하는 함수 return0 삼각형 return1 사각형
int determineShape(vector<pair<int, int>> edgePoints) {
    pair<int, int> firstCorner, secondCorner, thirdCorner, fourthCorner;

    firstCorner = getFarPoint(edgePoints, edgePoints.front());
    secondCorner = getFarPoint(edgePoints, firstCorner);
    thirdCorner = getFarPoint(edgePoints, calcLineEquation(firstCorner, secondCorner));

    int x1 = firstCorner.first;     int y1 = firstCorner.second;
    int x2 = secondCorner.first;    int y2 = secondCorner.second;
    int x3 = thirdCorner.first;     int y3 = thirdCorner.second;

    int nMaxDim = 0;

    for (vector<pair<int, int>>::iterator it = edgePoints.begin(); it != edgePoints.end(); ++it) {
        int x = it->first;
        int y = it->second;
        int nDim = abs((x1 * y2 + x2 * y + x * y1) - (x2 * y1 + x * y2 + x1 * y))
            + abs((x1 * y + x * y3 + x3 * y1) - (x * y1 + x3 * y + x1 * y3))
            + abs((x * y2 + x2 * y3 + x3 * y) - (x2 * y + x3 * y2 + x * y3));

        if (nDim > nMaxDim)
            nMaxDim = nDim;
    }

    float triDim = abs((x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)) / 2;
    float sqDim = (nMaxDim / 2 + triDim) / 2;

    if (sqDim / triDim > RATIO)
        return 0;  // triangle
    else
        return 1;  // square
}

// 직선 방정식 구하는 함수
line calcLineEquation(pair<int, int> point1, pair<int, int> point2) {
    line lineEquation;
    lineEquation.a = point1.second - point2.second;
    lineEquation.b = point2.first - point1.first;
    lineEquation.c = (point2.second - point1.second) * point1.first - (point2.first - point1.first) * point1.second;
    return lineEquation;
}

// 제일 멀리 떨어진 점 구하는 함수. distFrom - 점이나 직선 방정식 들어감
template <typename T>
pair<int, int> getFarPoint(vector<pair<int, int>> points, T distFrom) {
    pair<int, int> maxPoint;

    int max = 0;
    int temp = 0;

    for (vector<pair<int, int>>::iterator it = points.begin(); it != points.end(); ++it) {
        temp = calcDist(distFrom, *it);
        if (temp > max) {
            max = temp;
            maxPoint = *it;
        }
    }

    return maxPoint;
}

// 두 점 사이의 거리 (비교하는 거라서 정확한 값은 아님)
int calcDist(pair<int, int> point1, pair<int, int> point2) {
    return pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2);
}

// 직선과 점 사이의 거리 (비교하는 거라서 정확한 값은 아님)
int calcDist(line lineEquation, pair<int, int> point) {
    return abs(lineEquation.a * point.first + lineEquation.b * point.second + lineEquation.c);
}
