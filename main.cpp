#include "tgaimage.h"
#include "triangle.cpp"
#include "types.h"
#include "utils/draw_utils.h"
#include "utils/string_utils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <strings.h>

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer);

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

        // int res = drawObjFile("./obj/diablo3_pose/diablo3_pose.obj",
        //                       static_cast<float>(width),
        //                       static_cast<float>(height), &framebuffer);

        // std::ifstream inf{"./obj/diablo3_pose/diablo3_pose.obj"};
        // std::string strInput;
        // for (int i = 0; i < 10; ++i) {
        //         std::getline(inf, strInput);
        //         std::cout << "Num of bytes in line " << i << " is "
        //                   << strInput.size() << " bytes\n";
        // }
        // types::vec3f p1 = {7.0, 3.0, 0.0};
        // types::vec3f p2 = {12.0, 37.0, 0.0};
        // types::vec3f p3 = {62.0, 53.0, 0.0};
        // Triangle triangle = {p1, p2, p3};
        // triangle.draw(&framebuffer, tgaColors::blue);
        //
        types::vec3i p1 = {7, 3, 0};
        types::vec3i p2 = {12, 37, 0};
        types::vec3i p3 = {62, 53, 0};
        DrawUtils::drawTriangle(&framebuffer, p1, p2, p3);
        framebuffer.write_tga_file("framebuffer.tga");

        // if (res != 0) {
        //         return res;
        // }
        return 0;
}

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer) {
        std::ifstream inf{fileName};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return 1;
        }

        std::vector<types::vec3f> verticies;
        std::string strInput;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v' && strInput[1] == ' ') {
                        std::vector<std::string> tokens =
                            StringUtils::split(strInput, " ");
                        types::vec3f vertex;
                        // Transform -1 to 1 space to 0 to 2
                        vertex.x = std::stof(tokens[1]) + 1;
                        vertex.y = std::stof(tokens[2]) + 1;
                        vertex.z = std::stof(tokens[3]) + 1;
                        verticies.push_back(vertex);
                } else if (strInput[0] == 'f' && strInput[1] == ' ') {
                        std::vector faceStrs =
                            StringUtils::split(strInput, " ");

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

                        DrawUtils::drawLinei(
                            frameBuffer, types::vec3i{v1x, v1y},
                            types::vec3i{v2x, v2y}, tgaColors::red);
                        DrawUtils::drawLinei(
                            frameBuffer, types::vec3i{v2x, v2y},
                            types::vec3i{v3x, v3y}, tgaColors::red);
                        DrawUtils::drawLinei(
                            frameBuffer, types::vec3i{v3x, v3y},
                            types::vec3i{v1x, v1y}, tgaColors::red);

                        frameBuffer->set(v1x, v1y, tgaColors::white);
                        frameBuffer->set(v2x, v2y, tgaColors::white);
                        frameBuffer->set(v3x, v3y, tgaColors::white);
                }
        }

        return 0;
}
