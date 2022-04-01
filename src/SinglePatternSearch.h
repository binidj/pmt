#pragma once
#include "Text.h"
#include <vector>

class SinglePatternSearch
{
public:
    virtual void Init(const Text& pattern, const int EditDistance) = 0;
    virtual const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance) = 0;
    SinglePatternSearch() = default;
    ~SinglePatternSearch() = default;
};