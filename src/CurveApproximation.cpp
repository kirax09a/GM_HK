#include <CurveApproximation.hpp>

CurveApproximation::CurveApproximation() {}

CurveApproximation::CurveApproximation(std::vector<Eigen::Vector3d> _D, unsigned int _h, unsigned int _p) {
    D = _D;

    n = D.size() - 1;
    h = _h;
    p = _p;

    // D.resize(n + 1);
    t.resize(n + 1);
    P.resize(h + 1);

    // set knots
    knots.resize(h + p + 2, 0.0);
    for (int i = 0; i <= p; i++) {
        knots[i] = 0.0;
        knots[knots.size() - 1 - i] = 1.0;
    }
    double step = static_cast<double>(1.0 / (h - p + 1));
    for (int i = p + 1; i < h + 1; i++) {
        knots[i] = knots[i - 1] + step;
    }
}

void CurveApproximation::setUniformParam() {
    const double low = 0.0;
    const double high = 1.0;

    t[0] = low;
    t[n] = high;

    double step = (high - low) / static_cast<double>(n);
    for (int i = 1; i < n; i++) {
        t[i] = t[i - 1] + step;
    }
}

void CurveApproximation::setChordLengthParam() {
    const double low = 0.0;
    const double high = 1.0;

	t[0] = low;
	t[n] = high;

	double Lk = 0;
	double L = 0;
	for (int i = 1; i < n; i++)
	{
		auto v = D[i] - D[i - 1];
		L += sqrt(static_cast<double>(v.dot(v)));

	}
	for (int i = 1; i < n; i++)
	{
		auto v = D[i] - D[i - 1];
		Lk += sqrt(static_cast<double>(v.dot(v)));
		t[i] = low + (high - low) * (Lk / L);
	}
}

void CurveApproximation::setCentripetalParam() {
    const double low = 0.0;
    const double high = 1.0;

	t[0] = low;
	t[n] = high;

	double Lk = 0;
	double L = 0;
	for (int i = 1; i < n; i++)
	{
		auto v = D[i] - D[i - 1];
		L += sqrt(sqrt(static_cast<double>(v.dot(v))));
	}
	for (int i = 1; i < n; i++)
	{
		auto v = D[i] - D[i - 1];
		Lk += sqrt(sqrt(static_cast<double>(v.dot(v))));
		t[i] = low + (high - low) * (Lk / L);
	}
}

std::vector<double> CurveApproximation::getBasisFuncs(double t) {
    std::vector<double> N(h + 1);      // 存放每个控制点对应的系数
    for (int i = 0; i < N.size(); i++) {
        N[i] = 0.0;
    }
    if (t == knots[0]) {
        N[0] = 1.0;
    } else if (t == knots[knots.size()-1]) {
        N[h] = 1.0;
    } else {
        unsigned int k;
        for (k = 0; k < knots.size() - 1; k++) {
            if (t >= knots[k] && t < knots[k + 1]) {
                break;
            }
        }
        N[k] = 1.0;
        for (unsigned int d = 1; d <= p; d++)
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
    return N;
}

void CurveApproximation::buildBSplineCurve() {
    std::vector<std::vector<double>> basis;
    basis.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        basis[i] = getBasisFuncs(t[i]);
    }

    std::vector<Eigen::Vector3d> Q(n + 1);
    for (int k = 0; k <= n; k++) {
        Q[k] = D[k] - basis[k][0] * D[0] - basis[k][h] * D[n];
    }

    Eigen::MatrixXd N(n - 1, h - 1);
    for (int k = 1; k <= n - 1; k++) {
        for (int i = 1; i <= h - 1; i++) {
            N(k - 1, i - 1) = basis[k][i];
        }
    }

    Eigen::VectorXd Q1(h - 1), Q2(h - 1), Q3(h - 1);
    for (int i = 1; i <= h - 1; i++) {
        double temp1 = 0.0;
        double temp2 = 0.0;
        double temp3 = 0.0;
        for (int k = 1; k <= n - 1; k++) {
            temp1 += basis[k][i] * Q[k](0);
            temp2 += basis[k][i] * Q[k](1);
            temp3 += basis[k][i] * Q[k](2);
        }
        Q1(i - 1) = temp1;
        Q2(i - 1) = temp2;
        Q3(i - 1) = temp3;
    }

    Eigen::MatrixXd NT(h - 1, n - 1);
    NT = N.transpose();
    auto NTN = NT * N;
    Eigen::VectorXd x = NTN.colPivHouseholderQr().solve(Q1);
	Eigen::VectorXd y = NTN.colPivHouseholderQr().solve(Q2);
	Eigen::VectorXd z = NTN.colPivHouseholderQr().solve(Q3);

    P[0] = D[0];
    P[h] = D[n];
    for (int i = 1; i <= h - 1; i++) {
        Eigen::Vector3d pt;
        pt(0) = x(i - 1);
        pt(1) = y(i - 1);
        pt(2) = z(i - 1);
        P[i] = pt;
    }

    crv.knots = knots;
    crv.conPts = P;
    crv.degree = p;
}