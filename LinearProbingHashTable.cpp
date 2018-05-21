#include "LinearProbingHashTable.h"

size_t increment(size_t numBucks, size_t bucket) {
  if(bucket >= numBucks - 1)
    return 0;
  return bucket + 1;
}

LinearProbingHashTable::LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  TableHash = family->get();
  std::vector<int> temp(numBuckets, 0);
  buckets = temp.copy(); //(int*)malloc(numBuckets * sizeof(int));  
  numBucks = numBuckets;
  indicators = temp.copy();
}

LinearProbingHashTable::~LinearProbingHashTable() {
  //free(buckets);
  //free(indicators);
}


void LinearProbingHashTable::insert(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Search for empty spot.  If spot has data, just return
  while(empty == 1){
    if(val_at_spot == data)
      return;
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
    //empty = *(indicators + (sizeof(int) + bucket));
    //val_at_spot = *(buckets + (sizeof(int) + bucket));
  }

  // Now place element and update indicators
  indicators[bucket] = 1;
  buckets[bucket] = data;
}

bool LinearProbingHashTable::contains(int data) const {
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Loop while still looking at non-empty spots
  while(empty != 0) {
    // If not a tombstone, we found it!
    if(empty != -1 && val_at_spot == data)
        return true;
    // If tombstone, value has been removed...
    if(empty == -1 && val_at_spot == data)
        return false;
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
  }
  return false;
}

void LinearProbingHashTable::remove(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Loop while we have not found the data
  while(empty != 0){
    if(val_at_spot == data){
      *(indicators + (sizeof(int) + bucket)) = -1;
      return;
    }
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
  }
}
