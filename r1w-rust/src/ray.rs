use crate::point::Point3D;
use crate::vec::Vector3D;

#[derive(Clone, Copy, Default, Debug)]
pub struct Ray {
    orig: Point3D,
    dir: Vector3D,
}

impl Ray {
    pub fn new(origin: &Point3D, direction: &Vector3D) -> Self {
        Ray {
            orig: origin.clone(),
            dir: direction.clone(),
        }
    }

    pub fn origin(&self) -> Point3D {
        self.orig
    }

    pub fn direction(&self) -> Vector3D {
        self.dir
    }

    pub fn at(&self, t: f64) -> Point3D {
        self.orig + self.dir.mul_with_f64(t)
    }
}
