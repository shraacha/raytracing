#include "vec3.h"
#include "colour.h"
#include "ray.h"

#include <iostream>

/*
** A sphere can be represented by:
** x^2 + y^2 + z^2 = r^2
**
** A sphere with center point C can be represented by:
** (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
**
** We can use vector notation for this:
*/
double hit_sphere(const point3& center, double radius, const ray &r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4 * a * c;
    if (discriminant < 0.0) {            // don't completely understand why we return -1 here, can t not be negative?
        return -1.0;
    } else {
        // since the rays are all facing towards the sphere, solving for their intersection with the
        // sphere must return a positive scaling of the ray's direction vector
        return (-b - sqrt(discriminant)) / (2.0 * a);
        // taking the solution with the negative sqrt(discriminant) gives us the first intersection with the sphere
    }
}

/*
 * The gradient is based off the height of the vector **after** normalization
 * This means that we get both a vertical and horizontal gradient:
 * - when we normalize the ray vectors, the rays on one scan line will have varying heights once normalized
*/

colour ray_colour(const ray & r) {
    // Sphere Collision
    auto t = hit_sphere(point3(0, 0, -1.0), 0.5, r);
    // if the ray intersects with the sphere, we will use the normal to give some idea of the 3 dimensional aspect of the sphere

    if (t > 0.0) {
        // the normal is the intersection point of the ray and sphere (i.e. the ray at scale t), minus the center of the sphere
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1.0));
        // just converting the normal vector coordinates to values between 0 & 1, and converting to rgb
        return 0.5 * colour(N.x() + 1, N.y() + 1, N.z() + 1);
    }


    // Background
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
    // the first part of the expression creates a white to black gradient based on t
    // the second part of the gradient makes the black to <defined rgb colour> gradient
    // adding the two colours creates the white - to - colour gradient
}

int main () {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0 , 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; j--) {
    std::cerr << "\rScan lines remaining:" << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            colour pixel_colour = ray_colour(r);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone\n";
}
