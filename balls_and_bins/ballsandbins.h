#ifndef BALLS_AND_BINS_BALLSANDBINS_H
#define BALLS_AND_BINS_BALLSANDBINS_H
#include <fstream>

void generate_data1();
void generate_data2();
void do_experiment1(int n, std::ofstream& file);
void do_experiment2(int n, std::ofstream& file);
void throw_ball(int* tab, const int n, int random_bin);
bool if_first_collision(int* tab, const int n);
int count_empty_bins(int* tab, const int n);
bool end_of_experiment(int* tab, const int n);
int maximum_load(int* tab, const int n);

#endif //BALLS_AND_BINS_BALLSANDBINS_H
