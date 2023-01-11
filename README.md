# CurveApproximation



### 项目结构

```C++
├── include  
    ├── BSplineCurve.hpp
    ├── CurveApproximation.hpp
├── src  
    ├── BSplineCurve.cpp
    ├── CurveApproximation.cpp
├── data  
    ├── data1.txt
├── tests
    ├── main.cpp
    ├── test.hpp
```
### 项目简介
```c++
/*	
    下面是B样条曲线的定义，conPts保存控制点，knots保存节点向量
    degree为B样条曲线的次数
*/
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
/*	
    下面是拟合类的定义
*/
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
```

### 编译方法

#### 依赖

具体依赖于如下库：

* `libigl`
* `OpenGL`
* `glfw`
* `Eigen`
* `glad`

#### 编译

项目环境: `Ubuntu20.04`

编译方法：

```shell
mkdir build && cd build
cmake ..
make
```

编译成功后，会在build/tests目录下生成`test`可执行文件。

### 使用方法

命令行输入`./test`

#### 运行效果
