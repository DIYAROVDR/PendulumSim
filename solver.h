#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <cmath>
#include <vector>

class Solver {
public:
    Solver(double m, double L,double x0,double y0,double v0);
    void setTimeInterval(double t1, double t2, double dt);
    void run();
    std::vector<double> X();
    std::vector<double> Y();
private:
    void run_euler(double t0, double t1, double dt, std::vector<double>& y);
    std::vector<double> derivatives(double t, const std::vector<double>& y);
    double g(double t);
    double m,L,x0,y0,v0,t1,t2,dt;
    std::vector<double> x_data;
    std::vector<double> y_data;
    const double g0 = 9.81; // Среднее ускорение свободного падения, м/с^2
    const double omega = 2 * M_PI;
};

#endif // SOLVER_H
