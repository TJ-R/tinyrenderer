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
        constexpr int width = 1280;
        constexpr int height = 960;
        TGAImage framebuffer(width, height, TGAImage::RGB);

        int res = drawObjFile("./obj/diablo3_pose/diablo3_pose.obj",
                              static_cast<float>(width),
                              static_cast<float>(height), &framebuffer);

        framebuffer.write_tga_file("framebuffer.tga");

        if (res != 0) {
                return res;
        }
        return 0;
}

int drawObjFile(const char *fileName, const float width, const float height,
                TGAImage *frameBuffer) {
        std::ifstream inf{fileName};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return 1;
        } else {
                std::cout << "Starting drawing for " << fileName << "\n";
        }

        std::vector<vec3f> verticies;
        std::string strInput;
        int count = 0;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v' && strInput[1] == ' ') {
                        std::vector<std::string> tokens = split(strInput, " ");
                        vec3f vertex;
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

                        if (count == 0) {
                                drawTriangle(frameBuffer, vec3i{v1x, v1y},
                                             vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                             tgaColors::red);
                                count++;
                        } else if (count == 1) {
                                drawTriangle(frameBuffer, vec3i{v1x, v1y},
                                             vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                             tgaColors::blue);
                                count++;
                        } else if (count == 2) {
                                drawTriangle(frameBuffer, vec3i{v1x, v1y},
                                             vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                             tgaColors::green);
                                count++;
                        } else if (count == 3) {
                                drawTriangle(frameBuffer, vec3i{v1x, v1y},
                                             vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                             tgaColors::yellow);
                                count++;
                        } else {
                                drawTriangle(frameBuffer, vec3i{v1x, v1y},
                                             vec3i{v2x, v2y}, vec3i{v3x, v3y},
                                             tgaColors::white);
                                count = 0;
                        }
                        frameBuffer->set(v1x, v1y, tgaColors::white);
                        frameBuffer->set(v2x, v2y, tgaColors::white);
                        frameBuffer->set(v3x, v3y, tgaColors::white);
                }
        }

        return 0;
}
