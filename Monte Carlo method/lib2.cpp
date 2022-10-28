#include "lib2.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <time.h>
using namespace std;

void generate_data2() {

    ofstream file("data2.txt");
    ofstream file_avg("avg2.txt");
    file << "number of points;" << "result" << endl;
    double avg[101];

    for (int n = 50; n <= 5000; n += 50) {
        double sum = 0;
        for (int i = 1; i <= 50; i++) {
            double result = integral2(n);
            file << n << ';' << result << endl;
            sum += result;
        }
        avg[n/50] = sum/static_cast<double>(50);
    }

    file.close();
    file_avg << "number of points;" << "average" << endl;

    for (int i = 1; i <= 100; i++) {
        file_avg << i * 50 << ';' << avg[i] << endl;
    }

    file_avg.close();
}

double integral2(const int n) {

    const double M = 1.01;
    double x[n];
    double y[n];
    const double a = 0.0;
    const double b = M_PI;
    srand(time(nullptr));
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> distx(a, b);
    uniform_real_distribution<double> disty(0, M);

    for (int i = 0; i < n; i++) {
        x[i] = distx(mt);
        y[i] = disty(mt);
    }

    int c = 0;
    for (int i = 0; i < n; i++) {
        if (y[i] <= f2(x[i])) {
            c++;
        }
    }

    double approx_integral = static_cast<double>(c)/static_cast<double>(n) * (b-a) * M;
    return approx_integral;
}

double f2(double num) {
    return sin(num);
}
