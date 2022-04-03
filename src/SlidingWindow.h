#pragma once
#include <vector>
#include "Text.h"
#include "SinglePatternSearch.h"

class SlidingWindow : public SinglePatternSearch
{
public:
    void Init(const Text& pattern, const int EditDistance);
    const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance);
};