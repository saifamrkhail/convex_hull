#include <iostream>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include<bits/stdc++.h>
#include "divide_conquer.h"
using namespace cv;
using namespace std;

//OpenCV
static void help(char* argv[])
{
    cout << "\nThis sample program demonstrates the use of the convexHull() function\n"
         << "Call:\n"
         << argv[0] << endl;
}

int main(int argc, char* argv[]) {
    std::cout << "Divide and Conquer Algorithm" << std::endl;
    divide_conquer div_conq;

    vector<pair<int, int> > a;
    a.push_back(make_pair(0, 0));
    a.push_back(make_pair(1, -4));
    a.push_back(make_pair(-1, -5));
    a.push_back(make_pair(-5, -3));
    a.push_back(make_pair(-3, -1));
    a.push_back(make_pair(-1, -3));
    a.push_back(make_pair(-2, -2));
    a.push_back(make_pair(-1, -1));
    a.push_back(make_pair(-2, -1));
    a.push_back(make_pair(-1, 1));
    int n = a.size();
    sort(a.begin(), a.end());
    vector<pair<int, int> > ans = div_conq.divide(a);
    cout << "Convex Hull:\n";
    for (auto e: ans)
        cout << e.first << " " << e.second << endl;


    //OpenCV

    CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help"))
    {
        help(argv);
        return 0;
    }
    Mat img(500, 500, CV_8UC3);
    RNG& rng = theRNG();
    for (;;)
    {
        int i, count = (unsigned)rng % 30 + 20;
        vector<Point> points;
        for (i = 0; i < count; i++)
        {
            Point pt;
            pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
            pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
            points.push_back(pt);
        }
        vector<Point> hull;
        convexHull(points, hull, true);
        img = Scalar::all(0);
        for (i = 0; i < count; i++)
            circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
        polylines(img, hull, true, Scalar(0, 255, 0), 1, LINE_AA);
        imshow("convex hull", img);
        char key = (char)waitKey();
        if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
            break;
    }
    return 0;
}
