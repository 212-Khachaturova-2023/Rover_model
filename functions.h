#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#define EPS 1e-14
#define MAX_HILLS_HEIGHT 13
#define MAX_STONE_HEIGHT 10
#define MAX_BEAMS_HEIGHT 3
#define NET_STEP 0.1
using namespace std;

double get_random(double min, double max);
double get_sqr(const double& num);
bool is_extra_symbol_after_semicolon(string str);
bool is_substr(string str, string substr);
bool can_double_to_int(const double& num);
void printer_with_time(string message, ofstream& file);

extern size_t _max_rand_hills;
extern size_t _max_rand_stones;
extern size_t _max_rand_beams;