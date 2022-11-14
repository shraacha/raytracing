#include "rtweekend.h"

#include "colour.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>


colour ray_colour(const ray & r, const hittable & world) {
    hit_record rec;

    if(world.hit (r, 0, infinity, rec)) {                             // determining the colour of pixels if the cast ray contacts an object
        return 0.5 * (rec.normal + colour(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);   // the colour of the background
}

int main () {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
            colour pixel_colour = ray_colour(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone\n";
}
