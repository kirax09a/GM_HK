#include "BSplineCurve.hpp"

BSplineCurve::BSplineCurve() {

}

BSplineCurve::BSplineCurve(int _degree, std::vector<Eigen::Vector3d> _conPts, std::vector<double> _knots) {
    degree = _degree;
    conPts = _conPts;
    knots = _knots;    
}

Eigen::Vector3d BSplineCurve::pt(double t) {
    std::vector<double> N(conPts.size());      // 存放每个控制点对应的系数
    for (int i = 0; i < N.size(); i++) {
        N[i] = 0.0;
    }
    if (t == knots[0]) {
        N[0] = 1.0;
    } else if (t == knots[knots.size()-1]) {
        N[conPts.size() - 1] = 1.0;
    } else {
        unsigned int k;
        for (k = 0; k < knots.size() - 1; k++) {
            if (t >= knots[k] && t < knots[k + 1]) {
                break;
            }
        }
        N[k] = 1.0;
        for (unsigned int d = 1; d <= degree; d++)
	    {
            N[k - d] = ((knots[k + 1] - t) / (knots[k + 1] - knots[(k - d) + 1])) * N[(k - d) + 1];
            for (unsigned int i = k - d + 1; i <= k-1; i++)
            {
                N[i] =
                    ((t - knots[i]) / (knots[i + d] - knots[i])) * N[i] +
                    ((knots[i + d + 1] - t) / (knots[i + d + 1] - knots[i + 1])) * N[i + 1];
            }
            N[k] = ((t - knots[k]) / (knots[k + d] - knots[k])) * N[k];
        }
    }
    Eigen::Vector3d ret(0.0, 0.0, 0.0);
    for (int i = 0; i < conPts.size(); i++) {
        ret += N[i] * conPts[i];
    }

    // debug
    // for (auto i : N) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;


    return ret;
}

