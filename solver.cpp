#include "Solver.h"

Solver::Solver(double m, double L, double x0, double y0, double v0)
    : m(m), L(L), x0(x0), y0(y0), v0(v0), t1(0), t2(0), dt(0) {
    x_data.push_back(x0);
    y_data.push_back(y0);
}

void Solver::setTimeInterval(double t1, double t2, double dt) {
    this->t1 = t1;
    this->t2 = t2;
    this->dt = dt;
}

double Solver::g(double t) {
    return g0 + 0.05 * sin(omega * t);
}

void Solver::run() {
    double x = x0;
    double y = y0;
    double vx = -v0 * (x0 / sqrt(x0*x0 + y0*y0)); // Начальная скорость по x
    double vy = -v0 * (y0 / sqrt(x0*x0 + y0*y0)); // Начальная скорость по y
    double t = t1;

    while (t <= t2) {
        // double r = sqrt(x*x + y*y);
        double T = m * (vx*vx + vy*vy + g(t) * y) / L; // T из второго уравнения для y

        // Обновление скоростей
        double ax = -T * x / (m * L);
        double ay = -T * y / (m * L) - g(t);

        // Интегрирование методом Эйлера
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;

        // Сохранение данных
        x_data.push_back(x);
        y_data.push_back(y);

        t += dt;
    }
}

std::vector<double> Solver::X() {
    return x_data;
}

std::vector<double> Solver::Y() {
    return y_data;
}
