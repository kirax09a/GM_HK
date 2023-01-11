#include "test.hpp"

int main(int argc, char const *argv[])
{
    test();

    return 0;
}


// int main(int argc, char const *argv[])
// {
//     std::vector<Eigen::Vector3d> pts = {
//         {-3, 0, 0},
//         {-1, 4, 0},
//         {1, -5, 0},
//         {2, 1, 0},
//         {4, -1, 0},
//         {6, 2, 0},
//         {8, 4, 0}
//     };
//     int degree = 2;
//     std::vector<double> knots = {0, 0, 0, 1, 2, 3, 4, 5, 5, 5};
//     BSplineCurve crv(degree, pts, knots);
    
//     std::vector<Eigen::Vector3d> dataPoints;
//     while (1) {
//         Eigen::Vector3d temp;
//         std::cin >> temp(0) >> temp(1) >> temp(2);
//         if (temp(0) == 1.0) break;
//         dataPoints.push_back(temp);
//     }
//     std::cout << "num of dataPoints: ";
//     std::cout << dataPoints.size() << std::endl;
//     // for (double i = 0.0; i <= 5.0; i += 5.0 / 10000) {
//     //     dataPoints.push_back(crv.pt(i));
//     // }

//     CurveApproximation appr(99, 4, 2);
//     appr.D = dataPoints;

//     // // appr.setUniformParam();
//     // // appr.setChordLengthParam();
//     appr.setCentripetalParam();

//     appr.buildBSplineCurve();

//     // 输出拟合后的控制点
//     for (auto i : appr.crv.conPts) {
//         std::cout << (Eigen::RowVector3d)i << std::endl;
//     }
    
//     // std::cout << "Hello, World!" << std::endl;
//     // std::vector<Eigen::Vector3d> pts = {
//     //     {-3, 0, 0},
//     //     {-1, 4, 0},
//     //     {1, -5, 0},
//     //     {2, 1, 0},
//     //     {4, -1, 0},
//     //     {6, 2, 0},
//     //     {8, 4, 0}
//     // };
//     // int degree = 2;
//     // std::vector<double> knots = {0, 0, 0, 1, 2, 3, 4, 5, 5, 5};

//     // BSplineCurve crv(degree, pts, knots);

//     // std::cout << crv.pt(0.0) << std::endl;

//     // std::cout << "-----------------------------------------------" << std::endl;
//     // for (double t = 0.0; t <= 5.0; t += 1.0) {
//     //     std::cout << (Eigen::RowVector3d)crv.pt(t) << std::endl;
//     // }
//     // std::cout << "-----------------------------------------------" << std::endl;
//     // for (double t = 0.0; t <= 1.0; t += 0.2) {
//     //     std::cout << (Eigen::RowVector3d)appr.crv.pt(t) << std::endl;
//     // }

//     // crv.pt(1.2);

//     // std::cout << "---------------------------------------" << std::endl;



//     // CurveApproximation appr(10, 6, 2);
//     // appr.setUniformParam();

//     // std::vector<double> basis;
//     // basis = appr.getBasisFuncs(1.2);

//     // for (auto i:basis) {
//     //     std::cout << i << " ";
//     // }
//     // std::cout << std::endl;

//     // for (auto i:appr.t) {
//     //     std::cout << i << " ";
//     // }
//     // std::cout << std::endl;
//     // for (auto i:appr.knots) {
//     //     std::cout << i << " ";
//     // }
//     // std::cout << std::endl;


//     return 0;
// }

