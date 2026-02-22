#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct Posting {
    int doc_id;
    int term_freq;
};

class InvertedIndex {
private:
    std::unordered_map<std::string, std::vector<Posting>> index;
    std::unordered_map<int, int> doc_lengths; // docID → total terms
    int total_docs = 0;

public:
    void add_document(int doc_id, const std::vector<std::string>& tokens);
    const std::vector<Posting>& get_postings(const std::string& term) const;
    std::vector<int> get_doc_ids(const std::string& term) const;
    int get_doc_length(int doc_id) const;
    int get_total_docs() const;
    double get_avg_doc_length() const;
};
