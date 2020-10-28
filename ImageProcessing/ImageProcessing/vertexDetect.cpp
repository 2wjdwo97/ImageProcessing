#include "vertexDetect.h"


// shape �����ϴ� �Լ� return0 �ﰢ�� return1 �簢��
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

// ���� ������ ���ϴ� �Լ�
line calcLineEquation(pair<int, int> point1, pair<int, int> point2) {
    line lineEquation;
    lineEquation.a = point1.second - point2.second;
    lineEquation.b = point2.first - point1.first;
    lineEquation.c = (point2.second - point1.second) * point1.first - (point2.first - point1.first) * point1.second;
    return lineEquation;
}

// ���� �ָ� ������ �� ���ϴ� �Լ�. distFrom - ���̳� ���� ������ ��
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

// �� �� ������ �Ÿ� (���ϴ� �Ŷ� ��Ȯ�� ���� �ƴ�)
int calcDist(pair<int, int> point1, pair<int, int> point2) {
    return pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2);
}

// ������ �� ������ �Ÿ� (���ϴ� �Ŷ� ��Ȯ�� ���� �ƴ�)
int calcDist(line lineEquation, pair<int, int> point) {
    return abs(lineEquation.a * point.first + lineEquation.b * point.second + lineEquation.c);
}
