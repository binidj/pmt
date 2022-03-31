#pragma once
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Text.h"

class WuManber
{
private:
    static std::vector<unsigned long long> CharMasks;
    static std::vector<unsigned long long> Errors;
    static std::vector<unsigned long long> NextErrors;

    static void GetCharMasks(const Text& pattern);
public:
    static const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance = 0, const bool Rebuild = false);
};