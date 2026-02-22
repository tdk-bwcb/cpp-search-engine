#include "compression.h"

std::vector<int> Compressor::delta_encode(const std::vector<int>& doc_ids){
    std::vector<int> deltas;
    if(doc_ids.empty()) return deltas;

    // first element satys as-is
    deltas.push_back(doc_ids[0]);

    // store gaps for subsequent elements
    for(size_t i = 1; i < doc_ids.size(); i++){
        deltas.push_back(doc_ids[i] - doc_ids[i-1]);
    }

    return deltas;
}

std::vector<int> Compressor::delta_decode(const std::vector<int>& deltas){
    std::vector<int> doc_ids;
    if (deltas.empty()) return doc_ids;

    // first element satys as-is
    doc_ids.push_back(deltas[0]);

    // Reconstruct by adding deltas
    for (size_t i = 1; i < deltas.size(); ++i) {
       doc_ids.push_back(doc_ids.back() + deltas[i]);
    }

    return doc_ids;
}

