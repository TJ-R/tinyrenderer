#pragma once

#include "../tga_colors.h"
#include "../tgaimage.h"
#include "../types.h"
#include <cmath>

namespace DrawUtils {

void drawLinei(TGAImage *frameBuffer, types::vec3i v1, types::vec3i v2,
               const TGAColor &c);

void drawLinef(TGAImage *frameBuffer, types::vec3f v1, types::vec3f v2,
               const TGAColor &c);

} // namespace DrawUtils
