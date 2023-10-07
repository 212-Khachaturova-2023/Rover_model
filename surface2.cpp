#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>

#define NUM 5
#define NUM_ST 2
#define NUM_BM 1
#define EPS 0.0001
//Хачатурова Ирина
//group 212
using namespace std;

class point {
protected:
    double x, y, z;
public:
    //class point constructor
    point(double xc = 0, double yc = 0, double zc = 0) {
        x = xc, y = yc, z = zc;
    }
};

//class hill is a subclass of class point
class hill : public point {
    friend class surface;
private:
    double sig_x, sig_y; //x, y - variance
    double var;
public:
    hill() = default;
    //class hill constructorgnuplot> set isosample 100

    hill(double xx = 0, double yy = 0, double zz = 0, double sig_xx = 0.5, double sig_yy = 0.5, double alpha = 1);
    double Gauss(double x0, double y0); //function generates hills using Gauss formulae
};

class stone {
private:
    double x, y;
    double r;
public:
    stone() = default;
    //class stone constructor
    stone(double xc, double yc, double rc);
    double sphere(double x0, double y0); //function generates stone models using spherical equation
};

class beam {
private:
    double x1, x2, y1, y2;
    double r;
public:
    beam() = default;
    //class beam constructor
    beam(double x1, double x2, double y1, double y2, double r);
    double cylinder(double x0, double y0); //function generates beam models using cylinder equation
};

class surface {
private:
    double dim_x, dim_y; //x-, y-dimensions
    hill* points[NUM]; //array for hills
    stone* stones[NUM_ST]; //array for stones
    beam* beams[NUM_BM]; //array for beams
public:
    //class surface constructor
    surface(double dim_x0 = 25.0, double dim_y0 = 25.0) {
        dim_x = dim_x0, dim_y = dim_y0;
    }
    void surf_generate(); //function randomly generates coordinates, variances, angles for the hills and stones
    void surf_print(); //function prints data to the file for GnuPlot
};

int main() {
    double DIM_X = 25;
    double DIM_Y = 25;
    surface off_road(DIM_X, DIM_Y); //new object from class surface
    off_road.surf_generate();
    off_road.surf_print();
    return 0;
}

hill::hill(double xx, double yy, double zz, double sig_xx, double sig_yy, double alpha) {
    x = xx, y = yy, z = zz;
    sig_x = abs(sig_xx) + 1;
    sig_y = abs(sig_yy) + 1;
    var = alpha;
}

double hill::Gauss(double x0, double y0) {
    return z * exp((-1) * (pow((-sin(var) * (x - x0) + cos(var) * (y - y0)), 2) / sig_x + pow((cos(var) * (x - x0) + sin(var) * (y - y0)), 2) / sig_y));
}

stone::stone(double xc, double yc, double rc) {
    x = abs(xc) + 1, y = abs(yc) + 1, r = abs(rc) + 1;
}

double stone::sphere(double x0, double y0) {
    if (r * r - pow((x - x0), 2) - pow((y - y0), 2) > EPS) {
        return sqrt(r * r - pow((x - x0), 2) - pow((y - y0), 2));
    }
    return 0;
}

beam::beam(double x1c, double x2c, double y1c, double y2c, double rc) {
    x1 = abs(x1c) + 1, x2 = abs(x2c) + 1;
    y1 = abs(y1c) + 1, y2 = abs(y2c) + 1;
    r = abs(rc) + 1;
}

double beam::cylinder(double x0, double y0) {
    double A = pow(y2 - y1, 2) + pow(x1 - x2, 2);
    double B1 = (-y1 * (x1 - x2) - x1 * (y2 - y1));
    double B2 = (x1 - x2) * (x1 + x2) / 2 - (y2 - y1) * (y2 + y1) / 2;
    double dr1 = abs((y2 - y1) * x0 + (x1 - x2) * y0 + B1) / sqrt(A);
    double dr2 = abs(-(x2 - x1) * x0 + (y2 - y1) * y0 + B2) / sqrt(A);
    if (pow(r, 2) > pow(dr1, 2) && A / 4 > pow(dr2, 2)) {
        return sqrt(pow(r, 2) - pow(dr1, 2));
    }
    return 0;
}

void surface::surf_generate() {
    srand(time(NULL));
    for (int i = 0; i < NUM; i++) {
        double x0 = rand() / double(RAND_MAX) * dim_x;
        double y0 = rand() / double(RAND_MAX) * dim_y;

        //heigth of bells between -5 and 5
        double z0 = rand() / double(RAND_MAX) * 10 - 5;

        double sig_x0 = rand() / double(RAND_MAX) * 2.9 + 0.1;
        double sig_y0 = rand() / double(RAND_MAX) * 2.9 + 0.1;

        double var_0 = rand() / double(RAND_MAX) * 10;

        //adding every hill to the array
        points[i] = new hill(x0, y0, z0, sig_x0, sig_y0, var_0);
    }

    for (int i = 0; i < NUM_ST; i++) {
        double x_st = rand() / double(RAND_MAX) * dim_x;
        double y_st = rand() / double(RAND_MAX) * dim_y;
        double r_st = rand() / double(RAND_MAX) * 0.9 + 0.1;

        //adding every stone to the array
        stones[i] = new stone(x_st, y_st, r_st);
    }

    for (int i = 0; i < NUM_BM; i++) {
        double x1_b = rand() / double(RAND_MAX) * dim_x;
        double y1_b = rand() / double(RAND_MAX) * dim_y;
        double x2_b = rand() / double(RAND_MAX) * dim_x;
        double y2_b = rand() / double(RAND_MAX) * dim_y;
        double r_b = rand() / double(RAND_MAX) * 0.09 + 0.1;

        //adding every beam to the array
        beams[i] = new beam(x1_b, x2_b, y1_b, y2_b, r_b);
    }
}

void surface::surf_print() {
    //opennig files for surface and stones
    ofstream fout_st("stone.txt");
    ofstream fout_b("beam.txt");
    ofstream fout_surf("func_s.txt");
    for (double i = 0.0; i - dim_x < EPS; i += 0.3) {
        for (double j = 0.0; j - dim_y < EPS; j += 0.3) {
            double h_sf = 0;
            double h_st = 0;
            double h_b = 0;
            for (int k = 0; k < NUM; k++) {
                h_sf += points[k]->Gauss(i, j);
            }
            fout_surf << i << " " << j << " " << h_sf << "\n";

            for (int m = 0; m < NUM_ST; m++) {
                h_st += stones[m]->sphere(i, j);
            }
            fout_st << i << " " << j << " " << h_st << "\n";
            
            for (int p = 0; p < NUM_BM; p++) {
                h_b += beams[p]->cylinder(i, j);
            }
            fout_b << i << " " << j << " " << h_b << "\n";
        }
        fout_st << "\n";
        fout_surf << "\n";
        fout_b << "\n";
    }
}
