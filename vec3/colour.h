#ifndef COLOUR_H_
#define COLOUR_H_

#include "vec3.h"

#include <iostream>

void write_colour(std::ostream &out, colour pixel_colour) {
    // Writing the translated [0,255] value of each colour component
    out << static_cast<int>(255.999 * pixel_colour.x()) << ' '
        << static_cast<int>(255.999 * pixel_colour.y()) << ' '
        << static_cast<int>(255.999 * pixel_colour.z()) << '\n';
}


#endif // COLOUR_H_
