#include "main.h"


int main(int, char**)
{
    vector<Mat> edge_images;
    vector<vector<pair<int, int>>> edges;

    for (int i = 0; i < IMAGE_NUMBER; i++) {
        // input
        Mat img = imread("C:\\input\\" + to_string(i + 1) + ".jpg");
        if (img.empty())
        {
            cout << "No Image:" + to_string(i + 1) + ".jpg" << endl;
            return -1;
        }

        // edge detection
        edge_images.push_back(detectEdge(img));

        // labeling (push the coordinates of the edge pixels into the vector)
        edges.push_back(getEdgeList(edge_images[i]));

        // print detected edges as images
        namedWindow("Image" + to_string(i + 1));
        imshow("Image" + to_string(i + 1), edge_images[i]);

        // print results (whether it is triangle or square)
        if (determineShape(edges[i]) == 0)
            cout << "triangle" << endl;
        else if (determineShape(edges[i]) == 1)
            cout << "square" << endl;
        else
            cout << "error" << endl;

    }

    //// print edges in vector form
    //for (int i = 0; i < IMAGE_NUMBER; i++)
    //    for (int j = 0; j < edges[i].size(); j++)
    //        cout << edges[i][j].first << ", " << edges[i][j].second << endl;

    waitKey(0);

    return 0;
}
