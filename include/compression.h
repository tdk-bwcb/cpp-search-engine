#pragma once
#include <vector>

class Compressor{
public:
    static std::vector<int> delta_encode(const std::vector<int>& doc_ids);
    static std::vector<int> delta_decode(const std::vector<int>& deltas);
};