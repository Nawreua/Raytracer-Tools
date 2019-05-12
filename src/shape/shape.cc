#include "shape.hh"

Shape::Shape()
    : material_(Material())
      ,transform_(Matrix::identity_matrix())
{ }

std::vector<Intersection> Shape::intersect(const Ray& ray)
{
    auto local_ray = ray.transform(transform_.inverse());
    return local_intersect(local_ray);
}

Tuple Shape::normal_at(const Tuple& p)
{
    auto local_point = transform_.inverse() * p;
    auto local_normal = local_normal_at(local_point);
    auto world_normal = transform_.inverse().transpose() * local_normal;
    world_normal.w_ = 0;
    return world_normal.normalize();
}

void Shape::set_transform(const Matrix& t)
{
    transform_ = t;
}

bool operator==(const Shape& lhs, const Shape& rhs)
{
    return lhs.material_ == rhs.material_
        && lhs.transform_ == rhs.transform_;
}

std::vector<Intersection> TestShape::local_intersect(const Ray& ray)
{
    saved_ray_ = ray;
    return std::vector<Intersection>();
}

Tuple TestShape::local_normal_at(const Tuple& p)
{
    return vector(p.x_, p.y_, p.z_);
}
