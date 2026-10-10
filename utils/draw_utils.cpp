#include "draw_utils.h"
#include <iostream>

void drawLinei(TGAImage *frameBuffer, vec3i v1, vec3i v2, const TGAColor &c) {
        // frameBuffer->set();
        bool steep = std::abs(v1.x - v2.x) < std::abs(v1.y - v2.y);
        if (steep) {
                std::swap(v1.x, v1.y);
                std::swap(v2.x, v2.y);
        }

        if (v1.x > v2.x) {
                std::swap(v1.x, v2.x);
                std::swap(v1.y, v2.y);
        }
        for (int x = v1.x; x <= v2.x; x++) {
                // Sampling based on x positioning
                // t is calced by the division of the a "normalization"
                // of of the line starting it a 1 in first iteration of
                // loop and the amount of samples we need 3rd iter for
                // red would be (10 - 7) / (62 - 7) => 3 / 55 interval
                // of t will be 0 -> 1
                float t = (x - v1.x) / static_cast<float>(v2.x - v1.x);
                int y = std::round(v1.y + (t * (v2.y - v1.y)));
                if (steep) {
                        // flipped the x and y back when drawing
                        // since it is currently transposed
                        frameBuffer->set(y, x, c);
                } else {
                        frameBuffer->set(x, y, c);
                }
        }
};

void drawLinef(TGAImage *frameBuffer, vec3f v1, vec3f v2, const TGAColor &c) {
        // frameBuffer->set();
        bool steep = std::abs(v1.x - v2.x) < std::abs(v1.y - v2.y);
        if (steep) {
                std::swap(v1.x, v1.y);
                std::swap(v2.x, v2.y);
        }

        if (v1.x > v2.x) {
                std::swap(v1.x, v2.x);
                std::swap(v1.y, v2.y);
        }
        for (int x = v1.x; x <= v2.x; x++) {
                // Sampling based on x positioning
                // t is calced by the division of the a "normalization"
                // of of the line starting it a 1 in first iteration of
                // loop and the amount of samples we need 3rd iter for
                // red would be (10 - 7) / (62 - 7) => 3 / 55 interval
                // of t will be 0 -> 1
                float t = (x - v1.x) / static_cast<float>(v2.x - v1.x);
                int y = std::round(v1.y + (t * (v2.y - v1.y)));
                if (steep) {
                        // flipped the x and y back when drawing
                        // since it is currently transposed
                        frameBuffer->set(y, x, c);
                } else {
                        frameBuffer->set(x, y, c);
                }
        }
};

void drawTriangle(TGAImage *frameBuffer, vec3i v1, vec3i v2, vec3i v3) {
        // Sort by y ... v3 is highest y
        if (v1.y > v2.y) {
                std::swap(v1, v2);
        }

        if (v2.y > v3.y) {
                std::swap(v2, v3);
        }

        // This should be refactored into separate functions where it makes
        // sense Determine which cords have furthest distance
        int diffV1V3X = std::abs(v3.x - v1.x);
        int diffV2V3X = std::abs(v3.x - v2.x);
        int diffV1V3Y = std::abs(v3.y - v1.y);
        int diffV2V3Y = std::abs(v3.y - v2.y);

        if (diffV1V3X >= diffV2V3X && diffV1V3X > diffV1V3Y &&
            diffV1V3X > diffV2V3Y) {
                // do nothing
                for (int x = v1.x; x < v3.x; ++x) {
                        int x1 = x;
                        float t = (x - v1.x) / static_cast<float>(v3.x - v1.x);
                        int y1 = std::round(v1.y + t * (v3.y - v1.y));
                        int x2 = std::round(v2.x + t * (v3.x - v2.x));
                        int y2 = std::round(v2.y + t * (v3.y - v2.y));

                        std::cout << "t is " << t << "\n";
                        std::cout << "v1t From (" << x1 << ", " << y1 << ")\n";
                        std::cout << "v2t From (" << x2 << ", " << y2 << ")\n";

                        drawLinei(frameBuffer, vec3i{x1, y1}, vec3i{x2, y2},
                                  tgaColors::red);
                }

        } else if (diffV2V3X >= diffV1V3X && diffV2V3X > diffV1V3Y &&
                   diffV2V3X > diffV2V3Y) {
                std::swap(v1, v2);
                for (int x = v1.x; x < v3.x; ++x) {
                        int x1 = x;
                        float t = (x - v1.x) / static_cast<float>(v3.x - v1.x);
                        int y1 = std::round(v1.y + t * (v3.y - v1.y));
                        int x2 = std::round(v2.x + t * (v3.x - v2.x));
                        int y2 = std::round(v2.y + t * (v3.y - v2.y));

                        std::cout << "t is " << t << "\n";
                        std::cout << "v1t From (" << x1 << ", " << y1 << ")\n";
                        std::cout << "v2t From (" << x2 << ", " << y2 << ")\n";

                        drawLinei(frameBuffer, vec3i{x1, y1}, vec3i{x2, y2},
                                  tgaColors::red);
                }
        } else if (diffV1V3Y >= diffV1V3X && diffV1V3Y > diffV1V3X &&
                   diffV1V3Y > diffV2V3Y) {
                std::swap(v1.x, v1.y);
                std::swap(v2.x, v2.y);
                for (int x = v1.x; x < v3.x; ++x) {
                        int x1 = x;
                        float t = (x - v1.x) / static_cast<float>(v3.x - v1.x);
                        int y1 = std::round(v1.y + t * (v3.y - v1.y));
                        int x2 = std::round(v2.x + t * (v3.x - v2.x));
                        int y2 = std::round(v2.y + t * (v3.y - v2.y));

                        std::cout << "t is " << t << "\n";
                        std::cout << "v1t From (" << x1 << ", " << y1 << ")\n";
                        std::cout << "v2t From (" << x2 << ", " << y2 << ")\n";

                        // Flipped due to swap a top of block
                        drawLinei(frameBuffer, vec3i{y1, x1}, vec3i{y2, x2},
                                  tgaColors::red);
                }

        } else {
                std::swap(v1, v2);
                std::swap(v1.x, v1.y);
                std::swap(v2.x, v2.y);
                for (int x = v1.x; x < v3.x; ++x) {
                        int x1 = x;
                        float t = (x - v1.x) / static_cast<float>(v3.x - v1.x);
                        int y1 = std::round(v1.y + t * (v3.y - v1.y));
                        int x2 = std::round(v2.x + t * (v3.x - v2.x));
                        int y2 = std::round(v2.y + t * (v3.y - v2.y));

                        std::cout << "t is " << t << "\n";
                        std::cout << "v1t From (" << x1 << ", " << y1 << ")\n";
                        std::cout << "v2t From (" << x2 << ", " << y2 << ")\n";

                        // Flipped due to swap a top of block
                        drawLinei(frameBuffer, vec3i{y1, x1}, vec3i{y2, x2},
                                  tgaColors::red);
                }
        }

        drawLinei(frameBuffer, v1, v3, tgaColors::white);
        drawLinei(frameBuffer, v2, v3, tgaColors::white);
        drawLinei(frameBuffer, v1, v2, tgaColors::white);
};

/* Getting all of the vertexes between two points */
std::vector<vec3i> getVertexsBetweenVertexes(vec3i v1, vec3i v2) {
        std::vector<vec3i> vecs;
        bool steep = std::abs(v1.x - v2.x) < std::abs(v1.y - v2.y);
        if (steep) {
                std::swap(v1.x, v1.y);
                std::swap(v2.x, v2.y);
        }

        if (v1.x > v2.x) {
                std::swap(v1.x, v2.x);
                std::swap(v1.y, v2.y);
        }
        for (int x = v1.x; x <= v2.x; x++) {
                // Sampling based on x positioning
                // t is calced by the division of the a "normalization"
                // of of the line starting it a 1 in first iteration of
                // loop and the amount of samples we need 3rd iter for
                // red would be (10 - 7) / (62 - 7) => 3 / 55 interval
                // of t will be 0 -> 1
                float t = (x - v1.x) / static_cast<float>(v2.x - v1.x);
                int y = std::round(v1.y + (t * (v2.y - v1.y)));
                if (steep) {
                        // flipped the x and y back when drawing
                        // since it is currently transposed
                        vecs.push_back(vec3i{y, x});
                } else {
                        vecs.push_back(vec3i{x, y});
                }
        }

        return vecs;
}
