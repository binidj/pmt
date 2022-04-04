#pragma once
#include <vector>
#include "Text.h"
#include "SinglePatternSearch.h"

class KMP : public SinglePatternSearch
{
private:
    std::vector<int> Border;
public:
    static std::vector<int> GetBorder(const Text& pattern);
    void Init(const Text& pattern, const int EditDistance);
    const int Search(const Text& text, const Text& pattern, const int EditDistance);
};