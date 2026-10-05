#include "tgaimage.h"
#include "types.h"
#include "utils/draw_utils.h"
#include <strings.h>

class Triangle {
        types::vec3f m_p1;
        types::vec3f m_p2;
        types::vec3f m_p3;

      public:
        Triangle(types::vec3f p1, types::vec3f p2, types::vec3f p3) {
                m_p1 = p1;
                m_p2 = p2;
                m_p3 = p3;
        };

        void draw(TGAImage *frameBuffer, TGAColor c) {
                DrawUtils::drawLinef(frameBuffer, m_p1, m_p2, c);
                DrawUtils::drawLinef(frameBuffer, m_p1, m_p3, c);
                DrawUtils::drawLinef(frameBuffer, m_p2, m_p3, c);
        };
};
