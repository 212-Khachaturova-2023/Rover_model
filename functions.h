#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#define _USE_MATH_DEFINES
#define EPS 0.00000001
#define MAX_HILL_HEIGHT 15
#define MAX_STONE_HEIGHT 5
#define MAX_BEAM_HEIGHT 3
#define NET_STEP 0.5

using namespace std;

//function generates random nuber between min and max
//argumnts: minimum and maximum values
double get_random(double min, double max);

//function defines if there is an extra symbol in the given string
//arguments: string
bool is_extra_symbol_after_semicolon(string str);

//function defines if substring is in the string
//arguments: string, substring
bool is_substr(string str, string substr);

//function returns time of the completed action
//arguments: string, file 
void time_print(string message, ofstream& file);

extern size_t _max_rand_hills;
extern size_t _max_rand_stones;
extern size_t _max_rand_beams;