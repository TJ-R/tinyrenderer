#include "tgaimage.h"
#include <cmath>
#include <strings.h>

constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

struct vec3f {
        float x;
        float y;
        float z;
};

class Triangle {
        vec3f m_p1;
        vec3f m_p2;
        vec3f m_p3;

        Triangle(vec3f p1, vec3f p2, vec3f p3) {
                m_p1 = p1;
                m_p2 = p2;
                m_p3 = p3;
        };

        void draw(TGAImage *frameBuffer) {
                drawLine(frameBuffer, m_p1, m_p2);
                drawLine(frameBuffer, m_p1, m_p3);
                drawLine(frameBuffer, m_p2, m_p3);
        };

      private:
        void drawLine(TGAImage *frameBuffer, vec3f p1, vec3f p2) {
                // frameBuffer->set();
                bool steep = std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y);
                if (steep) {
                        std::swap(p1.x, p1.y);
                        std::swap(p2.x, p2.y);
                }

                if (p1.x > p2.x) {
                        std::swap(p1.x, p2.x);
                        std::swap(p1.y, p2.y);
                }
                for (int x = p1.x; x <= p2.x; x++) {
                        // Sampling based on x positioning
                        // t is calced by the division of the a "normalization"
                        // of of the line starting it a 1 in first iteration of
                        // loop and the amount of samples we need 3rd iter for
                        // red would be (10 - 7) / (62 - 7) => 3 / 55 interval
                        // of t will be 0 -> 1
                        float t = (x - p1.x) / static_cast<float>(p2.x - p1.x);
                        int y = std::round(p1.y + (t * (p2.y - p1.y)));
                        if (steep) {
                                // flipped the x and y back when drawing
                                // since it is currently transposed
                                frameBuffer->set(y, x, red);
                        } else {
                                frameBuffer->set(x, y, red);
                        }
                }
        };
};
