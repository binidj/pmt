#pragma once
#include <vector>
#include "Text.h"

class SlidingWindow
{
public:
    static const std::vector<size_t> Search(const Text& text, const Text& pattern);
};