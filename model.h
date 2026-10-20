#include "utils/string_utils.h"
#include "vector.h"
#include <fstream>
#include <iostream>
#include <string>

class Model {
      private:
        std::vector<vec3f> verts;
        std::vector<int> face_verts; // needed group in 3

      public:
        Model(std::string filename);
        int nverts();
        int nfaces();
        vec3f vert(const int i) const;
        vec3f vert(const int iface, const int nthvert) const;
};
