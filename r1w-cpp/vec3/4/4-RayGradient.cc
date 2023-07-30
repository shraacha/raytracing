#include "vec3.h"
#include "colour.h"
#include "ray.h"

#include <iostream>

/*
 * The gradient is based off the height of the vector **after** normalization
 * This means that we get both a vertical and horizontal gradient:
 * - when we normalize the ray vectors, the rays on one scan line will have varying heights once normalized
*/

colour ray_colour(const ray & r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
    // the first part of the expression creates a white to black gradient based on t
    // the second part of the gradient makes the black to <defined rgb colour> gradient
    // adding the two colours creates the white - to - colour gradient
}

/*
** Trying to make a vertical linear gradient
** - not the best way to do it, since it is specific to the viewport height, however this works by taking the height of the ray in proportion to the
** camera pane,
** - since the camera pane goes from the y range [-1, 1], and it is centered at the origin, we need to divide the ray height by 1/2 the height of the pane
** - since the pane itself is 2 units tall, turns out that the ray height is already scaled properly
*/
colour ray_colour_1(const ray & r) {
    auto t = 0.5*((r.direction()).y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.2, 1.0);
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
            colour pixel_colour = ray_colour_1(r);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone\n";
}
