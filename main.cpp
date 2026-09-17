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

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer);

struct Vertex {
        float x;
        float y;
        float z;
};

int main(int argc, char **argv) {
        constexpr int width = 640;
        constexpr int height = 640;
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

        int res = drawObjFile("./obj/diablo3_pose/diablo3_pose.obj",
                              static_cast<float>(width),
                              static_cast<float>(height), &framebuffer);

        framebuffer.write_tga_file("framebuffer.tga");

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

        while (true) {
                nextPos = str.find(delimiter, pos);

                if (nextPos == std::string::npos) {
                        nextPos = str.size() - 1;
                        std::string token = str.substr(pos, nextPos - pos);
                        tokens.push_back(token);
                        break;
                } else {
                        std::string token = str.substr(pos, nextPos - pos);
                        pos = nextPos + 1;
                        tokens.push_back(token);
                }
        }

        return tokens;
}

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer) {
        std::ifstream inf{fileName};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return 1;
        }

        std::vector<Vertex> verticies;
        std::string strInput;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v' && strInput[1] == ' ') {
                        std::vector<std::string> tokens = split(strInput, " ");
                        Vertex vertex;
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

                        drawLine(frameBuffer, v1x, v1y, v2x, v2y, red);
                        drawLine(frameBuffer, v2x, v2y, v3x, v3y, red);
                        drawLine(frameBuffer, v3x, v3y, v1x, v1y, red);
                        frameBuffer->set(v1x, v1y, white);
                        frameBuffer->set(v2x, v2y, white);
                        frameBuffer->set(v3x, v3y, white);
                }
        }

        return 0;
}
