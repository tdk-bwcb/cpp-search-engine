#include "inverted_index.h"
#include <stdexcept>

void InvertedIndex::add_document(int doc_id, const std::vector<std::string>& tokens) {
    total_docs++;
    doc_lengths[doc_id] = tokens.size();

    // count term frequencies
    std::unordered_map<std::string, int> term_counts;
    for(const auto& token : tokens){
        term_counts[token]++;
    }

    // add postings to index
    for(const auto& pair : term_counts){
        index[pair.first].push_back({doc_id,pair.second});
    }
}

const std::vector<Posting>& InvertedIndex::get_postings(const std::string& term) const {
    static const std::vector<Posting> empty;
    auto it = index.find(term);
    if(it != index.end()){
        return it->second;
    }
    return empty;
}

std::vector<int> InvertedIndex::get_doc_ids(const std::string& term) const {
    std::vector<int> doc_ids;
    const auto& postings = get_postings(term);

    for(const auto& posting : postings) {
        doc_ids.push_back(posting.doc_id);
    }

    return doc_ids;
}

int InvertedIndex::get_doc_length(int doc_id) const {
    auto it = doc_lengths.find(doc_id);
    if(it != doc_lengths.end()){
        return it->second;
    }
    return 0;
}

int InvertedIndex::get_total_docs() const {
    return total_docs;
}

double InvertedIndex::get_avg_doc_length() const { // Needed for BM25's length normalization
    if (total_docs == 0) return 0.0;
    int total_length = 0;
    for (const auto& pair : doc_lengths) {
        total_length += pair.second;
    }
    return static_cast<double>(total_length) / total_docs;
}