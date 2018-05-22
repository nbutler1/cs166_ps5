#include "RobinHoodHashTable.h"

size_t increment(size_t numBucks, size_t bucket) {
  if(bucket >= numBucks - 1)
    return 0;
  return bucket + 1;
}

size_t distance(size_t numBucks, size_t hashed, size_t actual){
  // If hashed is larger than actual we have gone past zero
  if(hashed > actual) {
    actual = actual + (numBucks - hashed);
  }
  return actual - hashed;
}

RobinHoodHashTable::RobinHoodHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  TableHash = family->get();
  std::vector<int> temp(numBuckets, 0);
  buckets = temp; 
  numBucks = numBuckets;
  indicators = temp;
}

RobinHoodHashTable::~RobinHoodHashTable() {
  // TODO: Implement this
}

void RobinHoodHashTable::insert(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Search for empty spot.  If spot has data, just return
  while(empty == 1){
    if(val_at_spot == data)
      return;
    size_t buck_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    size_t data_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    if(buck_dist > data_dist){
      buckets[bucket] = data;
      indicators[bucket] = 1;
      data = val_at_spot;
    }
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
  }

  // Now place element and update indicators
  indicators[bucket] = 1;
  buckets[bucket] = data;

}

bool RobinHoodHashTable::contains(int data) const {
  // TODO: Implement this
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Search for empty spot.  If spot has data, just return
  while(empty == 1){
    if(val_at_spot == data)
      return true;
    size_t buck_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    size_t data_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    if(buck_dist < data_dist){
      return false;
    }
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
  }
  return false;
}

void RobinHoodHashTable::remove(int data) {
  size_t bucket = TableHash(data) % numBucks;
  int empty = indicators.at(bucket);
  int val_at_spot = buckets.at(bucket);
  
  // Loop while we have not found the data
  while(empty != 0){
    if(val_at_spot == data){
      indicators[bucket] = -1;
      return;
    }
    size_t buck_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    size_t data_dist = distance(numBucks, TableHash(val_at_spot), bucket);
    if(buck_dist < data_dist){
      return;
    }
    bucket = increment(numBucks, bucket);
    empty = indicators.at(bucket);
    val_at_spot = buckets.at(bucket);
  }
}
