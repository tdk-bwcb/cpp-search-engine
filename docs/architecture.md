# Search Engine Architecture
<br>

**Current Version:** Phase 2



Data Flow
---------

Text -> Tokenizer -> Inverted Index -> BM25 -> Ranked Results

<br>
<br>


# Phase 1 — Core Search Engine
<br>


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


<br><br>


# Phase 2 — Posting List Compression
<br>


Overview
--------

Implemented **delta encoding** for posting list doc\_ids to reduce storage size while preserving correctness.

Design Decisions
----------------

### 1\. Sorted Posting Lists (Required Invariant)

*   Documents are indexed in increasing doc\_id order.
    
*   Delta encoding requires strictly ascending doc IDs.
    
*   This invariant is enforced by the indexing pipeline.
    

### 2\. Why Delta Encoding?

*   Posting lists contain increasing integers.
    
*   Gaps between doc IDs are smaller than raw IDs.
    
*   Example: 

`   [1, 5, 20, 50] → [1, 4, 15, 30]   `

Smaller numbers → better compression in future variable-byte stage.

Best case:

`   [1,2,3,4,5] → [1,1,1,1,1]   `

### 3\. Module Isolation

*   Implemented in compression.h/cpp
    
*   Independent of BM25 and indexing logic
    
*   Enables isolated testing and incremental integration
    

Correctness Guarantee
---------------------

Core invariant:

`   decode(encode(x)) == x   `

Tested on:

*   Empty lists
    
*   Single element
    
*   Sequential IDs
    
*   Large gaps
    
*   Real index data
    

Memory Impact
-------------

**Uncompressed Posting**


```
int doc_id    (4 bytes)
int term_freq (4 bytes)
Total: 8 bytes per posting
```




**After Delta Encoding**

*   Smaller numeric range
    
*   Prepares for variable-byte encoding (Phase 3)
    
*   Expected total reduction: 50–80% after full compression
    

Current Status
--------------

*   Delta encoding implemented
    
*   Integrated without breaking BM25
    
*   Backward compatibility maintained


---
<br>


_Last Updated: Phase 2 — Delta Encoding Complete_