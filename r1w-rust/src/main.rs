mod color;
mod point;
mod vec;

use std::io::prelude::*;

use color::Color;
use point::Point3D;
use vec::Vec3D;

fn main() {
    // Bufwriter
    let mut out = std::io::BufWriter::new(std::io::stdout().lock());
    let mut err = std::io::BufWriter::new(std::io::stderr().lock());

    // Image
    let image_width: i32 = 256;
    let image_height: i32 = 256;

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
            let pixel_color: Color = Color::new_eat(Point3D::new_with(
                (i as f64) / (image_width - 1) as f64,
                (j as f64) / (image_width - 1) as f64,
                0.0,
            ));

            writeln!(out, "{pixel_color}").unwrap();
        }
    }

    writeln!(err, "\rDone.                          ").unwrap();
}
