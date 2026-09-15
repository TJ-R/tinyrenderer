#include "tgaimage.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <strings.h>

constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void drawLine(TGAImage *frameBuffer, int ax, int ay, int bx, int by,
              const TGAColor &c);

int drawObjFile(const char *fileName);

struct Vertex {
        float x;
        float y;
        float z;
};

int main(int argc, char **argv) {
        constexpr int width = 64;
        constexpr int height = 64;
        TGAImage framebuffer(width, height, TGAImage::RGB);

        // int ax = 7, ay = 3;
        // int bx = 12, by = 37;
        // int cx = 62, cy = 53;
        //
        // framebuffer.set(ax, ay, white);
        // framebuffer.set(bx, by, white);
        // framebuffer.set(cx, cy, white);

        // drawLine(&framebuffer, ax, ay, bx, by, blue);
        // drawLine(&framebuffer, cx, cy, bx, by, green);
        // drawLine(&framebuffer, cx, cy, ax, ay, yellow);
        // drawLine(&framebuffer, ax, ay, cx, cy, red);
        // framebuffer.write_tga_file("framebuffer.tga");
        //

        int res = drawObjFile("./obj/diablo3_pose/diablo3_pose.obj");
        if (res != 0) {
                return 0;
        }
        return 0;
}

void drawLine(TGAImage *frameBuffer, int ax, int ay, int bx, int by,
              const TGAColor &c) {

        bool steep = std::abs(ax - bx) < std::abs(ay - by);

        // transpose if true
        if (steep) {
                std::swap(ax, ay);
                std::swap(bx, by);
        }

        if (ax > bx) {
                std::swap(ax, bx);
                std::swap(ay, by);
        }
        for (int x = ax; x <= bx; x++) {
                // Sampling based on x positioning
                // t is calced by the division of the a "normalization"
                // of of the line starting it a 1 in first iteration of
                // loop and the amount of samples we need 3rd iter for
                // red would be (10 - 7) / (62 - 7) => 3 / 55 interval
                // of t will be 0 -> 1
                float t = (x - ax) / static_cast<float>(bx - ax);
                int y = std::round(ay + (t * (by - ay)));
                if (steep) {
                        // flipped the x and y back when drawing
                        // since it is currently transposed
                        frameBuffer->set(y, x, c);
                } else {
                        frameBuffer->set(x, y, c);
                }
        }
}

std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter) {

        // Currently failing with blank output
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t nextPos;

        while ((nextPos = str.find(delimiter, pos)) != std::string::npos) {
                std::string token = str.substr(pos, nextPos - pos);

                std::cout << token << "\n";
                pos = nextPos;
        }

        return tokens;
}

int drawObjFile(const char *fileName) {
        std::ifstream inf{fileName};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return 1;
        }

        std::vector<Vertex> verticies;
        std::string strInput;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v') {
                        split(strInput, " ");
                } else if (strInput[0] == 'f') {
                }
        }

        return 0;
}
