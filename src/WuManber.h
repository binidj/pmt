#pragma once
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Text.h"
#include "SinglePatternSearch.h"

class WuManber : public SinglePatternSearch
{
private:
    std::vector<unsigned long long> CharMasks;
    std::vector<unsigned long long> Errors;
    std::vector<unsigned long long> NextErrors;
    void GetCharMasks(const Text& pattern);
public:
    void Init(const Text& pattern, const int EditDistance);
    const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance);
};