#include "compression.h"
#include "document.h"
#include "tokenizer.h"
#include "inverted_index.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <algorithm>

void print_vector(const std::string& label, const std::vector<int>& vec) {
    std::cout << std::setw(15) << std::left << label << ": ";
    if(vec.empty()) {
        std::cout << "(empty)";
    }
    else {
        for(size_t i = 0; i < vec.size(); i++) {
            if(i>0) std::cout << ", ";
            std::cout << vec[i];
        }
    }
    std::cout << std::endl;
}

void test_delta_encoding() {
    std::cout << "=== Delta Encoding Tests ===" << std::endl;
    std::cout << std::endl;

    // Test 1: Normal case with gaps
    {
        std::cout << "Test 1: Normal case with gaps" << std::endl;
        std::vector<int> original = {1, 5, 20, 50};
        
        auto encoded = Compressor::delta_encode(original);
        auto decoded = Compressor::delta_decode(encoded);
        
        print_vector("Original", original);
        print_vector("Encoded", encoded);
        print_vector("Decoded", decoded);
        
        assert(original == decoded);
        std::cout << "✓ PASS: decode(encode(x)) == x" << std::endl;
        std::cout << std::endl;
    }

    // Test 2: Single element
    {
        std::cout << "Test 2: Single element" << std::endl;
        std::vector<int> original = {42};
        
        auto encoded = Compressor::delta_encode(original);
        auto decoded = Compressor::delta_decode(encoded);
        
        print_vector("Original", original);
        print_vector("Encoded", encoded);
        print_vector("Decoded", decoded);
        
        assert(original == decoded);
        std::cout << "✓ PASS: Single element works" << std::endl;
        std::cout << std::endl;
    }

    // Test 3: Empty list
    {
        std::cout << "Test 3: Empty list" << std::endl;
        std::vector<int> original = {};
        
        auto encoded = Compressor::delta_encode(original);
        auto decoded = Compressor::delta_decode(encoded);
        
        print_vector("Original", original);
        print_vector("Encoded", encoded);
        print_vector("Decoded", decoded);
        
        assert(original == decoded);
        std::cout << "✓ PASS: Empty list handled" << std::endl;
        std::cout << std::endl;
    }

    // Test 4: Sequential IDs (smallest gaps)
    {
        std::cout << "Test 4: Sequential IDs (best compression)" << std::endl;
        std::vector<int> original = {1, 2, 3, 4, 5};
        
        auto encoded = Compressor::delta_encode(original);
        auto decoded = Compressor::delta_decode(encoded);
        
        print_vector("Original", original);
        print_vector("Encoded", encoded);
        print_vector("Decoded", decoded);
        
        assert(original == decoded);
        std::cout << "✓ PASS: Sequential IDs compress to all 1s" << std::endl;
        std::cout << std::endl;
    }

    // Test 5: Large gaps
    {
        std::cout << "Test 5: Large gaps" << std::endl;
        std::vector<int> original = {1, 1000, 5000, 10000};
        
        auto encoded = Compressor::delta_encode(original);
        auto decoded = Compressor::delta_decode(encoded);
        
        print_vector("Original", original);
        print_vector("Encoded", encoded);
        print_vector("Decoded", decoded);
        
        assert(original == decoded);
        std::cout << "✓ PASS: Large gaps handled correctly" << std::endl;
        std::cout << std::endl;
    }
}

void test_with_real_index() {
    std::cout << "=== Integration Test: Delta Encoding with Real Index ===" << std::endl;
    std::cout << std::endl;

    // Create documents and index
    std::vector<Document> documents = {
        {1, "search engine ranking"},
        {3, "search algorithm"},
        {5, "ranking systems"},
        {10, "search and ranking"},
        {15, "engine design"}
    };

    InvertedIndex index;

    std::cout << "Indexing documents..." << std::endl;
    for (const auto& doc : documents) {
        std::vector<std::string> tokens = Tokenizer::tokenize(doc.content);
        index.add_document(doc.id, tokens);
        std::cout << "  Doc " << doc.id << ": \"" << doc.content << "\"" << std::endl;
    }
    std::cout << std::endl; 

    // Test compression on terms
    std::vector<std::string> test_terms = {"search", "ranking", "engine"};

    for (const auto& term : test_terms) {
        std::cout << "Term: \"" << term << "\"" << std::endl;
        
        auto doc_ids = index.get_doc_ids(term);
        
        if (doc_ids.empty()) {
            std::cout << "  No documents contain this term" << std::endl;
            std::cout << std::endl;
            continue;
        }
        
        auto encoded = Compressor::delta_encode(doc_ids);
        auto decoded = Compressor::delta_decode(encoded);

        print_vector("  Doc IDs", doc_ids);
        print_vector("  Encoded", encoded);
        print_vector("  Decoded", decoded);
        
        assert(doc_ids == decoded);
        std::cout << "  ✓ Compression verified" << std::endl;

        // Calculate compression benefit
        int original_ints = doc_ids.size();
        int max_original = doc_ids.empty() ? 0 : doc_ids.back();
        int max_encoded = encoded.empty() ? 0 : *std::max_element(encoded.begin(), encoded.end());
        
        std::cout << "  Analysis:" << std::endl;
        std::cout << "    - Max original ID: " << max_original << std::endl;
        std::cout << "    - Max encoded gap: " << max_encoded << std::endl;
        std::cout << "    - Compression benefit: Smaller numbers = fewer bits needed" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         PHASE 2: DELTA ENCODING VERIFICATION              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
    
    try {
        test_delta_encoding();
        test_with_real_index();
        
        std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║  ✓ ALL TESTS PASSED - Delta Encoding Working              ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "✗ TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}