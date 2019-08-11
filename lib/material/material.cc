#include "material.hh"

namespace
{
    constexpr inline bool equal(float a, float b)
    {
        return abs(a - b) < EPSILON;
    }
} // namespace

Material::Material()
    : color_(Color(1, 1, 1))
    , ambient_(0.1)
    , diffuse_(0.9)
    , specular_(0.9)
    , shininess_(200)
    , reflective_(0.0)
    , transparency_(0.0)
    , refractive_index_(1.0)
    , pattern_(nullptr)
{}

Color Material::lighting(const Shape& object, const PointLight& light,
                         const Tuple& point, const Tuple& eyev,
                         const Tuple& normalv, bool in_shadow)
{
    auto& color = color_;
    if (pattern_)
        color_ = pattern_->pattern_at_shape(object, point);
    auto effective_color = color * light.intensity_;
    auto lightv = (light.position_ - point).normalize();

    auto ambient = effective_color * ambient_;
    if (in_shadow)
        return ambient;
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
        float reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye <= 0)
            specular = Color::black();
        else
        {
            auto factor = std::pow(reflect_dot_eye, shininess_);
            specular = light.intensity_ * specular_ * factor;
        }
    }
    return ambient + diffuse + specular;
}

bool operator==(const Material& lhs, const Material& rhs)
{
    return lhs.color_ == rhs.color_ && equal(lhs.ambient_, rhs.ambient_)
        && equal(lhs.diffuse_, rhs.diffuse_)
        && equal(lhs.specular_, rhs.specular_)
        && equal(lhs.shininess_, rhs.shininess_)
        && equal(lhs.reflective_, rhs.reflective_)
        && equal(lhs.transparency_, rhs.transparency_)
        && equal(lhs.refractive_index_, rhs.refractive_index_);
}
