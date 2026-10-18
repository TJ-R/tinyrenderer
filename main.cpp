#include "model.h"
#include "tgaimage.h"
#include "triangle.cpp"
#include "types.h"
#include "utils/string_utils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <strings.h>

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer);

std::tuple<int, int> project(vec3f v, int width, int height) {
        // v is currently from [-1, 1] range
        // need to move it on our plane so
        // + 1 => [0, 2] and then divide by 2
        // => [0, 1]

        int ax = ((v.x + 1.) * width / 2);
        int ay = ((v.y + 1.) * height / 2);

        return std::make_tuple(ax, ay);
};

void triangle(TGAImage *frameBuffer, vec3i a, vec3i b, vec3i c,
              const TGAColor &color) {
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

                        frameBuffer->set(x, y, barycentric);
                }
        }
}

int main(int argc, char **argv) {
        constexpr int width = 100;
        constexpr int height = 100;
        TGAImage framebuffer(width, height, TGAImage::RGB);

        // if (argc < 2) {
        //         std::cout << "Usage: " << argv[0] << " obj/model.obj\n";
        //         return 1;
        // }

        // Model model(argv[1]);
        // for (int i = 0; i < model.nfaces(); i++) {
        //         auto [ax, ay] = project(model.vert(i, 0), width, height);
        //         auto [bx, by] = project(model.vert(i, 1), width, height);
        //         auto [cx, cy] = project(model.vert(i, 2), width, height);
        //
        //         TGAColor rnd;
        //         for (int c = 0; c < 3; c++)
        //                 rnd[c] = std::rand() % 255;
        //
        //         triangle(&framebuffer, {ax, ay}, {bx, by}, {cx, cy}, rnd);
        //         // drawLinei(&framebuffer, vec3i{ax, ay}, vec3i{bx, by},
        //         //           tgaColors::red);
        //         // drawLinei(&framebuffer, vec3i{ax, ay}, vec3i{cx, cy},
        //         //           tgaColors::red);
        //         // drawLinei(&framebuffer, vec3i{cx, cy}, vec3i{bx, by},
        //         //           tgaColors::red);
        // }

        vec3i a = vec3i{20, 20};
        vec3i b = vec3i{80, 65};
        vec3i c = vec3i{50, 85};

        // drawTriangle(&framebuffer, a, b, c, tgaColors::red);
        triangle(&framebuffer, a, b, c, tgaColors::red);

        framebuffer.write_tga_file("framebuffer.tga");
        return 0;
}

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer) {
        std::ifstream inf{fileName};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return 1;
        } else {
                std::cout << "Starting drawing for " << fileName << "\n";
        }

        std::vector<vec3f> verticies;
        std::string strInput;
        int count = 0;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v' && strInput[1] == ' ') {
                        std::vector<std::string> tokens = split(strInput, " ");
                        vec3f vertex;
                        // Transform -1 to 1 space to 0 to 2
                        vertex.x = std::stof(tokens[1]) + 1;
                        vertex.y = std::stof(tokens[2]) + 1;
                        vertex.z = std::stof(tokens[3]) + 1;
                        verticies.push_back(vertex);
                } else if (strInput[0] == 'f' && strInput[1] == ' ') {
                        std::vector faceStrs = split(strInput, " ");

                        size_t pos;
                        size_t nextPos;

                        pos = 0;
                        nextPos = faceStrs[1].find("/", pos);
                        int vIdx1 =
                            std::stoi(faceStrs[1].substr(pos, nextPos)) - 1;
                        int v1x = std::round(verticies[vIdx1].x * (width / 2));
                        int v1y = std::round(verticies[vIdx1].y * (height / 2));

                        pos = 0;
                        nextPos = faceStrs[2].find("/", pos);
                        int vIdx2 =
                            std::stoi(faceStrs[2].substr(pos, nextPos)) - 1;

                        int v2x = std::round(verticies[vIdx2].x * (width / 2));
                        int v2y = std::round(verticies[vIdx2].y * (height / 2));

                        pos = 0;
                        nextPos = faceStrs[3].find("/", pos);
                        int vIdx3 =
                            std::stoi(faceStrs[3].substr(pos, nextPos)) - 1;

                        int v3x = std::round(verticies[vIdx3].x * (width / 2));
                        int v3y = std::round(verticies[vIdx3].y * (height / 2));

                        if (count == 0) {
                                triangle(frameBuffer, vec3i{v1x, v1y},
                                         vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                         tgaColors::red);
                                count++;
                        } else if (count == 1) {
                                triangle(frameBuffer, vec3i{v1x, v1y},
                                         vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                         tgaColors::blue);
                                count++;
                        } else if (count == 2) {
                                triangle(frameBuffer, vec3i{v1x, v1y},
                                         vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                         tgaColors::green);
                                count++;
                        } else if (count == 3) {
                                triangle(frameBuffer, vec3i{v1x, v1y},
                                         vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                         tgaColors::yellow);
                                count++;
                        } else {
                                triangle(frameBuffer, vec3i{v1x, v1y},
                                         vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                         tgaColors::white);
                                count = 0;
                        }
                        frameBuffer->set(v1x, v1y, tgaColors::white);
                        frameBuffer->set(v2x, v2y, tgaColors::white);
                        frameBuffer->set(v3x, v3y, tgaColors::white);
                }
        }

        return 0;
}
