mod color;
mod point;
mod ray;
mod vec;

use std::io::prelude::*;

use color::Color;
use point::Point3D;
use ray::Ray;
use vec::Vector3D;

fn ray_color(r: &Ray) -> Color {
    Color::default()
}

fn main() {
    // Bufwriter
    let mut out = std::io::BufWriter::new(std::io::stdout().lock());
    let mut err = std::io::BufWriter::new(std::io::stderr().lock());

    // Image
    let aspect_ratio: f64 = 16.0 / 9.0;
    let image_width: u64 = 400;

    // Calculating image height, and ensuring that it's at least 1
    let image_height: u64 = (image_width as f64 / aspect_ratio) as u64;

    // Camera
    let focal_length: f64 = 1.0;
    let viewport_height: f64 = 2.0; // real valued unlike the image dimensions
    let viewport_width: f64 = viewport_height * (image_width as f64 / image_height as f64);
    let camera_center: Point3D = Point3D::default();

    // Calculating the vectors across the horiz/down the vert viewport edges
    let viewport_u: Vector3D = Vector3D::new(viewport_width, 0.0, 0.0);
    let viewport_v: Vector3D = Vector3D::new(0.0, -viewport_height, 0.0);

    // Calculating the horiz/vert delta vectors from pixel to pixel
    let pixel_delta_u = viewport_u.div_with_f64((image_width as f64).clone());
    let pixel_delta_v = viewport_v.div_with_f64((image_height as f64).clone());

    // Calculate the location of the upper left pixel
    let viewport_upper_left: Point3D = camera_center
        - *Vector3D::new(0.0, 0.0, focal_length.clone()) // z_axis is negative in the forward dir
        - viewport_u.div_with_f64(2.0)
        - viewport_v.div_with_f64(2.0);
    let pixel00_loc: Point3D =
        viewport_upper_left + (pixel_delta_u + pixel_delta_v).mul_with_f64(0.5);

    // Render
    writeln!(out, "P3\n{image_width} {image_height}\n255").unwrap();

    for j in 0..image_height {
        write!(
            err,
            "\rScanlines remaining: {prog} ",
            prog = image_height - j
        )
        .unwrap();

        for i in 0..image_width {
            let pixel_center: Point3D = pixel00_loc
                + pixel_delta_u.div_with_f64((i as f64).clone())
                + pixel_delta_v.div_with_f64((j as f64).clone());
            let ray_direction: Vector3D = Vector3D::new_with_point(pixel_center - camera_center);

            let r: Ray = Ray::new(&pixel_center, &ray_direction);

            let pixel_color: Color = ray_color(&r);

            writeln!(out, "{pixel_color}").unwrap();
        }
    }

    writeln!(err, "\rDone.                          ").unwrap();
}
