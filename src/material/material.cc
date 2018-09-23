#include "material.hh"

namespace
{
    bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
}

Material::Material()
    : color_(Color(1, 1, 1)), ambient_(0.1), diffuse_(0.9), specular_(0.9),
    shininess_(200)
{}

Color Material::lighting(const PointLight& light, const Tuple& point,
                    const Tuple& eyev, const Tuple& normalv)
{
    auto effective_color = color_ * light.intensity_;
    auto lightv = (light.position_ - point).normalize();

    auto ambient = effective_color * ambient_;
    Color diffuse;
    Color specular;

    auto light_dot_normal = dot(lightv, normalv);

    if (light_dot_normal < 0)
    {
        diffuse = Color::black();
        specular = Color::black();
    }
    else
    {
        diffuse = effective_color * diffuse_ * light_dot_normal;

        auto reflectv = (-lightv).reflect(normalv);
        float reflect_dot_eye = std::pow(dot(reflectv, eyev), shininess_);

        if (reflect_dot_eye <= 0)
            specular = Color::black();
        else
            specular = light.intensity_ * specular_ * reflect_dot_eye;
    }
    return ambient + diffuse + specular;
}

bool operator==(const Material& lhs, const Material& rhs)
{
    return lhs.color_ == rhs.color_ && equal(lhs.ambient_, rhs.ambient_)
        && equal(lhs.diffuse_, rhs.diffuse_)
        && equal(lhs.specular_, rhs.specular_)
        && equal(lhs.shininess_, rhs.shininess_);
}
