#include "elements.h"

Hill::Hill(double x, double y, double z, double sig_x, double sig_y, double angle) {
    x_cord = x;
    y_cord = y;
    z_cord = z;
    sig_x_c = sig_x;
    sig_y_c = sig_y;
    angle_c = angle;
}

double Hill::hill_height(double x, double y) {
    //getting z from the Gauss formulae
    double z = z_cord * exp((-1) * (pow(cos(angle_c) * (x - x_cord) + sin(angle_c) * (y - y_cord), 2) / (sig_x_c)+pow(-sin(angle_c) * (x - x_cord) + cos(angle_c) * (y - y_cord), 2) / sig_y_c));
    return z;
}

Stone::Stone(double x, double y, double rad) {
    x_cord = x;
    y_cord = y;
    r_st = rad;
}

double Stone::stone_height(double x0, double y0) {
    //checking the correctness of defining the height of the stone
    double z = pow(r_st, 2) - pow(x_cord - x0, 2) - pow(y_cord - y0, 2);
    if (z >= EPS) {
        return sqrt(z);
    }
    else {
        return 0;
    }
}

Beam::Beam(double x1, double y1, double x2, double y2, double radius) {
    x1_cord = x1;
    x2_cord = x2;
    y1_cord = y1;
    y2_cord = y2;
    beam_rad = radius;
}

double Beam::beam_height(double x0, double y0) {
    if (fabs(x2_cord - x1_cord) >= EPS) {

        double z = pow(beam_rad,2) - pow((y0 - (x0 - x1_cord) * (y2_cord - y1_cord) / (x2_cord - x1_cord) - y1_cord), 2);
        if (z >= 0 && fabs(y0 - ((x1_cord - x2_cord) * x0 / (y2_cord - y1_cord)) - (y1_cord + y2_cord) / 2 + (x1_cord - x2_cord) * (x1_cord + x2_cord) / (2 * (y2_cord - y1_cord))) <= sqrt(pow(x1_cord - x2_cord, 2) + pow(y1_cord - y2_cord, 2)) / 2) {
            return sqrt(z);
        }
        else {
            return 0;
        }
    }
    if (fabs(y2_cord - y1_cord) >= EPS) {
        double z = pow(beam_rad, 2) - pow(x0 - x1_cord, 2);
        if ((z >= 0) && ((y2_cord > y1_cord && y0 < y2_cord && y0 > y1_cord) || (y1_cord >= y2_cord && y0 >= y2_cord && y0 <= y1_cord))) {
            return sqrt(z);
        }
        else return 0;
    }
    else return 0;
}

Cursor::Cursor(double x, double y) {
    x_cord = x;
    y_cord = y;
}