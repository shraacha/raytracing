use crate::point::Point3D;

use std::ops::Deref;

#[derive(Clone, Copy, Default, Debug)]
pub struct Vector3D(Point3D);

impl Vector3D {
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self {
            0: Point3D::new(x, y, z),
        }
    }

    pub fn new_with_point(pt: Point3D) -> Self {
        Self { 0: pt }
    }

    pub fn length_squared(&self) -> f64 {
        self.x() * self.x() + self.y() * self.y() + self.z() * self.z()
    }

    pub fn length(&self) -> f64 {
        self.length_squared().sqrt()
    }
}

impl Deref for Vector3D {
    type Target = Point3D;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

fn dot(u: &Vector3D, v: &Vector3D) -> f64 {
    u.x() * v.x() + u.y() * v.y() + u.z() * v.z()
}

fn cross(u: &Vector3D, v: &Vector3D) -> Vector3D {
    Vector3D(Point3D::new(
        u.y() * v.z() - u.z() * v.y(),
        u.z() * v.x() - u.x() * v.z(),
        u.x() * v.y() - u.y() * v.x(),
    ))
}

fn unit_vector(v: &Vector3D) -> Vector3D {
    return Vector3D(v.div_with_f64(v.length()));
}
