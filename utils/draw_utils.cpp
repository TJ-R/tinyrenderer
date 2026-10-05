#include "draw_utils.h"

namespace DrawUtils {

void drawLinei(TGAImage *frameBuffer, types::vec3i v1, types::vec3i v2,
               const TGAColor &c) {
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

void drawLinef(TGAImage *frameBuffer, types::vec3f v1, types::vec3f v2,
               const TGAColor &c) {
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

} // namespace DrawUtils
