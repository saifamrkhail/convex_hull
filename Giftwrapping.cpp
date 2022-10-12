#include "Giftwrapping.h"


void Giftwrapping::convexHull(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull)
{
	Timing* measureTime = Timing::getInstance();
	int num_points = points.size();
	if (num_points < 3) return;
	measureTime->startRecord("Giftwrapping");
	float x_min = points[0].x;
	int i_min = 0;
	for (int i = 0; i < num_points; i++) {
		if (points[i].x < x_min) {
			i_min = i;
			x_min = points[i].x;
		}
	}
	int p = i_min, q;
	do {
		hull.push_back(points[p]);
		q = (p + 1) % num_points;
		for (int i = 0; i < num_points; i++) {
			if (orient2d(points[p], points[q], points[i]) < 0) {
				q = i;
			}
		}
		p = q;
	} while (p != i_min);
	measureTime->stopRecord("Giftwrapping");
	measureTime->print(false);
}

void Giftwrapping::convexHullVis(std::vector<cv::Point2f> points, std::vector<cv::Point2f>& hull, cv::Mat& matrix)
{
	char key;
	cv::Scalar blue(255, 0, 0);
	cv::Scalar green(0, 255, 0);
	cv::Scalar red(0, 0, 255);
	cv::Scalar black(0, 0, 0);
	int num_points = points.size();
	if (num_points < 3) return;
	float x_min = points[0].x;
	int i_min = 0;
	for (int i = 0; i < num_points; i++) {
		if (points[i].x < x_min) {
			i_min = i;
			x_min = points[i].x;
		}
	}
	cv::imshow("Convex Hull", matrix);
	key = cv::waitKey(0);
	if (key == 27 || key == 'q' || key == 'Q')
		return;
	int p = i_min, q;
	do {
		hull.push_back(points[p]);
		if (hull.size() > 1) {
			cv::line(matrix, hull.end()[-2], hull.end()[-1], green, 5);
		}
		else {
			cv::line(matrix, hull.front(), hull.front(), green, 5);
		}
		cv::imshow("Convex Hull", matrix);
		key = cv::waitKey(0);
		if (key == 27 || key == 'q' || key == 'Q')
			return;
		q = (p + 1) % num_points;
		cv::line(matrix, points[p], points[p], blue, 10);
		cv::line(matrix, points[q], points[q], blue, 10);
		cv::imshow("Convex Hull", matrix);
		key = cv::waitKey(0);
		if (key == 27 || key == 'q' || key == 'Q')
			return;
		for (int i = 0; i < num_points; i++) {
			if (i == p || i == q) {
				continue;
			}
			cv::line(matrix, points[i], points[i], red, 10);
			cv::imshow("Convex Hull", matrix);
			key = cv::waitKey(0);
			if (key == 27 || key == 'q' || key == 'Q')
				return;
			if (orient2d(points[p], points[q], points[i]) > 0) {
				cv::line(matrix, points[i], points[i], blue, 10);
				cv::line(matrix, points[q], points[q], black, 10);
				q = i;
			}
			else {
				cv::line(matrix, points[i], points[i], black, 10);
			}
			cv::imshow("Convex Hull", matrix);
			key = cv::waitKey(0);
			if (key == 27 || key == 'q' || key == 'Q')
				return;
		}
		cv::line(matrix, points[p], points[p], black, 10);
		cv::line(matrix, points[q], points[q], black, 10);
		p = q;
	} while (p != i_min);
	cv::line(matrix, hull.end()[-1], hull.front(), green, 3);
	cv::imshow("Convex Hull", matrix);
	cv::waitKey(0);
}

float Giftwrapping::orient2d(cv::Point2f a, cv::Point2f b, cv::Point2f c)
{
	return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}
