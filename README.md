# C++ Search Engine

## Overview

High-performance lightweight search engine implemented in C++.

The project focuses on:

- Efficient text indexing
- Fast ranked retrieval
- Memory-aware posting list representation
- Modular architecture

## Features

### Core Retrieval
- Tokenization (lowercase normalization and punctuation filtering)
- Inverted Index construction
- BM25 ranking model
- Top-K result retrieval

### Performance Enhancements (Phase 2)
- Posting list compression module
- Improved storage efficiency for index structures

## Architecture

Raw Text  
→ Tokenizer  
→ Inverted Index Construction  
→ Optional Compression Layer  
→ BM25 Ranking  
→ Retrieval Output

## System Design Notes

- Single shard architecture
- No concurrency layer yet
- Focus on deterministic retrieval correctness and memory efficiency

## Project Status

- Phase 1: Core Search Engine ✔  
- Phase 2: Compression and index optimization ✔ 


