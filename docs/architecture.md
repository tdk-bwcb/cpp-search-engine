Data Flow
---------

Text -> Tokenizer -> Inverted Index -> BM25 -> Ranked Results

Core Structures
---------------

*   Inverted Index: A map of terms to posting lists (document ID and frequency).
    
*   Document Store: A map of document IDs to their total token counts.
    
*   Global Stats: Tracking total documents and average document length.
    

Key Design Choices
------------------

*   unordered\_map: Chosen for O(1) average lookup speed.
    
*   BM25 Ranking: Selected over TF-IDF to handle term saturation and normalize for document length.
    
*   Minimal Postings: Stores only necessary ID and frequency data to keep Phase 1 lightweight.
    

Tokenization Strategy
---------------------

*   Converts text to lowercase.
    
*   Removes non-alphabetic characters.
    
*   Splits tokens based on whitespace.
    

Phase 1 Status
--------------

*   Done: Correct BM25 ranking, functional inverted index, and basic tokenization.
    
*   Next: Posting list compression (Phase 2), multi-threading, and persistence.
    

System Limits
-------------

*   In-memory only (no persistence yet).
    
*   Single-threaded execution.
    
*   No compression or fuzzy matching.