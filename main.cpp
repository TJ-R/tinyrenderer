#include "model.h"
#include "tgaimage.h"
#include "triangle.cpp"
#include "vector.h"
#include <iostream>
#include <strings.h>

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer);

std::tuple<int, int, int> project(vec3f v, int width, int height) {
        // v is currently from [-1, 1] range
        // need to move it on our plane so
        // + 1 => [0, 2] and then divide by 2
        // => [0, 1]

        int ax = ((v.x + 1.) * width / 2);
        int ay = ((v.y + 1.) * height / 2);
        int az = ((v.z + 1.) * 255 / 2);

        return std::make_tuple(ax, ay, az);
};

void triangle(TGAImage *frameBuffer, TGAImage *zbuffer, vec3i a, vec3i b,
              vec3i c, const TGAColor &color) {
        int bboxMaxX = std::max(std::max(a.x, b.x), c.x);
        int bboxMaxY = std::max(std::max(a.y, b.y), c.y);
        int bboxMinX = std::min(std::min(a.x, b.x), c.x);
        int bboxMinY = std::min(std::min(a.y, b.y), c.y);

        double totalArea =
            0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));

        // Don't draw triangles smaller than area of 1
        if (totalArea < 1)
                return;

#pragma omp parallel for // Saying run loop in parallel
        for (int x = bboxMinX; x <= bboxMaxX; ++x) {
                for (int y = bboxMinY; y <= bboxMaxY; ++y) {
                        double alpha =
                            (0.5 * (x * (b.y - c.y) + b.x * (c.y - y) +
                                    c.x * (y - b.y))) /
                            totalArea;

                        double beta =
                            (0.5 * (a.x * (y - c.y) + x * (c.y - a.y) +
                                    c.x * (a.y - y))) /
                            totalArea;

                        double gamma =
                            (0.5 * (a.x * (b.y - y) + b.x * (y - a.y) +
                                    x * (a.y - b.y))) /
                            totalArea;

                        if (alpha < 0 || beta < 0 || gamma < 0)
                                continue;

                        TGAColor barycentric;
                        if (alpha < 0.1 || beta < 0.1 || gamma < 0.1) {
                                barycentric[0] = 255 * alpha;
                                barycentric[1] = 255 * beta;
                                barycentric[2] = 255 * gamma;
                        } else {

                                barycentric[0] = 0;
                                barycentric[1] = 0;
                                barycentric[2] = 0;
                        }

                        unsigned char z = static_cast<unsigned char>(
                            alpha * a.z + beta * b.z + gamma * c.z);

                        // If pixel already has something drawn there
                        // with higher z-index then skip pixel
                        if (z <= zbuffer->get(x, y)[0])
                                continue;
                        zbuffer->set(x, y, {z});
                        frameBuffer->set(x, y, color);
                }
        }
}

int main(int argc, char **argv) {
        constexpr int width = 800;
        constexpr int height = 800;
        TGAImage framebuffer(width, height, TGAImage::RGB);
        TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);

        if (argc < 2) {
                std::cout << "Usage: " << argv[0] << " obj/model.obj\n";
                return 1;
        }

        Model model(argv[1]);
        for (int i = 0; i < model.nfaces(); i++) {
                auto [ax, ay, az] = project(model.vert(i, 0), width, height);
                auto [bx, by, bz] = project(model.vert(i, 1), width, height);
                auto [cx, cy, cz] = project(model.vert(i, 2), width, height);

                TGAColor rnd;
                for (int c = 0; c < 3; c++)
                        rnd[c] = std::rand() % 255;

                triangle(&framebuffer, &zbuffer, {ax, ay, az}, {bx, by, bz},
                         {cx, cy, cz}, rnd);
                // drawLinei(&framebuffer, vec3i{ax, ay}, vec3i{bx, by},
                //           tgaColors::red);
                // drawLinei(&framebuffer, vec3i{ax, ay}, vec3i{cx, cy},
                //           tgaColors::red);
                // drawLinei(&framebuffer, vec3i{cx, cy}, vec3i{bx, by},
                //           tgaColors::red);
        }

        // vec3i a = vec3i{20, 20};
        // vec3i b = vec3i{80, 65};
        // vec3i c = vec3i{50, 85};

        // drawTriangle(&framebuffer, a, b, c, tgaColors::red);
        // triangle(&framebuffer, &zbuffer, a, b, c, tgaColors::red);

        zbuffer.write_tga_file("zbuffer.tga");
        framebuffer.write_tga_file("framebuffer.tga");
        return 0;
}
