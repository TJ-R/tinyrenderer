#include "model.h"

Model::Model(std::string filename) {
        std::ifstream inf{filename};

        if (!inf) {
                std::cout << "Failed to open file" << "\n";
                return;
        } else {
                std::cout << "Starting drawing for " << filename << "\n";
        }

        std::string strInput;
        while (std::getline(inf, strInput)) {
                if (strInput[0] == 'v' && strInput[1] == ' ') {
                        std::vector<std::string> tokens = split(strInput, " ");
                        vec3f vertex;
                        vertex.x = std::stof(tokens[1]);
                        vertex.y = std::stof(tokens[2]);
                        vertex.z = std::stof(tokens[3]);
                        verts.push_back(vertex);
                } else if (strInput[0] == 'f' && strInput[1] == ' ') {
                        std::vector faceStrs = split(strInput, " ");

                        size_t pos;
                        size_t nextPos;

                        pos = 0;
                        nextPos = faceStrs[1].find("/", pos);
                        int vIdx1 = std::stoi(faceStrs[1].substr(pos, nextPos));
                        face_verts.push_back(vIdx1 - 1);

                        pos = 0;
                        nextPos = faceStrs[2].find("/", pos);
                        int vIdx2 = std::stoi(faceStrs[2].substr(pos, nextPos));
                        face_verts.push_back(vIdx2 - 1);

                        pos = 0;
                        nextPos = faceStrs[3].find("/", pos);
                        int vIdx3 = std::stoi(faceStrs[3].substr(pos, nextPos));
                        face_verts.push_back(vIdx3 - 1);
                }
        }
}

int Model::nverts() {
        return verts.size();
}

int Model::nfaces() {
        return face_verts.size() / 3;
}

vec3f Model::vert(const int i) const {
        return verts[i];
}

vec3f Model::vert(const int iface, const int nthvert) const {
        int idx = iface * 3 + nthvert;

        return verts[face_verts[idx]];
}
