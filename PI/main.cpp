#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <time.h>
using namespace std;

void generate_points(double* x, double* y, const int n);
double PI_approx(const int n);

int main() {
    ofstream file("pi.txt");
    file << "number of points;" << "est" << endl;
    double avg[101];

    for (int n = 50; n <= 5000; n += 50) {
        double sum = 0;
        for (int i = 1; i <= 50; i++) {
            double result = PI_approx(n);
            file << n << ';' << result << endl;
            sum += result;
        }
        avg[n/50] = sum/static_cast<double>(50);
    }

    file << endl << "number of points;" << "average" << endl;

    for (int i = 1; i <= 100; i++) {
        file << i * 50 << ';' << avg[i] << endl;
    }

    file.close();
    return 0;
}

/**
 * Function generating random points (x,y), -1.0 <= x, y <= 1.0
 * @param x array containing values of x
 * @param y array containing values of y
 * @param n number of generated points
 */
void generate_points(double* x, double* y, const int n) {

    srand(time(nullptr));
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> dist(-1.0, 1.0);

    for (int i = 0; i < n; i++) {
        x[i] = dist(mt);
        y[i] = dist(mt);
    }
}

/**
 * Function estimating the value of π using Monte Carlo method.
 * @param n number of generated random points
 * @return approximation of Pi
 */
double PI_approx(const int n) {

    double x[n];
    double y[n];
    generate_points(x, y, n);

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (x[i] * x[i] + y[i] * y[i] <= 1.0) {
            cnt++;
        }
    }
    double result = static_cast<double>(cnt)/static_cast<double>(n) * 4.0;
    return result;
}
