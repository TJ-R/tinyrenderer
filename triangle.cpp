struct vec3f {
        float x;
        float y;
        float z;
};

class Triangle {
        vec3f m_p1;
        vec3f m_p2;
        vec3f m_p3;

        Triangle(vec3f p1, vec3f p2, vec3f p3) {
                m_p1 = p1;
                m_p2 = p2;
                m_p3 = p3;
        };

        void draw() {
        }
};
