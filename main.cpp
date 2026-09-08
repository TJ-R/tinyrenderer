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

        drawLine(&framebuffer, ax, ay, bx, by, blue);
        drawLine(&framebuffer, cx, cy, bx, by, green);
        drawLine(&framebuffer, cx, cy, ax, ay, yellow);
        drawLine(&framebuffer, ax, ay, cx, cy, red);
        framebuffer.write_tga_file("framebuffer.tga");
        return 0;
}

void drawLine(TGAImage *frameBuffer, int ax, int ay, int bx, int by,
              const TGAColor &c) {
        for (float t = 0.; t <= 1.; t += 0.1) {
                int x = std::round(ax + (t * (bx - ax)));
                int y = std::round(ay + (t * (by - ay)));
                frameBuffer->set(x, y, c);
        }
}
