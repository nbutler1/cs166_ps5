#include "LinearProbingHashTable.h"

LinearProbingHashTable::LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  // TODO: Implement this
  TableHash = family->get();
  buckets = (int*)malloc(numBuckets * sizeof(int));  
}

LinearProbingHashTable::~LinearProbingHashTable() {
  // TODO: Implement this
  free(buckets);
}

void LinearProbingHashTable::insert(int data) {
  // TODO: Implement this
}

bool LinearProbingHashTable::contains(int data) const {
  // TODO: Implement this
  return false;
}

void LinearProbingHashTable::remove(int data) {
  // TODO: Implement this
}
