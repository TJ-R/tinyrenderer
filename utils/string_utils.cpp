#include "string_utils.h"

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
