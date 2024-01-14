#include "elements.h"

Hill::Hill(const double& x0, const double& y0, const double& z0, const double& sig_x, const double& sig_y, const double& ax_rotat_angle) {
    x = x0;
    y = y0;
    z = z0;
    sigma_x = sig_x;
    sigma_y = sig_y;
    rotation_angle = ax_rotat_angle;
}

double Hill::get_hill_height(const double& x0, const double& y0) {
    double z = 0;
    if (fabs(x - x0) < 4 * sigma_x || fabs(x - x0) < 4 * sigma_y || fabs(y - y0) < 4 * sigma_x || fabs(y - y0) < 4 * sigma_y) {
        z = z * exp((-1) * (get_sqr(cos(rotation_angle) * (x - x0) + sin(rotation_angle) * (y - y0)) / (sigma_x)+get_sqr(-sin(rotation_angle) * (x - x0) + cos(rotation_angle) * (y - y0)) / sigma_y));
        return z;
    }
    else return 0;
}

Beam::Beam(const double& x1_0, const double& y1_0, const double& x2_0, const double& y2_0, const double& radius) {
    x1 = x1_0;
    x2 = x2_0;
    y1 = y1_0;
    y2 = y2_0;
    beam_rad = radius;
}

double Beam::get_beam_height(const double& x0, const double& y0) {

    if (fabs(x2 - x1) >= EPS) {

        double z = get_sqr(beam_rad) - get_sqr(y0 - (x0 - x1) * (y2 - y1) / (x2 - x1) - y1);
        if (z >= 0 && fabs(y0 - ((x1 - x2) * x0 / (y2 - y1)) - (y1 + y2) / 2 + (x1 - x2) * (x1 + x2) / (2 * (y2 - y1))) <= sqrt(get_sqr(x1 - x2) + get_sqr(y1 - y2)) / 2) {
            return sqrt(z);
        }
        else {
            return 0;
        }
    }
    if (fabs(y2 - y1) >= EPS) {
        double z = get_sqr(beam_rad) - get_sqr(x0 - x1);
        if ((z >= 0) && ((y2 > y1 && y0 < y2 && y0 > y1) || (y1 >= y2 && y0 >= y2 && y0 <= y1))) {
            return sqrt(z);
        }
        else return 0;
    }
    else return 0;
}

Stone::Stone(const double& x0, const double& y0, const double& radius) {
    x = x0;
    y = y0;
    radius_stone = radius;
}

double Stone::get_stone_height(const double& x0, const double& y0)
{
    double z = get_sqr(radius_stone) - get_sqr(x - x0) - get_sqr(y - y0);
    if (z >= 0) {
        return sqrt(z);
    }
    else {
        return 0;
    }
}

Cursor::Cursor(const double & x0 , const double & y0){
    x = x0;
    y = y0;
}