#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main() {
    hittable_list world;

    // 2 sphere setup
    // world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    camera cam;

    cam.aspect_ratio        = 16.0 / 10.0;
    cam.image_width         = 400;
    cam.samples_per_pixel   = 100;
    cam.max_depth           = 50;

    cam.render(world);

    // // Camera
    // auto focal_length = 1.0;
    // auto viewport_height = 2.0;
    // auto viewport_width = viewport_height * (double(image_width)/image_height);
    // auto camera_center = point3(0, 0, 0);

    // // Calculate the vectors across the horizontal and down the vertical viewport edges.
    // auto viewport_u = vec3(viewport_width, 0, 0);
    // auto viewport_v = vec3(0, -viewport_height, 0);

    // // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // auto pixel_delta_u = viewport_u / image_width;
    // auto pixel_delta_v = viewport_v / image_height;

    // // Calculate the location of the upper left pixel.
    // auto viewport_upper_left = camera_center
    //                          - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // for (int j = 0; j < image_height; j++) {
    //     std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    //     for (int i = 0; i < image_width; i++) {
    //         auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    //         auto ray_direction = pixel_center - camera_center;
    //         ray r(camera_center, ray_direction);

    //         color pixel_color = ray_color(r, world);
    //         write_color(std::cout, pixel_color);
    //     }
    // }

    // std::clog << "\rDone.                 \n";
}