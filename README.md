# C++ Search Engine (Phase 1)

## Features
- Tokenization (lowercase + punctuation removal)
- Inverted Index
- BM25 Ranking
- Top-K Retrieval

## Architecture
Raw Text → Tokenizer → Inverted Index → BM25 → Ranked Results

## Status
Phase 1 Complete:
- Single shard
- No compression
- No concurrency

Next:
- Posting list compression