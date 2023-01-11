#pragma once

#include <iostream>
#include <igl/opengl/glfw/Viewer.h>

#include <vector>

class BSplineCurve {
public:
    BSplineCurve();
    BSplineCurve(int _degree, std::vector<Eigen::Vector3d> _conPts, std::vector<double> _knots);
    Eigen::Vector3d pt(double t);
public:
    std::vector<Eigen::Vector3d> conPts;       // 控制点
    std::vector<double> knots;
    int degree;
};
