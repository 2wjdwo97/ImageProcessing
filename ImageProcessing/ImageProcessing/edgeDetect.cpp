#include "edgeDetect.h"


Mat detectEdge(Mat img)
{
    Mat img_horizental(img.rows + 2, img.cols + 2, CV_8UC3, Scalar(255, 255, 255));
    Mat img_vertical(img.rows + 2, img.cols + 2, CV_8UC3, Scalar(255, 255, 255));
    Mat img_edge(img.rows + 2, img.cols + 2, CV_8UC3, Scalar(255, 255, 255));
    
    // expand image
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            img_horizental.at<Vec3b>(row + 1, col + 1) = img.at<Vec3b>(row, col);
            img_vertical.at<Vec3b>(row + 1, col + 1) = img.at<Vec3b>(row, col);
        }
    }

    // extract only horizontal elements of the edges of the shapes from the image
    for (int row = 0; row < img_horizental.rows - 1; row++)
    {
        for (int col = 0; col < img_horizental.cols - 1; col++)
        {
            // get the RGB value of the pixel
            Vec3b v_curr = img_horizental.at<Vec3b>(row, col);
            Vec3b v_next = img_horizental.at<Vec3b>(row, col + 1);

            // grayscale of the pixel
            uchar curr = (v_curr[0] + v_curr[1] + v_curr[2]) / 3;
            uchar next = (v_next[0] + v_next[1] + v_next[2]) / 3;

            // difference of adjacent pixels
            uchar pixel;

            if (curr > next)
                pixel = curr - next;
            else
                pixel = next - curr;

            // mark with black only if the pixel is above the THRESHOLD
            if (pixel > THRESHOLD)
                img_edge.at<Vec3b>(row, col + 1) = Vec3b(0, 0, 0);
            else
                img_edge.at<Vec3b>(row, col + 1) = Vec3b(255, 255, 255);
        }
    }

    // extract only vertical elements of the edges of the shapes from the image
    for (int row = 0; row < img_vertical.rows - 1; row++)
    {
        for (int col = 0; col < img_vertical.cols - 1; col++)
        {
            // get the RGB value of the pixel
            Vec3b v_curr = img_vertical.at<Vec3b>(row, col);
            Vec3b v_next = img_vertical.at<Vec3b>(row + 1, col);

            // grayscale of the pixel
            uchar curr = (v_curr[0] + v_curr[1] + v_curr[2]) / 3;
            uchar next = (v_next[0] + v_next[1] + v_next[2]) / 3;

            // difference of adjacent pixels
            uchar pixel;

            if (curr > next)
                pixel = curr - next;
            else
                pixel = next - curr;

            // horizontal element + vertical element
            // mark with black only if the pixel is above the THRESHOLD
            if (pixel > THRESHOLD)
                img_edge.at<Vec3b>(row + 1, col) = Vec3b(0, 0, 0);
            else
            {
                if (img_edge.at<Vec3b>(row + 1, col) == Vec3b(0, 0, 0))
                    img_edge.at<Vec3b>(row + 1, col) = Vec3b(0, 0, 0);
            }
        }
    }

    return img_edge;
}


// Store the coordinates of the edge pixel in vectors from the image.
vector<pair<int, int>> getEdgeList(Mat img)
{
    vector<pair<int, int>> edge;
    int x = -1;
    int y = -1;

    // find the first pixel included in the edge
    bool isBreak = false;
    for (int row = 1; row < img.rows; row++) {
        for (int col = 1; col < img.cols; col++) {
            if (img.at<Vec3b>(row, col) == Vec3b(0, 0, 0)) {
                x = row;
                y = col;
                isBreak = true;
                break;
            }
        }
        if (isBreak)
            break;
    }

    if (x == -1 || y == -1) {
        cout << "error: no edge";
        exit(1);
    }

    // dfs
    dfs(x, y, img, edge);
    cout << x << " " << y;

    return edge;
}


// find all pixels that are included in the edge beginning with the first pixel
void dfs(int x, int y, Mat img, vector<pair<int, int>>& edge)
{
    int nx, ny;
    edge.push_back(make_pair(x, y));
    img.at<Vec3b>(x, y) = Vec3b(0, 0, 255);     // change searched pixels into red

    for (int i = 0; i < 8; i++) {
        nx = x + dx[i];
        ny = y + dy[i];

        if (nx >= 0 && nx < img.rows && ny >= 0 && ny < img.cols)
            if (img.at<Vec3b>(nx, ny) == Vec3b(0, 0, 0))
                dfs(nx, ny, img, edge);
    }
}
