#include "edgeDetect.h"


Mat detectEdge(Mat img)
{
    // horizontal
    Mat hor(img.rows, img.cols, CV_8U);

    for (int row = 1; row < img.rows - 1; row++)
    {
        for (int col = 0; col < img.cols - 2; col++)
        {
            uchar pixel;
            uchar curr = img.at<uchar>(row, col);
            uchar next = img.at<uchar>(row, col + 1);

            if (curr > next)
                pixel = curr - next;
            else
                pixel = next - curr;

            if (pixel > THRESHOLD)
                hor.at<uchar>(row, col + 1) = 0;
            else
                hor.at<uchar>(row, col + 1) = 255;
        }
    }

    // vertical
    Mat ver(img.rows, img.cols, CV_8U);

    for (int col = 1; col < img.cols - 1; col++)
    {
        for (int row = 0; row < img.rows - 2; row++)
        {
            uchar pixel;
            uchar curr = img.at<uchar>(row, col);
            uchar next = img.at<uchar>(row + 1, col);

            if (curr > next)
                pixel = curr - next;
            else
                pixel = next - curr;

            if (pixel > THRESHOLD)
                ver.at<uchar>(row + 1, col) = 0;
            else
                ver.at<uchar>(row + 1, col) = 255;
        }
    }

    // sum
    Mat edge = img.clone();

    for (int row = 1; row < img.rows - 1; row++) {
        for (int col = 1; col < img.cols - 1; col++) {
            uchar sum = ver.at<uchar>(row, col) + hor.at<uchar>(row, col);

            if (sum == 254)
                edge.at<uchar>(row, col) = 255;
            else
                edge.at<uchar>(row, col) = 0;
        }
    }

    return edge;
}


vector<pair<int, int>> getEdgeList(Mat img)
{
    vector<pair<int, int>> edge;
    int x, y;

    for (int row = 1; row < img.rows; row++) {
        for (int col = 1; col < img.cols; col++) {
            if (img.at<uchar>(row, col) == 0) {
                x = row;
                y = col;
                break;
            }
        }
    }

    dfs(x, y, img, edge);

    return edge;
}


void dfs(int x, int y, Mat img, vector<pair<int, int>>& edge)
{
    int nx, ny;
    edge.push_back(make_pair(x, y));
    img.at<uchar>(x, y) = 150;

    for (int i = 0; i < 8; i++) {
        nx = x + dx[i];
        ny = y + dy[i];

        if (nx >= img.rows || nx < 0 || ny >= img.cols || ny < 0)
            continue;

        if (img.at<uchar>(nx, ny) == 0)
            dfs(nx, ny, img, edge);
    }
}
