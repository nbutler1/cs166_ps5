#include "LinearProbingHashTable.h"


LinearProbingHashTable::LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  // TODO: Implement this
  TableHash = family->get();
  buckets = (int*)malloc(numBuckets * sizeof(int));  
  numBucks = numBuckets;
  indicators = (int*)calloc(numBuckets *sizeof(int));
}

LinearProbingHashTable::~LinearProbingHashTable() {
  // TODO: Implement this
  free(buckets);
  free(inidcators);
}

size_t LinearProbingHashTable::increment(size_t bucket) {
  if(bucket == numBucks - 1)
    return 0;
  return bucket + 1;
}

void LinearProbingHashTable::insert(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = *(indicators + (sizeof(int) + bucket));
  int val_at_spot = *(buckets + (sizeof(int) + bucket));
  
  // Search for empty spot.  If spot has data, just return
  while(empty == 1){
    if(val_at_spot == data)
      return;
    bucket = increment(bucket);
    empty = *(indicators + (sizeof(int) + bucket));
    val_at_spot = *(buckets + (sizeof(int) + bucket));
  }

  // Now place element and update indicators
  *(buckets + (sizeof(int) + bucket)) = data;
  *(indicators + (sizeof(int) + bucket)) = 1;
}

bool LinearProbingHashTable::contains(int data) const {
  size_t bucket = TableHash(data) % numBucks;
  int empty = *(indicators + (sizeof(int) + bucket));
  int val_at_spot = *(buckets + (sizeof(int) + bucket));
  
  // Loop while still looking at non-empty spots
  while(empty != 0) {
    // If not a tombstone, we found it!
    if(empty != -1 && val_at_spot == data)
        return true;
    // If tombstone, value has been removed...
    if(empty == -1 && val_at_spot == data)
        return false;
    bucket = increment(bucket);
    int empty = *(indicators + (sizeof(int) + bucket));
    int val_at_spot = *(buckets + (sizeof(int) + bucket));
  }
  return false;
}

void LinearProbingHashTable::remove(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = *(indicators + (sizeof(int) + bucket));
  int val_at_spot = *(buckets + (sizeof(int) + bucket));
  
  // Loop while we have not found the data
  while(empty != 0){
    if(val_at_spot == data){
      *(indicators + (sizeof(int) + bucket)) = -1;
      return;
    }
    bucket = increment(bucket);
    int empty = *(indicators + (sizeof(int) + bucket));
    int val_at_spot = *(buckets + (sizeof(int) + bucket));
  }
}
