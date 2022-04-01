#pragma once
#include <vector>
#include "Text.h"
#include "SinglePatternSearch.h"

class KMP : SinglePatternSearch
{
private:
    std::vector<int> Border;
public:
    static std::vector<int> GetBorder(const Text& pattern);
    void Init(const Text& pattern, const int EditDistance);
    const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance);
};