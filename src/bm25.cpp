#include "bm25.h"
#include <cmath>

// Constructor: Initialize member variables using member initializer list
BM25::BM25(const InvertedIndex& idx, double k1, double b)
    : index(idx), k1(k1), b(b) {}

std::unordered_map<int,double> BM25::score(const std::vector<std::string>& query_tokens) {
    std::unordered_map<int, double> scores;

    int N = index.get_total_docs();
    double avgdl = index.get_avg_doc_length();

    for(const auto& term : query_tokens) {
        const auto& postings = index.get_postings(term);

        if(postings.empty()){
            continue;
        }

        // calculate IDF
        int df = postings.size();
        double idf = std::log((N - df + 0.5) / (df + 0.5));

        for(const auto& posting : postings){
            int doc_id = posting.doc_id;
            int tf = posting.term_freq;
            int doc_len = index.get_doc_length(doc_id);

            // BM25 formula
            double numerator = tf * (k1 + 1);
            double denominator = tf + k1 * (1 - b + b * (doc_len / avgdl));
            double score = idf * (numerator / denominator);

            scores[doc_id] += score;
         }
    }

    return scores;
}
