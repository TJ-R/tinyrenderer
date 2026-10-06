#pragma once

#include "../tga_colors.h"
#include "../tgaimage.h"
#include "../types.h"
#include <cmath>

void drawLinei(TGAImage *frameBuffer, vec3i v1, vec3i v2, const TGAColor &c);

void drawTriangle(TGAImage *frameBuffer, vec3i v1, vec3i v2, vec3i v3);

std::vector<vec3i> getVertexsBetweenVertexes(vec3i v1, vec3i v2);

void drawLinef(TGAImage *frameBuffer, vec3f v1, vec3f v2, const TGAColor &c);
