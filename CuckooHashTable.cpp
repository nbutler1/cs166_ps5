#include "CuckooHashTable.h"

CuckooHashTable::CuckooHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  numBucks = numBuckets;
  h1 = family->get();
  h2 = family->get();
  std::vector<int> temp(numBuckets, 0);
  b1 = temp;
  b2 = temp;
  i1 = temp;
  i2 = temp;
}

CuckooHashTable::~CuckooHashTable() {
  // TODO: Implement this
}

void CuckooHashTable::insert(int data) {
  if(contains(data))
      return;
  size_t buck = h1(data) % numBucks;
  if(i1[buck] == 0){
    b1[buck] = data;
    i1[buck] = 1;
  }
  int temp = data;
  size_t counter = 1;
  while(true) {
    // First evict
    if(counter %2 == 0) {
      temp = b2[buck];
      b2[buck] = data;
      data = temp;
      buck = h1(data) % numBucks;
      if(i1[buck] == 0){
        b1[buck] = data;
        i1[buck] = 1;
        break;
      }
    } else {
      temp = b1[buck];
      b1[buck] = data;
      data = temp;
      buck = h2(data) % numBucks;
      if(i2[buck] == 0){
        b2[buck] = data;
        i2[buck] = 1;
        break;
      }
    }

    // Now find next hash
    counter += 1;
  }
}

bool CuckooHashTable::contains(int data) const {
  size_t buck = h1(data) % numBucks;
  size_t buck2 = h2(data) % numBucks;
  if(b1[buck] == data || b2[buck2] == data)
    return true;
  return false;
}

void CuckooHashTable::remove(int data) {
  size_t buck = h1(data) % numBucks;
  if(b1[buck] == data){
    i1[buck] = 0;
    return;
  }
  buck = h2(data) % numBucks;
  if(b2[buck] == data)
      i2[buck] = 0;
}
