#include "draw_utils.h"

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

void drawTriangle(TGAImage *frameBuffer, vec3i a, vec3i b, vec3i c,
                  const TGAColor &color) {
        // Bubble sort by y
        if (a.y > b.y) {
                std::swap(a, b);
        }

        if (a.y > c.y) {
                std::swap(a, c);
        }

        if (b.y > c.y) {
                std::swap(b, c);
        }

        // a, b, c are now in order by y
        // rasterize lower half ay to by (horizontal sweep)
        if (a.y != b.y) {
                for (int y = a.y; y <= b.y; ++y) {
                        // determine starting and ending x
                        /*
                         * Pretty close to x = ((y-b) * (x2 - x1)) / (y2 - y1)
                         * Also written as ((y - b) * 1/m) where
                         * m = (y2 - y1) / (x2 - x1) rise over run
                         */
                        int x1 = a.x + ((y - a.y) * (c.x - a.x)) / (c.y - a.y);
                        int x2 = a.x + ((y - a.y) * (b.x - a.x)) / (b.y - a.y);

                        // Fill in all pixels on horizontal line from x1 to x2
                        for (int x = std::min(x1, x2); x < std::max(x1, x2);
                             ++x) {
                                frameBuffer->set(x, y, color);
                        }
                }
        }

        // Do the same for top half
        if (b.y != c.y) {
                for (int y = b.y; y <= c.y; ++y) {
                        // determine starting and ending x
                        /*
                         * Pretty close to x = ((y-b) * (x2 - x1)) / (y2 - y1)
                         * Also written as ((y - b) * 1/m) where
                         * m = (y2 - y1) / (x2 - x1) rise over run
                         */
                        int x1 = a.x + ((y - a.y) * (c.x - a.x)) / (c.y - a.y);
                        int x2 = b.x + ((y - b.y) * (c.x - b.x)) / (c.y - b.y);

                        // Fill in all pixels on horizontal line from x1 to x2
                        for (int x = std::min(x1, x2); x < std::max(x1, x2);
                             ++x) {
                                frameBuffer->set(x, y, color);
                        }
                }
        }
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
