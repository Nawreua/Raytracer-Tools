#include "sphere.hh"

std::vector<Intersection> Sphere::local_intersect(const Ray& ray)
{
    std::vector<Intersection> res;

    auto sphere_to_ray = ray.origin_ - point(0, 0, 0);

    float a = dot(ray.direction_, ray.direction_);
    float b = 2.0 * dot(ray.direction_, sphere_to_ray);
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

Tuple Sphere::local_normal_at(const Tuple& world_point)
{
    auto object_normal = world_point - point(0, 0, 0);
    return object_normal;
}

Sphere Sphere::glass_sphere()
{
    auto sphere = Sphere();
    sphere.transform_ = Matrix::identity_matrix();
    sphere.material_.transparency_ = 1.0;
    sphere.material_.refractive_index_ = 1.5;
    return sphere;
}

/*
bool operator==(const Sphere& lhs, const Sphere& rhs)
{
    return lhs.material_ == rhs.material_
        && lhs.transform_ == rhs.transform_;
}
*/
