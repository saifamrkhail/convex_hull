#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
#include <opencv2/core/types.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "Giftwrapping.h"
#include "DivideAndConquer.h"

void displayMenu() {
    std::cout << "===================================================== \n";
    std::cout << " \t\tMENU \t \n ";
    std::cout << "===================================================== \n";
    std::cout << "GIFTWRAPPING: \n";
    std::cout << " 1.Visualize for Random Points\n";
    std::cout << " 2.Test Performance for File Points\n";
    std::cout << "===================================================== \n";
    std::cout << "DIVIDE AND CONQUER: \n";
    std::cout << " 3.Visualize for Random Points\n";
    std::cout << " 4.Test Performance for File Points\n";
}

void generateRandPoints(std::vector<cv::Point2f>& points, int n, int xlim, int ylim) {
    cv::RNG& rng = cv::theRNG();
    for (int i = 0; i < n; i++) {
        points.push_back(cv::Point2f(rng.uniform(xlim / 8, xlim * 7 / 8), rng.uniform(ylim / 8, ylim * 7 / 8)));
    }
}

void pointsFromFile(std::vector<cv::Point2f>& points, std::string fname) {
    std::ifstream infile(fname);
    std::string line;
    std::string x, y;
    while (std::getline(infile, line)) {
        std::stringstream ls(line);
        std::getline(ls, x, ',');
        std::getline(ls, y);
        cv::Point2f p(std::stof(x), std::stof(y));
        points.push_back(p);
    }
    infile.close();
}

int main(int argc, char* argv[]) {

    int userSelect = -1;
    displayMenu();
    std::cin >> userSelect;
    std::vector<cv::Point2f> points;
    std::vector<cv::Point2f> hull;
    switch (userSelect)
    {
    case 1: {
        generateRandPoints(points, 20, 500, 500);
        cv::Mat whiteMatrix(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Scalar point_color(0, 0, 0);
        cv::namedWindow("Convex Hull");
        for (cv::Point p : points) {
            cv::line(whiteMatrix, p, p, point_color, 10);
        }
        Giftwrapping::convexHullVis(points, hull, whiteMatrix);
        break;
    }
    case 2: {
        std::cout << "Enter filename:" << std::endl;
        std::string fname;
        std::cin >> fname;
        std::cout << "Print Hull Points [Y/N]:" << std::endl;
        char prnt;
        std::cin >> prnt;
        pointsFromFile(points, fname);
        Giftwrapping::convexHull(points, hull);
        if (prnt == 'Y' || prnt == 'y') {
            for (cv::Point2f p : hull) {
                std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
            }
        }
        break;
    }
    case 3: {
        break; // VISUAL wie case 1 nur mit divide_conquer::convexHullVis(points, hull, whiteMatrix);
    }
    case 4: {
        std::cout << "Enter filename:" << std::endl;
        std::string fname;
        std::cin >> fname;
        std::cout << "Print Hull Points [Y/N]:" << std::endl;
        char prnt;
        std::cin >> prnt;
        pointsFromFile(points, fname);
        DivideAndConquer divideAndConquer;
        hull = divideAndConquer.convexHull(points);
        if (prnt == 'Y' || prnt == 'y') {
            for (cv::Point2f p : hull) {
                std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
            }
        }
        break; // performance wie case 2 nur mit divide_conquer::convexHull(points, hull);; 
    }
    default:
        break;
    }
    return 0;
}
