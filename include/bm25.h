#pragma once
#include "inverted_index.h"
#include <unordered_map>
#include <vector>

class BM25 {

private:
    const InvertedIndex &index;
    double k1;
    double b;

public:
    BM25(const InvertedIndex& idx, double k1 = 1.5, double b = 0.75);
    std::unordered_map<int,double> score(const std::vector<std::string>& query_tokens);
};