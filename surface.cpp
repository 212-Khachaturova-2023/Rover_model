#include "surface.h"

size_t _max_rand_hills;
size_t _max_rand_beams;
size_t _max_rand_stones;

Surface::Surface(double surf_len, double surf_wid, double degree) {
    length = surf_len;
    width = surf_wid;
    variance = degree;
    //points = new Point[int(length * width / NET_STEP /NET_STEP)];
    double rand_x, rand_y, rand_z, rand_sig_y, rand_sig_x, rand_rad, rand_angle, rand_x2, rand_y2;
    srand(time(NULL));
    for (size_t i = 0; i < _max_rand_hills; i++) {
        //getting random value between lenth/10 and length * 9/10
        rand_x = get_random(length / 10, length * 9 / 10);
        rand_y = get_random(width / 10, width * 9 / 10);

        //getting random value between -MAX_HILL_HIGHT / 2 and MAX_HILL_HEIGHT
        rand_z = get_random(-MAX_HILL_HEIGHT / 2, MAX_HILL_HEIGHT);

        //getting random value between degree / 5 and degree
        rand_sig_x = get_random(degree / 5, degree);
        rand_sig_y = get_random(degree / 5, degree);
        
        //getting random angle value between 0 and pi
        rand_angle = get_random(0, 2 * 3.1415);

        //adding generated hill to hills array
        hills.push_back(Hill(rand_x, rand_y, rand_z, rand_sig_x, rand_sig_y, rand_angle));
    }

    for (size_t i = 0; i < _max_rand_stones; i++) {
        //getting random value between length/10 and length * 9/10
        rand_x = get_random(length / 10, length * 9 / 10);

        //getting random value between width/10 and width * 9/10
        rand_y = get_random(width / 10, width * 9 / 10);

        //getting random value between -MAX_HILL_HEIGHT/2 and MAX_HILL_HEIGHT
        rand_z = get_random(-MAX_HILL_HEIGHT / 2, MAX_HILL_HEIGHT);

        //getting random angle value between 0 and MAX_STONE_HEIGHT
        rand_rad = get_random(0, MAX_STONE_HEIGHT);

        //adding generated stone to the stones array
        stones.push_back(Stone(rand_x, rand_y, rand_rad));
    }

    for (size_t i = 0; i < _max_rand_beams; i++) {
        //getting random value between length/10 and length * 9/10
        rand_x = get_random(length / 10, length * 9 / 10);
        rand_x2 = get_random(length / 10, length * 9 / 10);

        //getting random value between width/10 and width * 9/10
        rand_y = get_random(width / 10, width * 9 / 10);
        rand_y2 = get_random(width / 10, width * 9 / 10);

        //getting random angle value between 0 and MAX_STONE_HEIGHT
        rand_rad = get_random(0, MAX_BEAM_HEIGHT);

        //adding generated beam to the beams array
        beams.push_back(Beam(rand_x, rand_y, rand_x2, rand_y2, rand_rad));
    }
}

bool Surface::add_hill(double x, double y, double z, double sig_x, double sig_y, double angle) {
    //checking if generated values fits dimensions of the surface
    if (x > -EPS && y > -EPS && x < length && y < width) {
        hills.push_back(Hill(x, y, z, sig_x, sig_y, angle));
        return true;
    }
    else {
        return false;
    }
}

bool Surface::add_beam(double x1, double y1, double x2, double y2, double radius) {
    //checking if generated values fits dimensions of the surface
    if (x1 > -EPS && y1 > -EPS && x1 < length && y1 < width && x2 > -EPS && y2 > -EPS && x2 < length && y2 < width) {
        beams.push_back(Beam(x1, y1, x2, y2, radius));
        return true;
    }
    else {
        return false;
    }
}

bool Surface::add_stone(double x, double y, double radius) {
    //checking if generated values fits dimensions of the surface
    if (x > 0 && y > 0 && x < length && y < width) {
        stones.push_back(Stone(x, y, radius));
        return true;
    }
    else {
        return false;
    }
}

/*void Surface::file_print(ofstream& file) {
    for (int i = 0; i < length/NET_STEP; i += 1) {
        for (int j = 0; j < width/NET_STEP; j += 1) {
            //points[i+int(length/NET_STEP)*j] = Point(i*NET_STEP, j * NET_STEP, surface_height(i*NET_STEP, j*NET_STEP));
            //file << i* NET_STEP << " " << j*NET_STEP << " " << points[i + int(length / NET_STEP) * j].z << "\n";
        }
    }
}*/

double Surface::surface_height(double x0, double y0) {
    double z = 0;
    //summing up z-coordinstes of hills, stones and beams in the given point (x0, y0)
    for (size_t i = 0; i < hills.size(); i++) {
        z += hills[i].hill_height(x0, y0);
    }
    for (size_t i = 0; i < stones.size(); i++) {
        z += stones[i].stone_height(x0, y0);
    }
    for (size_t i = 0; i < beams.size(); i++) {
        z += beams[i].beam_height(x0, y0);
    }
    return z;
}