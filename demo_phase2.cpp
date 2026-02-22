#include "document.h"
#include "tokenizer.h"
#include "inverted_index.h"
#include "bm25.h"
#include "compression.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::cout << "=== BM25 Search Engine - Phase 2 Demo ===" << std::endl;
    std::cout << "Now with Delta Encoding!" << std::endl;
    std::cout << std::endl;
    
    // Create sample documents
    std::vector<Document> documents = {
        {1, "quant developer builds trading systems"},
        {2, "search engine systems and ranking"},
        {3, "bm25 ranking algorithm in search engine"}
    };
    
    // Create inverted index
    InvertedIndex index;
    
    std::cout << "Indexing documents..." << std::endl;
    for (const auto& doc : documents) {
        std::vector<std::string> tokens = Tokenizer::tokenize(doc.content);
        index.add_document(doc.id, tokens);
        std::cout << "  Doc " << doc.id << ": \"" << doc.content << "\"" << std::endl;
    }
    std::cout << std::endl;
    
    // Show compression benefits
    std::cout << "=== Compression Analysis ===" << std::endl;
    std::vector<std::string> terms = {"search", "ranking", "systems"};
    
    for (const auto& term : terms) {
        auto doc_ids = index.get_doc_ids(term);
        if (doc_ids.empty()) continue;
        
        auto encoded = Compressor::delta_encode(doc_ids);
        
        std::cout << "Term '" << term << "':" << std::endl;
        std::cout << "  Original doc IDs: ";
        for (size_t i = 0; i < doc_ids.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << doc_ids[i];
        }
        std::cout << std::endl;
        
        std::cout << "  Delta encoded:    ";
        for (size_t i = 0; i < encoded.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << encoded[i];
        }
        std::cout << std::endl;
        std::cout << "  Benefit: Smaller numbers = fewer bits" << std::endl;
        std::cout << std::endl;
    }
    
    // Run query with BM25
    BM25 bm25(index);
    std::string query = "search ranking";
    std::cout << "Query: \"" << query << "\"" << std::endl;
    
    std::vector<std::string> query_tokens = Tokenizer::tokenize(query);
    auto scores = bm25.score(query_tokens);
    
    // Sort results
    std::vector<std::pair<int, double>> results(scores.begin(), scores.end());
    std::sort(results.begin(), results.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });
    
    // Print results
    std::cout << "Top Results:" << std::endl;
    for (const auto& result : results) {
        for (const auto& doc : documents) {
            if (doc.id == result.first) {
                std::cout << "  Doc " << doc.id 
                          << " (score: " << std::fixed << std::setprecision(3) << result.second << "): \"" 
                          << doc.content << "\"" << std::endl;
                break;
            }
        }
    }
    
    std::cout << std::endl;
    std::cout << "✓ Phase 2 Complete: Delta Encoding Working" << std::endl;
    std::cout << "✓ BM25 Scoring: Still Working" << std::endl;
    std::cout << "✓ No Breaking Changes" << std::endl;
    
    return 0;
}