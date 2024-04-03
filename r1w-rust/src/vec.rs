use crate::point::Point3D;

use std::ops::Deref;

pub struct Vec3D(Point3D);

impl Vec3D {
    pub fn length_squared(&self) -> f64 {
        self.x() * self.x() + self.y() * self.y() + self.z() * self.z()
    }

    pub fn length(&self) -> f64 {
        self.length_squared().sqrt()
    }
}

impl Deref for Vec3D {
    type Target = Point3D;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

fn dot(u: &Vec3D, v: &Vec3D) -> f64 {
    u.x() * v.x() + u.y() * v.y() + u.z() * v.z()
}

fn cross(u: &Vec3D, v: &Vec3D) -> Vec3D {
    Vec3D(Point3D::new_with(
        u.y() * v.z() - u.z() * v.y(),
        u.z() * v.x() - u.x() * v.z(),
        u.x() * v.y() - u.y() * v.x(),
    ))
}

fn unit_vector(v: &Vec3D) -> Vec3D {
    return Vec3D(v.div_with_f64(&v.length()));
}
