#pragma once
#include <vector>
#include "Text.h"

class KMP
{
private:
    static std::vector<int> Border;
    static void GetBorder(const Text& pattern);
public:
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, bool BuildBorder = false);
};