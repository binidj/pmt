#pragma once
#include <vector>
#include "Text.h"

class KMP
{
private:
    static std::vector<int> Border;
public:
    static const std::vector<int> GetBorder(const Text& pattern);
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, bool BuildBorder = false);
};