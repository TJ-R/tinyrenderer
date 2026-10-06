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

void drawTriangle(TGAImage *frameBuffer, types::vec3i v1, types::vec3i v2,
                  types::vec3i v3) {

        std::vector<types::vec3i> vecsBetween1And3 =
            getVertexsBetweenVertexes(v1, v3);

        std::vector<types::vec3i> vecsBetween2And3 =
            getVertexsBetweenVertexes(v2, v3);

        // Now draw all lines between both arrays in order
        int v1Idx = 0;
        int v2Idx = 0;
        int v1Max = vecsBetween1And3.size();
        int v2Max = vecsBetween2And3.size();

        while (v1Idx != v1Max && v2Idx != v2Max) {
                drawLinei(frameBuffer, vecsBetween1And3[v1Idx],
                          vecsBetween2And3[v2Idx], tgaColors::red);
                if (v1Idx != v1Max) {
                        v1Idx++;
                }

                if (v2Idx != v2Max) {
                        v2Idx++;
                }
        }

        drawLinei(frameBuffer, v1, v3, tgaColors::green);
        drawLinei(frameBuffer, v2, v3, tgaColors::green);
};

/* Getting all of the vertexes between two points */
std::vector<types::vec3i> getVertexsBetweenVertexes(types::vec3i v1,
                                                    types::vec3i v2) {
        std::vector<types::vec3i> vecs;
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
                        vecs.push_back(types::vec3i{y, x});
                } else {
                        vecs.push_back(types::vec3i{x, y});
                }
        }

        return vecs;
}

} // namespace DrawUtils
