#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const {
            return false;
        }
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            // lambertian sphere
            auto scatter_direction = rec.normal + random_unit_vector();

            // if the random vector is opposite of the normal,
            // we could end up with a scatter direction of 0
            // which might cause errors down the line
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        color albedo;
};

class metal : public material {
    public:
        // metal(const color& albedo) : albedo(albedo) {}
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            // surface absorbs scatters which went below the surface
            return (dot(scattered.direction(), rec.normal) > 0);
        }
    
    private:
        color albedo;
        double fuzz;
};


#endif