#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
        point3 center;
        double radius;

public:
        sphere () {};
        sphere (point3 cen, double r) : center(cen), radius(r) {};
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit (const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Finding the nearest square root that lies within the acceptable range (t_min to t_max)
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius; // vector from the center of the sphere to the point on the sphere, divided by the length of the vector
    rec.set_face_normal(r, outward_normal);

    return true;
}


#endif // SPHERE_H_
