use crate::point::Point3D;

use std::ops::Deref;

#[derive(Clone, Copy, Default, Debug)]
pub struct Color(Point3D);

impl Color {
    pub fn new(point: Point3D) -> Self {
        Color(point)
    }
}

impl Deref for Color {
    type Target = Point3D;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl std::fmt::Display for Color {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            // Write the translated [0,255] value of each color component.
            f,
            "{} {} {}",
            (255.999 * self.x()) as i32,
            (255.999 * self.y()) as i32,
            (255.999 * self.z()) as i32,
        )
    }
}
