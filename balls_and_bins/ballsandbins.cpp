#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <time.h>
#include "ballsandbins.h"
using namespace std;

/*
 * B - number of the first collision (two balls in the same bin)
 * U - number of empty bins after n throws
 * L - maximum load after n throws
 * C - min number of throws with no empty bins after (minimum one ball in every bin)
 * D - min number of throws with min 2 balls in every bin after (coupon collector’s brother)
 * DminC = D - C
 */

/*
 * Generates B, U, L and saves it to a file.
 */
void generate_data1() {

    ofstream file("results1.txt");
    file << "n;B;U;L\n";
            //"U;L;C;D;DminC\n";

    for (int n = 1000; n <= 100000; n += 1000) {
        for (int k = 1; k <= 50; k++) {
            do_experiment1(n, file);
        }
    }
    file.close();
}

/*
 * Generates C, D, DminC and saves it to a file.
 */
void generate_data2() {

    ofstream file("results2.txt");
    file << "n;C;D;DminC\n";

    for (int n = 1000; n <= 100000; n += 1000) {
        for (int k = 1; k <= 50; k++) {
            do_experiment2(n, file);
        }
    }
    file.close();
}

void do_experiment1(int n, ofstream& file) {

    int bin[n];
    int B = 0;
    int U = 0;
    int L = 0;
    int num = 0;

    for (int i = 0; i < n; i++) {
        bin[i] = 0;
    }

    while (!(if_first_collision(bin, n)) || num < n) {
        throw_ball(bin, n);
        num++;

        if (if_first_collision(bin, n) && B == 0) {
            B = num;
        }

        if (num == n) {
            U = count_empty_bins(bin, n);
            L = maximum_load(bin, n);
        }
    }

    file << n << ';' << B << ';' << U << ';' << L << '\n';
}

void do_experiment2(int n, ofstream& file) {

    int bin[n];
    int C = 0;
    int D;
    int DminC;
    int num = 0;

    for (int i = 0; i < n; i++) {
        bin[i] = 0;
    }

    while (!(end_of_experiment(bin, n))) {
        throw_ball(bin, n);
        num++;

        if (num >= n && C == 0 && count_empty_bins(bin, n) == 0) {
            C = num;
        }
    }

    D = num;
    DminC = D - C;
    file << n << ';' << C << ';' << D << ';' << DminC << '\n';
}

void throw_ball(int* tab, const int n) {
    srand(time(nullptr));
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> dist(0, n);
    int random_bin = floor(dist(mt));
    if (random_bin == n) {
        random_bin--;
    }
    tab[random_bin] = tab[random_bin] + 1;
}

bool if_first_collision(int* tab, const int n) {
    for (int i = 0; i < n; i++) {
        if (tab[i] > 1) {
            return true;
        }
    }
    return false;
}

int count_empty_bins(int* tab, const int n) {
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (tab[i] == 0) {
            num++;
        }
    }
    return num;
}

int maximum_load(int* tab, const int n) {
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (tab[i] > mx) {
            mx = tab[i];
        }
    }
    return mx;
}

bool end_of_experiment(int* tab, const int n) {
    for (int i = 0; i < n; i++) {
        if (tab[i] < 2) {
            return false;
        }
    }
    return true;
}