#pragma once

#include <string>
#include <vector>

namespace StringUtils {

std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter);

} // namespace StringUtils
