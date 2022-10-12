#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
#include <opencv2/core/types.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "Giftwrapping.h"

int main(int argc, char* argv[]) {
    std::ifstream infile("points.txt");
    std::string line;
    std::string x, y;
    std::vector<cv::Point2f> points;
    while (std::getline(infile, line)) {
        std::stringstream ls(line);
        std::getline(ls, x, ',');
        std::getline(ls, y);
        cv::Point2f p(std::stof(x), std::stof(y));
        points.push_back(p);
    }
    infile.close();


    cv::Mat whiteMatrix(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Scalar point_color(0, 0, 0);
    cv::namedWindow("Convex Hull");
    std::vector<cv::Point2f> hull;
    
    for (cv::Point p : points) {
        cv::line(whiteMatrix, p, p, point_color, 10);
    }
    Giftwrapping::convexHullVis(points, hull, whiteMatrix);
    /*
    cv::imshow("Convex Hull", whiteMatrix);
    cv::waitKey(0);
*/
    return 0;
}
