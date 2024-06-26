#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    point3 orig;
    vec3 dir;

public:
    ray () {}
    ray (const point3 & origin, const vec3 & direction) : orig(origin), dir(direction) {}

    point3 origin () const { return orig; }
    vec3 direction () const { return dir; }

    // vector equation of a line in 3D, this allows us to get any point along the ray's path
    point3 at (double t) const {
        return orig + t * dir;
    }
};

#endif // RAY_H
