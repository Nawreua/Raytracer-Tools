#include "sphere.hh"

Sphere::Sphere()
    : material_(Material())
{
    float grid[][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    transform_ = Matrix(grid);
}

std::vector<Intersection> Sphere::intersect(const Ray& ray)
{
    std::vector<Intersection> res;

    auto transformed_ray = ray.transform(transform_.inverse());
    auto sphere_to_ray = transformed_ray.origin_ - point(0, 0, 0);
    
    float a = dot(transformed_ray.direction_, transformed_ray.direction_);
    float b = 2.0 * dot(transformed_ray.direction_, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1.0;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0)
        return res;
    float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t1 > t2)
    {
        res.push_back(Intersection(t2, *this));
        res.push_back(Intersection(t1, *this));
        return res;
    }
    res.push_back(Intersection(t1, *this));
    res.push_back(Intersection(t2, *this));
    return res;
}

Tuple Sphere::normal_at(const Tuple& world_point)
{
    auto object_point = transform_.inverse() * world_point;
    auto object_normal = object_point - point(0, 0, 0);
    auto world_normal = transform_.inverse().transpose() * object_normal;
    world_normal.w_ = 0;
    return world_normal.normalize();
}

void Sphere::set_transform(const Matrix& t)
{
    transform_ = t;
}

bool operator==(const Sphere& lhs, const Sphere& rhs)
{
    return lhs.material_ == rhs.material_
        && lhs.transform_ == rhs.transform_;
}
