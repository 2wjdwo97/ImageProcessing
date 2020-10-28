#include "main.h"


int main(int, char**)
{
    vector<Mat> img_edge;
    vector<pair<int, int>> edge0;
    vector<pair<int, int>> edge1;
    vector<pair<int, int>> edge2;
    vector<pair<int, int>> edge3;

    for (int i = 1; i <= 4; i++) {
        Mat img = imread("C:\\input\\" + to_string(i) + ".jpg", IMREAD_GRAYSCALE);

        if (img.empty())
        {
            cout << "No Image:" + to_string(i) + ".jpg" << endl;
            return -1;
        }

        img_edge.push_back(detectEdge(img));
    }
    
    edge0 = getEdgeList(img_edge[0]);
    edge1 = getEdgeList(img_edge[1]);
    edge2 = getEdgeList(img_edge[2]);
    edge3 = getEdgeList(img_edge[3]);

    //// edge vector 출력
    // for (int i = 0; i < edge0.size(); i++)
    //    cout << edge0[i].first << "," << edge0[i].second << endl;
    
    // image 출력
    for (int i = 0; i < 4; i++)
        imshow("Image" + to_string(i), img_edge[i]);

    waitKey(0);

    return 0;
}
