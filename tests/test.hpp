#pragma once

#include <iostream>
#include <CurveApproximation.hpp>
#include <fstream>
#include <igl/opengl/glfw/Viewer.h>
igl::opengl::glfw::Viewer viewer;

#define RED Eigen ::RowVector3d(1, 0, 0)
#define GREEN Eigen ::RowVector3d(0, 1, 0)
#define BLUE Eigen ::RowVector3d(0, 0, 1)
#define YELLOW Eigen ::RowVector3d(1, 1, 0)
#define WHITE Eigen ::RowVector3d(1, 1, 1)
#define BLACK Eigen ::RowVector3d(0, 0, 0)

void readDataPoints(std::vector<Eigen::Vector3d> &dataPoints) {
    std::ifstream ifs;
    ifs.open("../../data/data1.txt");
    if (!ifs.is_open())
	{
		std::cout << "error！" << std::endl;
        return ;
	}
    std::string buf;
    Eigen::Vector3d Point;
    // std::vector<Eigen::Vector3d> dataPoints;
    while (getline(ifs, buf)) {
        int pos = 0, index = 0;
        for (int i = 0; i <= buf.size(); i++) {
            if (buf[i] == ' ' || i == buf.size()) {
                auto temp = atof(buf.substr(pos, i - pos).c_str());
                Point(index++) = temp;
                pos = i + 1;
            }
        }
        dataPoints.push_back(Point);
    }
    ifs.close();
}

// 展示数据点
void showDataPoints(std::vector<Eigen::Vector3d> dataPoints, Eigen::RowVector3d color) {
    for (int i = 0; i < dataPoints.size(); i++) {
        viewer.data().add_points((Eigen::RowVector3d)dataPoints[i], color);
    }
}

// 展示拟合后的曲线
void showCurve(BSplineCurve &crv, Eigen::RowVector3d color) {
    for (double t = 0.0; t <= 1.0; t += 1.0 / 512) {
        auto point = crv.pt(t);
        viewer.data().add_points((Eigen::RowVector3d)point, color);
    }
}

void test() {
    std::vector<Eigen::Vector3d> dataPoints;
    readDataPoints(dataPoints);

    CurveApproximation appr(dataPoints, 7, 2);
    appr.setCentripetalParam();
    appr.buildBSplineCurve();

    showDataPoints(dataPoints, RED);
    showCurve(appr.crv, GREEN);
    // 输出拟合后的控制点
    std::cout << "拟合后的控制点如下：" << std::endl;
    for (auto i : appr.crv.conPts) {
        std::cout << i(0) << ", " << i(1) << ", " << i(2) << std::endl;
    }

    viewer.data().point_size = 3;
    viewer.launch();
}