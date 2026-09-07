#include "tgaimage.h"
#include <cmath>
#include <iostream>

constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void drawLine(TGAImage *frameBuffer, int ax, int ay, int bx, int by,
              const TGAColor &c);

int main(int argc, char **argv) {
        constexpr int width = 64;
        constexpr int height = 64;
        TGAImage framebuffer(width, height, TGAImage::RGB);

        int ax = 7, ay = 3;
        int bx = 12, by = 37;
        int cx = 62, cy = 53;

        framebuffer.set(ax, ay, white);
        framebuffer.set(bx, by, white);
        framebuffer.set(cx, cy, white);

        std::cout << "Green\n";
        drawLine(&framebuffer, ax, ay, bx, by, green);
        std::cout << "Blue\n";
        drawLine(&framebuffer, ax, ay, cx, cy, blue);
        std::cout << "Red\n";
        drawLine(&framebuffer, bx, by, cx, cy, red);

        framebuffer.write_tga_file("framebuffer.tga");
        return 0;
}

void drawLine(TGAImage *frameBuffer, int ax, int ay, int bx, int by,
              const TGAColor &c) {
        for (int t = 1; t <= 100; t++) {
                // This is rounding without cmath usage
                float res = t / 100.f;
                int subRes = bx - ax;
                std::cout << "ax " << ax << "\n"
                          << "bx " << bx << "\n"
                          << "t / 100 = " << res << "\n"
                          << "bx - ax = " << subRes << "\n";

                int x = ax + (t / 100.f) * (bx - ax);
                int y = ay + (t / 100.f) * (by - ay);
                std::cout << "X: " << x << " Y: " << y << "\n";
                frameBuffer->set(x, y, c);
        }
}
