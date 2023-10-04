#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <math.h>

#define NUM 25
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
    string func;
public:
    hill(double xx = 0, double yy = 0, double zz = 0, double sig_xx = 0.5, double sig_yy = 0.5, double alpha = 1);
};

hill::hill(double xx, double yy, double zz, double sig_xx, double sig_yy, double alpha) {
    x = xx, y = yy, z = zz;
    sig_x = sig_xx;
    sig_y = sig_yy;
    var = alpha;
    func = to_string(z) + "* exp((-1) * (((-sin(" + to_string(var) + ") * (x - (" + to_string(x) + ")) + cos(" + to_string(var) + ") * (y - (" + to_string(y) + ")))**2) / " + to_string(sig_x) + " + ((cos(" + to_string(var) + ") * (x - (" + to_string(x) + ")) + sin(" + to_string(var) + ") * (y - (" + to_string(y) + ")))**2) / " + to_string(sig_y) + ")) ";
}

class surface {
private:
    double dim_x = 25.0, dim_y = 25.0;

    hill* points[NUM];
public:
    surface(ofstream & file, double length = 25.0, double width = 25.0);
    double h(double x, double y);
    void print_file(ofstream& file);
};

surface::surface(ofstream & file, double length, double width) {
    double dim_x = length;
    double dim_y = width;
    file << "splot" << " ";
    for (int i = 0; i < NUM; i++) {
        double x0 = rand() / double(RAND_MAX) * dim_x - dim_x / 2;
        double y0 = rand() / double(RAND_MAX) * dim_y - dim_y / 2;

        //heigth of bells between -5 and 5
        double z0 = rand() / double(RAND_MAX) * 10 - 5;

        double sig_x0 = rand() / double(RAND_MAX) * 2.9 + 0.1;
        double sig_y0 = rand() / double(RAND_MAX) * 2.9 + 0.1;

        double var_0 = rand() / double(RAND_MAX) * 10;

        //adding raandomly generated points to the array with objects from class hill
        points[i] = new hill(x0, y0, z0, sig_x0, sig_y0, var_0); 

        if (i < NUM - 1) {
            file << points[i]->func << " + ";
        } else {
            file << points[i]->func;
        }
    }
}

int main() {
    srand(time(NULL));
    ofstream file_surf;
    file_surf.open("func_s.txt");
    surface off_road(file_surf, 25, 25); //creating new object a in class surface
    return 0;
}
