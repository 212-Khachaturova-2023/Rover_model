#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <math.h>

//Хачатурова Ирина
//group 212
using namespace std;

//class for points on surface
class point {
protected:
    double x, y, z; //x, y, z-coordinates
    double sig_x = 0.5, sig_y = 0.5; //x, y-variance
public:
    //class constructor
    point(double xc = 0.0, double yc = 0.0, double zc = 0.0) {
        x = xc;
        y = yc;
        z = zc;
    }
};

class surface {
    friend class stone;
private:
    double dim_x = 25.0, dim_y = 25.0;
    int count = 40;
    string func = "splot ";
public:
    surface(double length = 25.0, double width = 25.0, int num = 40);
    void print_file(ofstream& file);
};

//function printing formula to the file
void surface::print_file(ofstream& file) {
    file << func;
}

surface::surface(double length, double width, int num) {
    double dim_x = length;
    double dim_y = width;
    int count = num;
    for (int i = 0; i < count; i++) {
        double x0 = rand() / double(RAND_MAX) * dim_x - dim_x / 2;
        double y0 = rand() / double(RAND_MAX) * dim_y - dim_y / 2;
        //heigth of bells between -5 and 5
        double z0 = rand() / double(RAND_MAX) * 10 - 5;

        double sig_x0 = rand() / double(RAND_MAX) * 2.9 + 0.1;
        double sig_y0 = rand() / double(RAND_MAX) * 2.9 + 0.1;

        if (i != count - 1) {
            func += to_string(z0) + '*' + "exp(-((x -" + to_string(x0) + ")**2 / (2 * " + to_string(sig_x0) + "**2) + " + "(y -" + to_string(y0) + ")**2 / (2 * " + to_string(sig_y0) + "**2))) + ";
        }
        else {
            func += to_string(z0) + '*' + "exp(-((x -" + to_string(x0) + ")**2 / (2 * " + to_string(sig_x0) + "**2) + " + "(y -" + to_string(y0) + ")**2 / (2 * " + to_string(sig_y0) + "**2)))";
        }
    }
}

int main() {
    srand(time(NULL));
    ofstream file_surf;
    file_surf.open("func_s.txt");
    surface off_road(25, 25, 25); //creating new object a in class surface
    off_road.print_file(file_surf);
    file_surf.close();
    return 0;
}
