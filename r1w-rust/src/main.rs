use std::io::prelude::*;

fn main() {
    // Bufwriter
    let mut out = std::io::BufWriter::new(std::io::stdout().lock());
    let mut err = std::io::BufWriter::new(std::io::stderr().lock());

    // Image
    let image_width:  i32 = 256;
    let image_height: i32 = 256;

    // Render

    writeln!(out, "P3\n{image_width} {image_height}\n255").unwrap();

    for j in 0..image_height {
        write!(err, "\rScanlines remaining: {prog} ", prog = image_height - j).unwrap();
        for i in 0..image_width {
            let r = i as f64 / (image_width - 1) as f64;
            let g = j as f64 / (image_height - 1) as f64;
            let b = 0 as f64;

            let ir: i32 = (255.999 * r) as i32;
            let ig: i32 = (255.999 * g) as i32;
            let ib: i32 = (255.999 * b) as i32;

            writeln!(out, "{ir} {ig} {ib}").unwrap();
        }
    }

    writeln!(err, "\rDone.                          ").unwrap();
}
