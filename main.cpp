#include "document.h"
#include "tokenizer.h"
#include "inverted_index.h"
#include "bm25.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main(){


// Program flow :
// 1. Sample Documents → 2. Tokenize → 3. Inverted Index → 4. BM25 Score → 5. Rank → 6. Display


    std::cout << "=== BM25 Search Engine- Phase 1 ===" << std::endl;
    std::cout << std::endl;

    // create sample documents
    std::vector<Document> documents = {
        {1, "quant developer builds trading systems"},
        {2, "search engine systems and ranking"},
        {3, "bm25 ranking algorithm in search engine"}
    };

    // Create inverted index
    InvertedIndex index;

    std::cout << "Indexing documents..." << std::endl;
    for(const auto& doc : documents){
        std::vector<std::string> tokens = Tokenizer::tokenize(doc.content);
        index.add_document(doc.id, tokens);
        std::cout << " Doc " << doc.id << ": \"" << doc.content << "\"" << std::endl;   
    }
    std::cout << std::endl;

    // create BM25 scorer
    BM25 bm25(index);

    // query
    std::string query = "bm25";
    std::cout << "Query: \"" << query << "\"" << std::endl;
    std::cout << std::endl;

    std::vector<std::string> query_tokens = Tokenizer::tokenize(query);
    auto scores = bm25.score(query_tokens);

    // sort results by score (descending)
    std::vector<std::pair<int,double>> results(scores.begin(),scores.end());
    std::sort(results.begin(),results.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
    
    // print top k results
    std::cout << "Top results:" << std::endl;
    for(const auto& result : results){
        int doc_id = result.first;
        double score = result.second;

        // find the document
        for(const auto& doc : documents){
            if(doc.id == doc_id){
                std::cout << " Doc " << doc_id << "(score: " << score << "): \"" << doc.content << "\"" << std::endl;
                break;
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Phase 1 Basic Engine Working ✓" << std::endl;
    
    return 0;

}