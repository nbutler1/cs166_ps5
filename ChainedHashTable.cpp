#include "ChainedHashTable.h"

ChainedHashTable::ChainedHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  // TODO: Implement this
  for(size_t i = 0; i < numBuckets; i++){
    buckets.push_back({});
  }
  numBucks = numBuckets;
  TableHash = family->get();
}

ChainedHashTable::~ChainedHashTable() {
  // TODO: Implement this
}

void ChainedHashTable::insert(int data) {
  size_t bucket = TableHash(data) % numBucks;
  for(size_t i = 0; i < buckets.at(bucket).size(); i++){
    if(buckets.at(bucket).at(i) == data)
      return;
  }
  buckets[bucket].push_back(data);
}

bool ChainedHashTable::contains(int data) const {
  size_t bucket = TableHash(data) % numBucks;
  for(size_t i = 0; i < buckets.at(bucket).size(); i++){
    if(buckets.at(bucket).at(i) == data)
      return true;
  }
  return false;
}

void ChainedHashTable::remove(int data) {
  size_t bucket = TableHash(data) % numBucks;
  for(size_t i = 0; i < buckets.at(bucket).size(); i++){
    if(buckets.at(bucket).at(i) == data){
      buckets.at(bucket).erase(buckets.at(bucket).begin() + i);
      return;
    }
  }
  
}
