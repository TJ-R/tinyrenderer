#include "tgaimage.h"
#include "types.h"
#include "utils/draw_utils.h"
#include <strings.h>

class Triangle {
        vec3f m_p1;
        vec3f m_p2;
        vec3f m_p3;

      public:
        Triangle(vec3f p1, vec3f p2, vec3f p3) {
                m_p1 = p1;
                m_p2 = p2;
                m_p3 = p3;
        };

        void draw(TGAImage *frameBuffer, TGAColor c) {
                drawLinef(frameBuffer, m_p1, m_p2, c);
                drawLinef(frameBuffer, m_p1, m_p3, c);
                drawLinef(frameBuffer, m_p2, m_p3, c);
        };
};
