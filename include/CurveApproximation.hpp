#pragma once

#include <vector>
#include <igl/opengl/glfw/Viewer.h>
#include <BSplineCurve.hpp>

class CurveApproximation {
public:
    CurveApproximation();
    CurveApproximation(std::vector<Eigen::Vector3d> _D, unsigned int _h, unsigned int _p);

    void setUniformParam();
    void setChordLengthParam();
    void setCentripetalParam();

    std::vector<double> getBasisFuncs(double t);
    void buildBSplineCurve();           // build the approximation curve
public:
    BSplineCurve crv;

    std::vector<Eigen::Vector3d> D;     // datapoints;
    std::vector<Eigen::Vector3d> P;     // controlpoints;
    std::vector<double> t;              // parameter of datapoints;
    std::vector<double> knots;          // knots of approximation curve
    
    unsigned int n;                     // num of datapoints: n+1
    unsigned int h;                     // num of controlpoints: h+1
    unsigned int p;                     // degree of approximation curve
};